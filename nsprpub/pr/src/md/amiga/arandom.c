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

/* Code dealing with random numbers */

/* CondVars and locks guarding randomdata/front/back
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

volatile int data[5];
volatile int num = 0;

/* Input handler which does gathers the data and signals the 
 * InputEventThread
 * Input - a0 - InputEvent structure
 * Input - a1 - use data (in my case the Process of the InputEventThread)
 * Output - d0 the new InputEvent structure (it is always the same as the input)
 */
static struct InputEvent *InputEventHandler(void) {
    register struct InputEvent *ie __asm("a0");
	struct InputEvent *ie2 = ie;
    register struct Process *p __asm("a1");
    register struct InputEvent *retval __asm("d0");
    int pos = 0;
    while (ie && pos < 5) {
		switch (ie->ie_Class) {
		case IECLASS_RAWKEY:
			data[pos] = ie->ie_Code | (int)ie->ie_position.ie_addr;
		default:				
			data[pos] = (int)ie->ie_position.ie_addr;
		}
        ie = ie->ie_NextEvent;
		if (data[pos])
			pos++;
    }

	if (pos) {
		num = pos;
		Signal((struct Task *)p, SIGBREAKF_CTRL_F);
	}
	retval = ie2;
	return retval;
}
        

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
        CreateExtIO(mp, sizeof(struct IOStdReq));
    struct Interrupt *ie = PR_NEWZAP(struct Interrupt);
	PRThread *me = PR_CurrentThread();

    OpenDevice("input.device", 0, (struct IORequest *)io, 0);
    
    ie->is_Code = InputEventHandler;
    ie->is_Data = me->p;
    ie->is_Node.ln_Pri = 100;
    ie->is_Node.ln_Name = "NSPR Input/Random handler";

    io->io_Data = (APTR)ie;
    io->io_Command = IND_ADDHANDLER;
    DoIO((struct IORequest *)io);

	printf("Added event handler\n");
    while (!done) {
        int mynum;
        int mydata[5];
		int i;
		ULONG flags = (1 << me->port->mp_SigBit) | SIGBREAKF_CTRL_F;

        me->state = _PR_IO_WAIT;
		flags = Wait(flags);
        me->state = _PR_RUNNING;
		if (flags & 1 << me->port->mp_SigBit) {
			printf("event thread got interrupted\n");
			done = PR_TRUE;
			break;
		}
        Disable();
		SetSignal(0, flags);
        /* Make a copy of the data to be safe */
        mynum = num;
        memcpy(mydata, data, sizeof(mydata));
        Enable();

		printf("Got %d pieces of random data\n", mynum);
        PR_Lock(listLock);
		for (i = 0; i < mynum; i++) {
			int j;
			int d = mydata[i];
			for (j = 0; j < 4; j++) {

				while ((front - back % BUFFERSIZE) == BUFFERSIZE -1) {
					printf("Full, waiting\n");
					if (PR_WaitCondVar(fullcv, PR_INTERVAL_NO_TIMEOUT) == PR_FAILURE) {
						printf("Wait for full interrupted %d\n", PR_GetError());

						done = PR_TRUE;
						break;
					}
				}
				printf("SEtting databuffer %d to %d\n", front, (int)(d & 0xff));
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

    if (!CheckIO(io))
        AbortIO(io);
    WaitIO(io);
    CloseDevice(io);
	DeleteExtIO(io);
	DeleteMsgPort(mp);
	printf("random thread done \n");
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

    printf("Eventthread %lx, fullcv %lx, emptycv %lx\n", eventThread, fullcv, emptycv);
}

void _PR_CleanupRandom(void) {
	printf("Waiting for event thread\n");
    PR_Interrupt(eventThread);
	_PR_MD_Signal(eventThread);

	PR_JoinThread(eventThread);
	printf("Done waiting for event thread\n");
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
    PR_Lock(listLock);
	while (size) {
		while ((front - back) % BUFFERSIZE == 0) {
			printf("Buffer empty, waiting...\n");
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
