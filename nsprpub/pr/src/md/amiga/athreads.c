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
extern struct Library *A4Base;
#include <proto/a4.h>

/* DEBUG threads */
/*#define DEBUG_ATHREADS*/

static PRStatus _InitThread(PRThread *pr);
static PRStatus PR_JoinThreadInternal(PRThread *thread, PRBool);

void _MD_Exit();

static void killThread (PRThread *thread, PRBool kill) {
#ifdef DEBUG_ATHREADS
    printf("Killing thread %lx with kill %d\n", thread, kill);
#endif

    if (kill) {
        Forbid();
        thread->state = _PR_DEAD_STATE;
        _PR_MD_Signal(thread);
        Permit();
        PR_JoinThreadInternal(thread, PR_TRUE);
    } else if (!thread->daemon) {
        /*        PR_Interrupt(thread);*/
        PR_JoinThreadInternal(thread, PR_TRUE);
    }
#ifdef DEBUG_ATHREADS
    printf("All done killing %x\n", thread);
#endif        
}

static void killThreads(PRBool kill) {
    PRThread *tmp;
    PRThread *me = PR_CurrentThread();

#ifdef DEBUG_ATHREADS
    printf("In processexit %d, next is %lx, prev is %lx\n", kill, me->next, me->prev);
#endif
    for (tmp = me->prev; tmp; tmp = tmp->prev) {
        killThread(tmp, kill);
    }

    for (tmp = me->next; tmp; tmp = tmp->next) {
        killThread(tmp, kill);
    }
}
        
void PR_ProcessExit(PRIntn status) {
    /* Let the atexit() call PR_Cleanup() */
    killThreads(PR_TRUE);
    exit(status);
}

static PRThread *primordialThread = NULL;

void _MD_Early_Init(void) {
    PRThread *thread;

    thread = PR_NEWZAP(PRThread);
    primordialThread = thread;
    thread->p = (struct Process *)FindTask(NULL);
    thread->parent = NULL;
    thread->p->pr_Task.tc_UserData = thread;
    _InitThread(thread);

#ifdef DEBUG_ATHREADS
    printf("Primorial Thread %lx\n", thread);
    fflush(stdout);
#endif

    setvbuf(stdout, NULL, _IONBF, 0);
    atexit(_MD_Exit);
    atexit(PR_Cleanup);
    _PR_InitSocket();
    _PR_InitRandom();
}

