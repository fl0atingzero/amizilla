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
#include <devices/inputevent.h>
#include <devices/input.h>
#include <exec/interrupts.h>

/* #define DEBUG_ARANDOM */

/* Code dealing with random numbers */

/* CondVars and locks guarding randomdata/front/back */
static PRLock *listLock;
static PRCondVar *fullcv;
static PRCondVar *emptycv;
static PRThread *eventThread;

#define BUFFERSIZE 100
static char randomdata[BUFFERSIZE];
/* Front of the list -- items are added here */
static int front = 0;
/* Back of the list -- items are removed here */
static int back = 0;

/* Architecture 
 * I install a highest priority input handler which just gathers the data
 * and notifies the thread with the data 
 * That thread fills up the queue until its full then waits
 * The random callers can empty the random data
 */

struct InputEvent *InputEventHandler(struct InputEvent *ie __asm("a0"), struct Process *p __asm("a1"));

static struct InputData ip;
/*
 * NSPR Input Event thread
 * Gets the data from InputEventHandler and just stores it
 * in a static-length buffer. If the buffer gets full, then
 * it waits
 */
static void InputEventThread(void *ignored) {
    PRBool done = PR_FALSE;
    struct MsgPort *mp = CreateMsgPort();
    struct IOStdReq *io = (struct IOStdReq *)
        CreateIORequest(mp, sizeof(struct IOStdReq));
    struct Interrupt *ie = PR_NEWZAP(struct Interrupt);
	PRThread *me = PR_CurrentThread();

    OpenDevice("input.device", 0, (struct IORequest *)io, 0);
    
    ip.p = me->p;
    ie->is_Code = (VOID *)InputEventHandler;
    ie->is_Data = &ip;
    ie->is_Node.ln_Pri = 100;
    ie->is_Node.ln_Name = "NSPR Input/Random handler";

    io->io_Data = (APTR)ie;
    io->io_Command = IND_ADDHANDLER;
    DoIO((struct IORequest *)io);

#ifdef DEBUG_ARANDOM
	printf("Added event handler\n");
#endif
    while (!done) {
        int mynum;
        int mydata[5];
		int i;
		ULONG flags = (1 << me->port->mp_SigBit) | SIGBREAKF_CTRL_F;

        me->state = _PR_IO_WAIT;
		flags = Wait(flags);
        me->state = _PR_RUNNING;
		if (flags & 1 << me->port->mp_SigBit) {
#ifdef DEBUG_ARANDOM
			printf("event thread got interrupted\n");
#endif
			done = PR_TRUE;
			break;
		}
        Disable();
		SetSignal(0, flags);
        /* Make a copy of the data to be safe */
        mynum = ip.num;
        memcpy(mydata, ip.data, sizeof(mydata));
        Enable();

#ifdef DEBUG_ARANDOM
		printf("Got %d pieces of random data\n", mynum);
        fflush(stdout);
#endif
        PR_Lock(listLock);
		for (i = 0; i < mynum; i++) {
			int j;
			int d = mydata[i];
            int previous;
			for (j = 0; j < 4; j++) {

				while ((front - back % BUFFERSIZE) == BUFFERSIZE -1) {
#ifdef DEBUG_ARANDOM
					printf("Full, waiting\n");
#endif
					if (PR_WaitCondVar(fullcv, PR_INTERVAL_NO_TIMEOUT) == PR_FAILURE) {
#ifdef DEBUG_ARANDOM
						printf("Wait for full interrupted %d\n", PR_GetError());
#endif

						done = PR_TRUE;
						break;
					}
				}
#ifdef DEBUG_ARANDOM
				printf("Setting databuffer %d to %d\n", front, (int)(d & 0xff));
#endif
                d = d ^ previous;
                previous = d;
				randomdata[front] = d & 0xff;
				d >>= 8;
				front = (front + 1) % BUFFERSIZE;
				PR_NotifyCondVar(emptycv);
                
			}
		}
        PR_Unlock(listLock);
	}
			
    io->io_Data = ie;
    io->io_Command = IND_REMHANDLER;
    DoIO((struct IORequest *)io);

    if (!CheckIO((struct IORequest *) io))
        AbortIO((struct IORequest *) io);
    WaitIO((struct IORequest *) io);
    CloseDevice((struct IORequest *) io);
	DeleteIORequest((struct IORequest *) io);
	DeleteMsgPort(mp);
#ifdef DEBUG_ARANDOM
	printf("random thread done \n");
#endif
}

void _PR_InitRandom(void) {
    listLock = PR_NewLock();
    PR_ASSERT(listLock);
	emptycv = PR_NewCondVar(listLock);
	PR_ASSERT(emptycv);
	fullcv = PR_NewCondVar(listLock);
	PR_ASSERT(fullcv);
	eventThread = PR_CreateThread(PR_SYSTEM_THREAD, InputEventThread, NULL, PR_PRIORITY_HIGH, PR_LOCAL_THREAD, PR_JOINABLE_THREAD, 0);
	PR_ASSERT(eventThread);
	eventThread->daemon = PR_TRUE;

#ifdef DEBUG_ARANDOM
    printf("Eventthread %lx, fullcv %lx, emptycv %lx\n", eventThread, fullcv, emptycv);
#endif
}

void _PR_CleanupRandom(void) {
#ifdef DEBUG_ARANDOM
	printf("Waiting for event thread\n");
#endif
    PR_Interrupt(eventThread);
	_PR_MD_Signal(eventThread);

	PR_JoinThread(eventThread);
#ifdef DEBUG_ARANDOM
	printf("Done waiting for event thread\n");
#endif
    PR_DestroyCondVar(emptycv);
	PR_DestroyCondVar(fullcv);
    PR_DestroyLock(listLock);
}

/*
 * Fill in the buffer with random data, waiting if
 * there needs to be random data generated
 */
PRSize _PR_MD_GetRandomNoise( void *buf, PRSize size ) {
	PRSize retval = size;

#ifdef DEBUG_ARANDOM
    printf("Getting %ld bytes of random noise\n");
    fflush(stdout);
#endif
    PR_Lock(listLock);
	while (size) {
		while ((front - back) % BUFFERSIZE == 0) {
#ifdef DEBUG_RANDOM
			printf("Buffer empty, waiting...\n");
            fflush(stdout);
#endif
			PR_WaitCondVar(emptycv, PR_INTERVAL_NO_TIMEOUT);
		}
		((char *)buf)[size-1] = randomdata[back];
		back = (back + 1) % BUFFERSIZE;
		PR_NotifyCondVar(fullcv);
		size--;
	}
    PR_Unlock(listLock);
	return retval;
}
