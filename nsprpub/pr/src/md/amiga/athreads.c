/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/* 
 * The contents of this file are subject to the Mozilla Public
 * License Version 1.1 (the "License"); you may not use this file
 * except in compliance with the License. You may obtain a copy of
 * the License at http://www.mozilla.org/MPL/
 * 
 * Software distributed under the License is distributed on an "AS
 * IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
 * implied. See the License for the specific language governing
 * rights and limitations under the License.
 * 
 * The Original Code is the Netscape Portable Runtime (NSPR).
 * 
 * The Initial Developer of the Original Code is Netscape
 * Communications Corporation.  Portions created by Netscape are 
 * Copyright (C) 1998-2000 Netscape Communications Corporation.  All
 * Rights Reserved.
 * 
 * Contributor(s):
 * Jeff Shepherd (jshepher@jshepher.dyndns.org)
 * 
 * Alternatively, the contents of this file may be used under the
 * terms of the GNU General Public License Version 2 or later (the
 * "GPL"), in which case the provisions of the GPL are applicable 
 * instead of those above.  If you wish to allow use of your 
 * version of this file only under the terms of the GPL and not to
 * allow others to use your version of this file under the MPL,
 * indicate your decision by deleting the provisions above and
 * replace them with the notice and other provisions required by
 * the GPL.  If you do not delete the provisions above, a recipient
 * may use your version of this file under either the MPL or the
 * GPL.
 */

#include <primpl.h>

static PRStatus _InitThread(PRThread *pr);

void _Exit(PRIntn status) {
    /* TODO - how to signal all the threads to stop!! */
}

static PRThread *primordialThread = NULL;

void _MD_Early_Init(void) {
    PRThread *thread;
    thread = PR_NEWZAP(PRThread);
    primordialThread = thread;
    thread->p = (struct Process *)FindTask(NULL);
    thread->p->pr_Task.tc_UserData = thread;
    _InitThread(thread);
    /* For debugging */
    setvbuf(stdout, NULL, _IONBF, 0);
    printf("Primorial Thread %lx\n", thread);
    atexit(PR_Cleanup);
}

PR_IMPLEMENT(PRStatus) PR_Interrupt(PRThread *thread) {
    PRThread *me = PR_CurrentThread();
    char buf[50];
    struct MsgPort *port;
    sprintf(buf, "NSPRPORT-%lx\n", thread);
    /* See if the thread is still around by trying to 
     * look for its public message port 
     */
    Forbid();
    port = FindPort(buf);
    if (port == NULL) {
        Permit();
        return PR_SUCCESS;
    }

    PR_Lock(thread->stateLock);
    thread->flags |= _PR_INTERRUPT;
    printf("%lx Interrupting thread %lx, flags are now %lx\n", me, thread, thread->flags);
    PR_Unlock(thread->stateLock);
    if (me != thread) {
        Signal((struct Task *)thread->p, 1 << thread->interruptSignal);
    }
    Permit();
        
    return PR_SUCCESS;
}

/**
 * Initialize the NSPR-specific part for a thread
 */
static PRStatus _InitThread(PRThread *pr) {
    char *buf = PR_Malloc(50);
    sprintf(buf, "NSPRPORT-%lx\n", pr);
    pr->port = CreateMsgPort();
    PR_ASSERT(pr->port);
    pr->port->mp_Node.ln_Name = buf;
    AddPort(pr->port);
    pr->selectPort = CreateMsgPort();
    PR_ASSERT(pr->selectPort);
    pr->interruptSignal = AllocSignal(-1);
    PR_ASSERT(pr->interruptSignal != -1);

    pr->sleepRequest =
        (struct timerequest *)CreateExtIO(pr->port, sizeof(struct timerequest));    
    PR_ASSERT(pr->sleepRequest);

    if (OpenDevice(TIMERNAME, UNIT_VBLANK, 
                   (struct IORequest *)pr->sleepRequest, 0)) {
        PR_ASSERT(PR_FALSE);
    }

    pr->AmiTCP_Base = OpenLibrary("bsdsocket.library", 0);

    PR_INIT_CLIST(&pr->lockList);
    pr->stateLock = PR_NewLock();
    PR_ASSERT(pr->stateLock);
    return PR_SUCCESS;
}

/**
 * Clean up the NSPR-specific thread objects
 */
static void procExit(void) {  
    PRThread *me = PR_GetCurrentThread();
    PRThread *join;

    Forbid();
    RemPort(me->port);
    join = me->join;
    if (me->prev) {
        me->prev->next = me->next;
    }
    if (me->next) {
        me->next->prev = me->prev;
    }
    Permit();

    _PR_DestroyThreadPrivate(me);
    PR_Free(me->port->mp_Node.ln_Name);
    DeleteMsgPort(me->port);
    DeleteMsgPort(me->selectPort);
    FreeSignal(me->interruptSignal);
    CloseDevice((struct IORequest *)me->sleepRequest);
    DeleteExtIO((struct IORequest *)me->sleepRequest);
    if (me->AmiTCP_Base != NULL)
        CloseLibrary(me->AmiTCP_Base);

    if (join != NULL) {
        printf("%lx done, signalling parent\n", me);
        fflush(stdout);
        PR_ASSERT(join->state == _PR_JOIN_WAIT);
        _PR_MD_Signal(join);
    }
    PR_DestroyLock(me->stateLock);
    PR_Free(me);
}