PR_IMPLEMENT(PRStatus) PR_Interrupt(PRThread *thread) {
    PRThread *me = PR_CurrentThread();
    char buf[50];
    struct MsgPort *port;
    sprintf(buf, "NSPRPORT-%lx\n", thread);

    /* See if the thread is still around by trying to 
     * look for its public message port 
     */

#ifdef DEBUG_ATHREADS
    printf("%lx Interrupting thread %lx with %lx, flags are now %lx\n", me, thread, (1 << thread->interruptSignal), thread->flags);
#endif

    Forbid();
    port = FindPort(buf);
    if (port != NULL) {
        thread->flags |= _PR_INTERRUPT;
        if (me != thread) {
            Signal((struct Task *)thread->p, 1 << thread->interruptSignal);
        }
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
        (struct timerequest *)CreateIORequest(pr->port, sizeof(struct timerequest));    
    PR_ASSERT(pr->sleepRequest);

    if (OpenDevice(TIMERNAME, UNIT_VBLANK, 
                   (struct IORequest *)pr->sleepRequest, 0)) {
        PR_ASSERT(PR_FALSE);
    }

    pr->AmiTCP_Base = OpenLibrary("bsdsocket.library", 0);

    PR_INIT_CLIST(&pr->lockList);
    /* Just in case */
    PR_INIT_CLIST(&pr->waitQLinks);

    return PR_SUCCESS;
}


/**
 * Clean up the NSPR-specific thread objects
 */
static void procExit(PRThread *me) {  

    PRThread *join;

    Forbid();
    RemPort(me->port);
    join = me->join;

    me->state = _PR_DEAD_STATE;
    Permit();

    _PR_DestroyThreadPrivate(me);
    PR_Free(me->port->mp_Node.ln_Name);
    DeleteMsgPort(me->port);
    DeleteMsgPort(me->selectPort);
    FreeSignal(me->interruptSignal);

    /* NOTE:
     * I can only AbortIO an IORequest only if the structure has
     * been used at keast once.
     */
    if (me->sleepRequestUsed && 
        !(CheckIO((struct IORequest *)me->sleepRequest))) {
        AbortIO((struct IORequest *)me->sleepRequest);
        WaitIO((struct IORequest *)me->sleepRequest);
    }
    CloseDevice((struct IORequest *)me->sleepRequest);
    DeleteIORequest((struct IORequest *)me->sleepRequest);
    if (me->AmiTCP_Base != NULL)
        CloseLibrary(me->AmiTCP_Base);

    if (join != NULL) {
#ifdef DEBUG_ATHREADS
        printf("%lx done, signalling parent %lx,state is %d\n", me, join, join->state);
        fflush(stdout);
#endif
        PR_ASSERT(join->state == _PR_JOIN_WAIT);
        _PR_MD_Signal(join);
    }    
    /* Don't free me here since other people may be using me
     * let the memory allocater at the end handle it
     * PR_Free(me);
     */
    if (primordialThread != me) {
        UnregisterThread(me->p);
    }
}

/**
 * First code called when the thread starts
 */
static void 
#if 0
__attribute__((saveds))
#endif
procEntry(void) {
    /* It may be possible for me to start (and restore a4) before the parent
     * can register my thread. That is why I have a local copy of SysBase
     * and DOSBase here -- so I don't reference any a4-relative variables
     */
    PRThread *pr;
    struct ExecBase *SysBase = *(struct ExecBase **)4L;
    struct Library *DOSBase = OpenLibrary("dos.library", 0);

    /* Hack. I need to wait for the parent to initialize some things for me */
    Wait(SIGBREAKF_CTRL_F);

    pr = PR_GetCurrentThread();
    _InitThread(pr);
    /* We are done initialization, signal the parent */
    PR_ASSERT(pr->parent->state == _PR_SUSPENDED);
    _PR_MD_Signal(pr->parent);
    if (setjmp(pr->jmpbuf) == 0) {
        pr->startFunc(pr->arg);
    } else {
        /* Remove anything I was waiting on */
        Forbid();
        PR_REMOVE_LINK(&pr->waitQLinks);
        Permit();
    }
    procExit(pr);
    CloseLibrary(DOSBase);
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
    thread->threadState = state;

    if (stackSize < 32768) stackSize = 32768;

    Forbid();
    thread->parent = me;
    /* Add this thread to our list of threads */
    thread->next = me->next;
    if (me->next) {
        me->next->prev = thread;
    }        
    me->next = thread;
    thread->prev = me;

    thread->p = CreateNewProcTags(NP_StackSize, stackSize,
                                  NP_Name, "NSPR Thread",
                                  NP_Input, Input(),
                                  NP_Output, Output(),
                                  NP_CloseInput, FALSE,
                                  NP_CloseOutput, FALSE,
                                  NP_Priority, _PR_Map_Priority(priority),
                                  NP_CloseError, FALSE,
                                  NP_Entry, (ULONG)procEntry);

    if(thread->p != NULL) {
        /*
         * Need to register the a4 context for the thread
         */
        RegisterThread(thread->p, primordialThread->p);

        thread->p->pr_Task.tc_UserData = thread;
        /* Hack for ixemul.library to work */
        thread->p->pr_Task.tc_TrapCode = me->p->pr_Task.tc_TrapCode;
        thread->p->pr_Task.tc_TrapData = me->p->pr_Task.tc_TrapData;

        /* Put this before signal just in case */
        me->state = _PR_SUSPENDED;        

        /* Hack because the new thread is waiting for us to do this */
        Signal((struct Task *)thread->p, SIGBREAKF_CTRL_F); 
        /* Need to wait for the other thread to do some init so there
         * isn't a race condition when we do a PR_CreateThread and do 
         * a PR_JoinThread before the thread comes up fully 
         */
        _PR_MD_Wait(me, PR_FALSE, PR_TRUE);
        me->state = _PR_RUNNING;

    } else {
        PR_Free(thread);
        thread = NULL;
    }
    Permit();

#ifdef DEBUG_ATHREADS
    printf("CreateThread(%lx) created thread %lx(%lx)\n", me, thread, thread->p);
    fflush(stdout);
#endif
    return thread;
}

PR_IMPLEMENT(PRThread*) PR_GetCurrentThread(void) {
    struct Process *p = (struct Process *)FindTask(NULL);
    return (PRThread *)p->pr_Task.tc_UserData;
}


PR_IMPLEMENT(PRStatus) PR_JoinThread(PRThread *thread) {
    return PR_JoinThreadInternal(thread, PR_FALSE);
}

static PRStatus PR_JoinThreadInternal(PRThread *thread, 
    PRBool allowJoinsOnUnjoinableThreads) {
    PRThread *me = PR_GetCurrentThread();
    char buf[50];
    struct MsgPort *port;
  
    if (thread->threadState == PR_UNJOINABLE_THREAD && 
        !allowJoinsOnUnjoinableThreads)
        return PR_FAILURE;

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
    me->state = _PR_JOIN_WAIT;
    thread->join = me;
    /*
     * Don't clear the signal since the thread may finish by the
     * time I get to waiting
     */
    _PR_MD_Wait(me, PR_FALSE, PR_FALSE);
    Permit();

    me->state = _PR_RUNNING;
    return PR_SUCCESS;
}

PR_IMPLEMENT(void) PR_SetConcurrency(PRUintn numCPUs) {
    /* Nothing to do */
}

PR_IMPLEMENT(void) PR_SetThreadPriority(PRThread *thread, PRThreadPriority priority) {
    thread->priority = priority;
    SetTaskPri((struct Task *)thread->p, _PR_Map_Priority(priority));
}

PR_IMPLEMENT(PRThreadPriority) PR_GetThreadPriority(const PRThread *thred)
{
    PR_ASSERT(thred != NULL);
    return thred->priority;
}  /* PR_GetThreadPriority */


PR_IMPLEMENT(void) PR_ClearInterrupt(void)
{
    PRThread *me = PR_CurrentThread();
    SetSignal(0, 1 << me->interruptSignal);
    me->flags &= ~_PR_INTERRUPT;
#ifdef DEBUG_ATHREADS
    printf("Clearing interrupt for %lx, flags are now %lx\n", me, me->flags);
#endif

}  /* PR_ClearInterrupt */


PR_IMPLEMENT(PRBool) PR_IsInterruptsBlocked(void)
{
    PRThread *me = PR_CurrentThread();
    PRBool retval;
    retval = (me->flags & _PR_INTERRUPT_BLOCKED) ? PR_TRUE : PR_FALSE;
    return retval;
}

PR_IMPLEMENT(void) PR_BlockInterrupt(void)
{
    PRThread *me = PR_CurrentThread();
    _PR_THREAD_BLOCK_INTERRUPT(me);
}  /* PR_BlockInterrupt */

PR_IMPLEMENT(void) PR_UnblockInterrupt(void)
{
    PRThread *me = PR_CurrentThread();
    _PR_THREAD_UNBLOCK_INTERRUPT(me);
}  /* PR_UnblockInterrupt */


void _PR_InitThreads(PRThreadType type, PRThreadPriority priority, 
    PRUintn maxPTDs)
{
    /* Nothing to do */
}



void _PR_InitStacks(void) {
}

void _MD_Exit(void) {
#ifdef DEBUG_ATHREADS
    Printf("_MD_Exit\n");
    Flush(Output());
#endif
    if (_pr_initialized) {
        /* I need to kill the socket thread before killing off
         * all of the other threads
         */
        _PR_CleanupSocket();
        _PR_CleanupRandom();
        killThreads(PR_TRUE);
        /* Clean up primorial thread */
        procExit(primordialThread);
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
        _PR_Release_Memory();
        _pr_initialized = PR_FALSE;
    }
}

PR_IMPLEMENT(PRStatus) PR_Cleanup(void)
{
    PRThread *me = PR_CurrentThread();
    if (me != primordialThread) {
        return PR_FAILURE;
    }
    killThreads(PR_FALSE);
    return PR_SUCCESS;
}  /* PR_Cleanup */

void _PR_MD_Wait(PRThread *thread, PRBool interruptable, PRBool clearSignal) {
    ULONG mySig = 1 << thread->port->mp_SigBit;

    /* See if someone is trying to kill me by setting my state to dead */
    if (thread->state == _PR_DEAD_STATE) {
#ifdef DEBUG_ATHREADS
        printf("Thread %x was forceably killed[1]\n", thread);
#endif
        longjmp(thread->jmpbuf, 1);
    }

    Forbid();
    if (clearSignal)
        SetSignal(0, mySig);
    if (interruptable == PR_TRUE) {
        ULONG interruptSig =  1 << thread->interruptSignal;
        ULONG sigs = mySig | interruptSig;
        PR_ASSERT(thread->state != _PR_RUNNING);
        Wait(sigs);
    } else {        
        Wait(mySig);
    }
    SetSignal(0, mySig);
    Permit();

    /* See if someone is trying to kill me by setting my state to dead */
    if (thread->state == _PR_DEAD_STATE) {
#ifdef DEBUG_ATHREADS
        printf("Thread %x was forceably killed[2]\n", thread);
#endif
        longjmp(thread->jmpbuf, 1);
    }
}

void _PR_MD_Signal(PRThread *thread) {
    Signal((struct Task *)thread->p, 1 << thread->port->mp_SigBit);
}

PR_IMPLEMENT(PRThreadScope) PR_GetThreadScope(const PRThread *thread) {
    return PR_GLOBAL_THREAD;
}


PR_IMPLEMENT(PRInt32) PR_GetThreadAffinityMask(PRThread *thread, PRUint32 *mask) {
    return 0;  /* not implemented */
}

PR_IMPLEMENT(PRInt32) PR_SetThreadAffinityMask(PRThread *thread, PRUint32 mask ) {
    return 0;  /* not implemented */
}

PR_IMPLEMENT(PRThreadState) PR_GetThreadState(const PRThread *thred)
{
    return thred->threadState;
}  /* PR_GetThreadState */


/*
 * Structure used by the polling thread to monitor pipes
 */
struct _MDPipePoll {
    PRPollDesc pollfds[3];  /* the fds to read with PR_Poll */
    PRIntn numfds;          /* number of fds to poll (max 3) */
    PRFileDesc *pipefds[3]; /* the corresponding write fds to write to */
};

/*
 * Thread which watches the file descriptors and pipes them to the
 * running process
 */
static void _MDPollThread(void *arg) {
    struct _MDPipePoll *mpp = (struct _MDPipePoll *)arg;
    int i;
    PRIntn numfds;
    PRBool done = PR_FALSE;
#ifdef DEBUG_ATHREADS
    printf("FD polling thread started, numfds is %d\n", mpp->numfds);
#endif
    while (!done) {
        char chr[1024];
        numfds = PR_Poll(mpp->pollfds, mpp->numfds, PR_INTERVAL_NO_TIMEOUT);
#ifdef DEBUG_ATHREADS
        printf("Poll returns %d\n", numfds);
#endif
        if (numfds < 0) {
            done = PR_TRUE;
            break;
        }

        for (i = 0; i < mpp->numfds; i++) {
            if (mpp->pollfds[i].out_flags & PR_POLL_READ) {
                PRIntn num;
                num = PR_Read(mpp->pollfds[i].fd, chr, sizeof(chr));
                if (num <= 0) {
                    done = PR_TRUE;
                } else {
                    num = PR_Write(mpp->pipefds[i], chr, num);
                }
            } else if (mpp->pollfds[i].out_flags & PR_POLL_EXCEPT) {
                done = TRUE;
            }
        }
    }
}

static void _MDCreateProcessThread(void *arg) {
    PRProcess *pr = (PRProcess *)arg;
    LONG returnCode;
    struct Process *me = (struct Process *)FindTask(NULL);
    char *cmdLine;
    size_t cmdLen = 0;
    struct TagItem items[10];
    struct _MDPipePoll *mpp;
    PRFileDesc *pipes[6] = {NULL,};
    PRIntn pipefd = 0;
    PRThread *pollThread;
    int i;

    PR_Lock(pr->md.lock);

    for (i = 0; pr->md.argv[i]; i++) {
        cmdLen += strlen(pr->md.argv[i]) + 4;
    }

    cmdLine = PR_Malloc(cmdLen);
    if (cmdLine == NULL) {
        pr->md.returnCode = 255;
        return;
    } 

    cmdLine[0] = '\0';
    for (i = 0; pr->md.argv[i]; i++) {
        if (i > 0)
            strcat(cmdLine, " ");
        strcat(cmdLine, "\"");
        strcat(cmdLine, pr->md.argv[i]);
        strcat(cmdLine, "\"");
    }

    /* Set up the environment */
    if (pr->md.envp != NULL) {
        for (i = 0; pr->md.envp[i]; i++) {
            char *equal;
            char *tmpenv = PR_Malloc(strlen(pr->md.envp[i]) + 1);
            /* Error check */
            strcpy(tmpenv, pr->md.envp[i]);
            equal = strchr(tmpenv, '=');
            if (equal) {
                *equal++ = '\0';
#ifdef DEBUG_ATHREADS
                printf("Setting env: %s to %s\n", tmpenv, equal);
#endif
                SetVar(tmpenv, equal, strlen(equal), GVF_LOCAL_ONLY);
            }
            PR_Free(tmpenv);
        }
    }


    /* Error */
    mpp = PR_NEWZAP(struct _MDPipePoll);
    mpp->numfds = 0;
    i = 0;
    if (pr->md.attr) {
        if (pr->md.attr->fdInheritBufferUsed > 0) {
            char *equal;
            char *tmpenv = PR_Malloc(pr->md.attr->fdInheritBufferUsed + 1);
            /* Error check */
#ifdef DEBUG_ATHREADS
            printf("inheritbuffer is %s\n", pr->md.attr->fdInheritBuffer);
#endif
            strcpy(tmpenv, pr->md.attr->fdInheritBuffer);
            equal = strchr(tmpenv, '=');
            if (equal) {
                *equal++ = '\0';
#ifdef DEBUG_ATHREADS
                printf("Setting env: %s to %s\n", tmpenv, equal);
#endif
                SetVar(tmpenv, equal, strlen(equal), GVF_LOCAL_ONLY);
            }
            PR_Free(tmpenv);
        }

        if (pr->md.attr->stdinFd) {
            PRFileDesc *pipein, *pipeout;
            PR_CreatePipe(&pipein, &pipeout);
            pipes[pipefd++] = pipein;
            pipes[pipefd++] = pipeout;
            mpp->pollfds[mpp->numfds].fd = pr->md.attr->stdinFd;
            mpp->pollfds[mpp->numfds].in_flags = PR_POLL_READ;
            mpp->pipefds[mpp->numfds++] = pipeout;
            items[i].ti_Tag = NP_CloseInput;
            items[i++].ti_Data = TRUE;
            items[i].ti_Tag = SYS_Input;
            items[i++].ti_Data = pipein->secret->md.osfd;
        } else {
            items[i].ti_Tag = NP_CloseInput;
            items[i++].ti_Data = FALSE;
            items[i].ti_Tag = SYS_Input;
            items[i++].ti_Data = Input();
        }

        if (pr->md.attr->stdoutFd) {
            PRFileDesc *pipein, *pipeout;
            PR_CreatePipe(&pipein, &pipeout);
            pipes[pipefd++] = pipein;
            pipes[pipefd++] = pipeout;
            mpp->pollfds[mpp->numfds].fd = pipein;
            mpp->pollfds[mpp->numfds].in_flags = PR_POLL_READ;
            mpp->pipefds[mpp->numfds++] = pr->md.attr->stdoutFd;
            items[i].ti_Tag = NP_CloseOutput;
            items[i++].ti_Data = TRUE;
            items[i].ti_Tag = SYS_Output;
            items[i++].ti_Data = pipeout->secret->md.osfd;
        } else {
            items[i].ti_Tag = NP_CloseOutput;
            items[i++].ti_Data = FALSE;
            items[i].ti_Tag = SYS_Output;
            items[i++].ti_Data = Output();
        }

        if (pr->md.attr->stderrFd) {
            PRFileDesc *pipein, *pipeout;
            PR_CreatePipe(&pipein, &pipeout);
            pipes[pipefd++] = pipein;
            pipes[pipefd++] = pipeout;

            mpp->pollfds[mpp->numfds].fd = pipein;
            mpp->pollfds[mpp->numfds].in_flags = PR_POLL_READ;
            mpp->pipefds[mpp->numfds++] = pr->md.attr->stderrFd;
            items[i].ti_Tag = NP_CloseError;
            items[i++].ti_Data = TRUE;
            items[i].ti_Tag = NP_Error;
            items[i++].ti_Data = pipeout->secret->md.osfd;
        } else {
            if (me->pr_CES) {
                items[i].ti_Tag = NP_CloseError;
                items[i++].ti_Data = FALSE;
                items[i].ti_Tag = NP_Error;
                items[i++].ti_Data = me->pr_CES;
            } else {
                items[i].ti_Tag = NP_CloseError;
                items[i++].ti_Data = TRUE;
                items[i].ti_Tag = NP_Error;
                items[i++].ti_Data = Open("*", MODE_OLDFILE);
            }
        }

        if (pr->md.attr->currentDirectory) {
            items[i].ti_Tag = NP_CurrentDir;
            items[i++].ti_Data = (ULONG)pr->md.attr->currentDirectory;
        }
    } else {
        items[i].ti_Tag = NP_CloseInput;
        items[i++].ti_Data = FALSE;
        items[i].ti_Tag = NP_CloseOutput;
        items[i++].ti_Data = FALSE;
        items[i].ti_Tag = SYS_Input;
        items[i++].ti_Data = Input();
        items[i].ti_Tag = SYS_Output;
        items[i++].ti_Data = Output();
        items[i].ti_Tag = NP_CloseError;
        items[i++].ti_Data = (me->pr_CES) ? FALSE : TRUE;
        items[i].ti_Tag = NP_Error;
        items[i++].ti_Data = me->pr_CES ? me->pr_CES : Open("*", MODE_OLDFILE);
    }
        
    items[i].ti_Tag = TAG_DONE;
    items[i].ti_Data = TAG_DONE;

    PR_NotifyAllCondVar(pr->md.condVar);
    PR_Unlock(pr->md.lock);

    if (mpp->numfds > 0) {
        pollThread = PR_CreateThread(PR_SYSTEM_THREAD, 
            _MDPollThread, mpp, PR_PRIORITY_NORMAL, PR_LOCAL_THREAD, 
            PR_JOINABLE_THREAD, 0);
    } else {
        PR_Free(mpp);
    }

#ifdef DEBUG_ATHREADS
    printf("Spawning '%s'\n", cmdLine);
#endif

    returnCode = SystemTagList(cmdLine, items);
    if (!_PR_PENDING_INTERRUPT(PR_CurrentThread())) {
        pr->md.returnCode = returnCode;
    }
    PR_Free(cmdLine);
    PR_JoinThread(pollThread);
    for (i = 0; i < pipefd; i++) {
        PR_Close(pipes[i]);
    }
}

PRProcess *_CreateProcess(const char *path, char *const *argv,
    char *const *envp, const PRProcessAttr *attr) {
    PRProcess *retval = PR_NEWZAP(PRProcess);
    PRLock *lock = NULL;
    PRCondVar *cv = NULL;
    if (retval == NULL) {
        PR_SetError(PR_OUT_OF_MEMORY_ERROR, 0);
        goto error;
    }

    lock = retval->md.lock = PR_NewLock();
    if (lock == NULL) {
        PR_SetError(PR_OUT_OF_MEMORY_ERROR, 0);
        goto error;
    }

    cv = retval->md.condVar = PR_NewCondVar(lock);
    if (cv == NULL) {
        PR_SetError(PR_OUT_OF_MEMORY_ERROR, 0);
        goto error;
    }

    PR_Lock(lock);

    retval->md.argv = argv;
    retval->md.envp = envp != NULL ? envp : NULL;
    retval->md.attr = attr;

    /* Since SystemTags() waits until it is done,
     * spawn it off on another thread
     */
    retval->md.executeThread = PR_CreateThread(PR_SYSTEM_THREAD, 
        _MDCreateProcessThread, retval, PR_PRIORITY_NORMAL, PR_LOCAL_THREAD, 
        PR_JOINABLE_THREAD, 0);

    /*
     * Wait until the process thread is done with the PRProcessAttr
     */
    PR_WaitCondVar(cv, PR_INTERVAL_NO_TIMEOUT);
    PR_Unlock(lock);
    PR_DestroyCondVar(cv);
    PR_DestroyLock(lock);

    return retval;
error:
    if (cv != NULL) {
        PR_DestroyCondVar(cv);
    }

    if (lock != NULL) {
        PR_DestroyLock(lock);
    }

    PR_FREEIF(retval);
    return NULL;
}


PRStatus _WaitProcess(PRProcess *process, PRInt32 *exitCode) {
    PR_JoinThread(process->md.executeThread);
    if (exitCode != NULL)
        *exitCode = process->md.returnCode;

    PR_Free(process);
    return PR_SUCCESS;
}

PRStatus _DetachProcess(PRProcess *process) {
    /* Maybe wait to free up process?? */
    PR_Interrupt(process->md.executeThread);
    PR_Free(process);
    return PR_SUCCESS;
}

PRStatus _KillProcess(PRProcess *process) {
    /* I don't think this can be done */
    return PR_SUCCESS;
}

PR_IMPLEMENT(void) PR_SetThreadRecycleMode(PRUint32 count) {
    /* Does nothing */
}

void _MD_INIT_IO(void) {
}