/**
 * First code called when the thread starts
 */
static void procEntry(void) {	
    PRThread *pr;
    struct Library *ixemulbase;

    /* Hack. I need to wait for the parent to initialize some things for me */
    Wait(SIGBREAKF_CTRL_F);
    pr = PR_GetCurrentThread();
    //  ixemulbase = OpenLibrary("ixemul.library", 0);
    _InitThread(pr);
    /* We are done initialization, signal the parent */
    PR_ASSERT(pr->parent->state == _PR_SUSPENDED);
    _PR_MD_Signal(pr->parent);
    pr->startFunc(pr->arg);
    //  CloseLibrary(ixemulbase);
    procExit();
}


static int _PR_Map_Priority(PRThreadPriority priority) {
    int retval;
    switch (priority) {
    case PR_PRIORITY_NORMAL:
        retval = 0;
        break;
    case PR_PRIORITY_LOW:
        retval = -128;
        break;
    case PR_PRIORITY_HIGH:
        retval = 64;
        break;
    case PR_PRIORITY_URGENT:
        retval = 127;
        break;
    }
    return retval;
}

PR_IMPLEMENT(PRThread*) PR_CreateThread(PRThreadType type,
                                        void (PR_CALLBACK *start)(void *arg),
                                        void *arg,
                                        PRThreadPriority priority,
                                        PRThreadScope scope,
                                        PRThreadState state,
                                        PRUint32 stackSize) {
    PRThread *thread; 
    PRThread *me;

    if (!_pr_initialized) _PR_ImplicitInitialization();

    me = PR_CurrentThread();
    thread = PR_NEWZAP(PRThread);
    if (thread == NULL) {
        return NULL;
    }

    thread->startFunc = start;
    thread->arg = arg;
    thread->priority = priority;
    thread->state = state;

    if (stackSize < 32768) stackSize = 32768;
    Forbid();
    thread->p = CreateNewProcTags(NP_StackSize, stackSize,
                                  NP_Name, "NSPR Thread",
                                  NP_Input, Input(),
                                  NP_Output, Output(),
                                  NP_CloseInput, FALSE,
                                  NP_CloseOutput, FALSE,
                                  NP_Error, Output(),
                                  NP_Priority, _PR_Map_Priority(priority),
                                  NP_CloseError, FALSE,
                                  NP_Entry, (ULONG)procEntry);

    if(thread->p != NULL) {
        thread->p->pr_Task.tc_UserData = thread;
        /* Hack for ixemul.library to work */
        thread->p->pr_Task.tc_TrapCode = me->p->pr_Task.tc_TrapCode;
        thread->p->pr_Task.tc_TrapData = me->p->pr_Task.tc_TrapData;
        thread->parent = me;

        /* Put this before signal just in case */
        me->state = _PR_SUSPENDED;        
        /* Hack because the new thread is waiting for us to do this */
        Signal((struct Task *)thread->p, SIGBREAKF_CTRL_F); 
        /* Need to wait for the other thread to do some init so there
         * isn't a race condition when we do a PR_CreateThread and do 
         * a PR_JoinThread before the thread comes up fully */
        _PR_MD_Wait(me, PR_FALSE);
        me->state = _PR_RUNNING;

        /* Add this thread to our list of threads */
        thread->next = me->next;
        if (me->next) {
            me->next->prev = thread;
        }        
        me->next = thread;
        thread->prev = me;
        Permit();
    } else {
        PR_Free(thread);
        thread = NULL;
        Permit();
    }
    printf("CreateThread(%lx) created thread %lx\n", me, thread);
    return thread;
}

PR_IMPLEMENT(PRThread*) PR_GetCurrentThread(void) {
    struct Process *p = (struct Process *)FindTask(NULL);
    return (PRThread *)p->pr_Task.tc_UserData;
}

PR_IMPLEMENT(PRStatus) PR_JoinThread(PRThread *thread) {
    PRThread *me = PR_GetCurrentThread();
    char buf[50];
    struct MsgPort *port;
  
    sprintf(buf, "NSPRPORT-%lx\n", thread);
    /* See if the thread is still around by trying to 
     * look for its public message port 
     */
    Forbid();
    port = FindPort(buf);
    if (port == NULL) {
        Permit();
        return PR_SUCCESS;
    }
    thread->join = me;

    me->state = _PR_JOIN_WAIT;
    Permit();
    _PR_MD_Wait(me, PR_FALSE);
    me->state = _PR_RUNNABLE;
    return PR_SUCCESS;
}

PR_IMPLEMENT(void) PR_SetConcurrency(PRUintn numCPUs) {
    /* Nothing to do */
}

PR_IMPLEMENT(void) PR_SetThreadPriority(PRThread *thread, PRThreadPriority priority) {
    thread->priority = priority;
    SetTaskPri((struct Task *)thread->p, _PR_Map_Priority(priority));
}

PR_IMPLEMENT(void) PR_ClearInterrupt(void)
{
    PRThread *me = PR_CurrentThread();
    PR_Lock(me->stateLock);
    SetSignal(0, 1 << me->interruptSignal);
    me->flags &= ~_PR_INTERRUPT;
    printf("Clearing interrupt for %lx, flags are now %lx\n", me, me->flags);
    PR_Unlock(me->stateLock);

}  /* PR_ClearInterrupt */


PR_IMPLEMENT(PRBool) PR_IsInterruptsBlocked(void)
{
    PRThread *me = PR_CurrentThread();
    PRBool retval;
    PR_Lock(me->stateLock);
    retval = (me->flags & _PR_INTERRUPT_BLOCKED) ? PR_TRUE : PR_FALSE;
    PR_Unlock(me->stateLock);
    return retval;
}

PR_IMPLEMENT(void) PR_BlockInterrupt(void)
{
    PRThread *me = PR_CurrentThread();
    PR_Lock(me->stateLock);
    _PR_THREAD_BLOCK_INTERRUPT(me);
    printf("Blocking interrupt for %lx, flags are %lx\n", me, me->flags);
    PR_Unlock(me->stateLock);
}  /* PR_BlockInterrupt */

PR_IMPLEMENT(void) PR_UnblockInterrupt(void)
{
    PRThread *me = PR_CurrentThread();
    PR_Lock(me->stateLock);
    _PR_THREAD_UNBLOCK_INTERRUPT(me);
    printf("Unblocking interrupt for %lx, flags are %lx\n", me, me->flags);
    PR_Unlock(me->stateLock);
}  /* PR_UnblockInterrupt */


void _PR_InitThreads(PRThreadType type, PRThreadPriority priority, 
    PRUintn maxPTDs)
{
    /* Nothing to do */
}



void _PR_InitStacks(void) {
}

PR_IMPLEMENT(PRStatus) PR_Cleanup(void)
{
    PRThread *me = PR_CurrentThread();
    PR_ASSERT(me == primordialThread);
    if (_pr_initialized) {
        _PR_CleanupSocket();
        _PR_CleanupMW();
        _PR_CleanupDtoa();
        _PR_CleanupCallOnce();
        _PR_ShutdownLinker();

        _PR_LogCleanup();
        _PR_CleanupNet();
        /* Close all the fd's before calling _PR_CleanupIO */
        _PR_CleanupIO();
        _PR_CleanupLayerCache();
        _PR_CleanupEnv();
        /* Clean up primorial thread */
        procExit();
        _PR_Release_Memory();
        _pr_initialized = PR_FALSE;
    }
    return PR_SUCCESS;
}  /* PR_Cleanup */

void _PR_MD_Wait(PRThread *thread, PRBool interruptable) {
    ULONG oldSigs;
    ULONG mySig = 1 << thread->port->mp_SigBit;
    PRBool blocked;

    oldSigs = SetSignal(0L, 0L);
#if 0
    if (oldSigs & mySig) {
        printf("HELP!!! %lx already got signal!!\n", thread);
    }
#endif
    SetSignal(0, mySig);
    if (interruptable == PR_TRUE) {
        ULONG interruptSig =  1 << thread->interruptSignal;
        ULONG sigs = mySig | interruptSig;

        // Can't do this here: PR_Lock(thread->stateLock);
        Forbid();
        PR_ASSERT(thread->state != _PR_RUNNING);
        blocked = (thread->flags & _PR_INTERRUPT_BLOCKED) ? PR_TRUE : PR_FALSE;
        // Can't do this here: PR_Unlock(thread->stateLock);
        Permit();        
        Wait(sigs);
    } else {        
        Wait(mySig);
    }
    SetSignal(0, mySig);
}

void _PR_MD_Signal(PRThread *thread) {
    PR_Lock(thread->stateLock);
    PR_ASSERT(thread->state != _PR_RUNNING);
    thread->state = _PR_RUNNING;
    PR_Unlock(thread->stateLock);
    Signal((struct Task *)thread->p, 1 << thread->port->mp_SigBit);
}

PR_IMPLEMENT(PRThreadScope) PR_GetThreadScope(const PRThread *thread) {
    return PR_GLOBAL_THREAD;
}

#if 0
/* FOR NOW */
int putenv(const char *str) {
}

#include <sys/socket.h>
#include <netinet/in.h>
unsigned long inet_addr(const char *cp) {
    return NULL;
}

#endif

