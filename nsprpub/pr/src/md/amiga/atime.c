/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
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
#include <devices/timer.h>
#include <proto/timer.h>

static PRUint32 ticksPerSec = 1000;

_PRInterruptTable _pr_interruptTable[] = {NULL,};



_PR_MD_Timeout _PR_Sleep(PRIntervalTime timeout) {

  PRThread *thread = PR_GetCurrentThread();
  struct timerequest *timerIO = thread->sleepRequest;
  _PR_MD_Timeout retval = FAILURE;
  struct Message *msg;

  if (timeout == PR_INTERVAL_NO_TIMEOUT)
    goto done;

  thread->sleep = timeout;

  timerIO->tr_node.io_Command = TR_ADDREQUEST;

  timerIO->tr_time.tv_secs = timeout / _PR_MD_INTERVAL_PER_SEC();
  timerIO->tr_time.tv_micro = timeout % _PR_MD_INTERVAL_PER_SEC();

  //PR_fprintf(PR_STDERR,"%lx, Beginning IO for sleep\n", thread);
  SendIO((struct IORequest *)timerIO);
  //PR_fprintf(PR_STDERR,"%lx, done begin io %lx\n", thread, thread->port);
  thread->state = _PR_SUSPENDED;
  _PR_MD_Wait(thread);
  retval = (thread->state == _PR_RUNNING) ? SUCCESS : TIMEDOUT;
  //PR_fprintf(PR_STDERR,"%lx, done waiting\n", thread);
  thread->state = _PR_RUNNING;

  msg = GetMsg(thread->port);

  // PR_fprintf(PR_STDERR,"%lx, got msg %lx\n", thread, msg);
  if (!(CheckIO((struct IORequest *)timerIO))) {
    //PR_fprintf(PR_STDERR,"%lx abort io\n", thread);
    AbortIO((struct IORequest *)timerIO);
    //PR_fprintf(PR_STDERR,"%lx wait IO\n", thread);
    WaitIO((struct IORequest *)timerIO);
  }

done:
  //PR_fprintf(PR_STDERR,"%lx done sleep returning\n", thread);
  return retval;
}

PR_IMPLEMENT(PRStatus) PR_Sleep(PRIntervalTime timeout) { 
  _PR_MD_Timeout retval = _PR_Sleep(timeout);
  return (retval == SUCCESS || retval == TIMEDOUT) ? PR_SUCCESS : PR_FAILURE;
}

void _MD_Interval_Init(void) {
  struct timerequest *tr = 
    AllocMem(sizeof(struct timerequest), MEMF_CLEAR| MEMF_PUBLIC);

  if (!(OpenDevice(TIMERNAME, UNIT_ECLOCK, (struct IORequest *)tr, 0))) {
    struct timeval tv;
    struct EClockVal ec;
    struct Library *TimerBase = (struct Library *)tr->tr_node.io_Device;
    ticksPerSec = ReadEClock(&ec);
    CloseDevice((struct IORequest *)tr);
  }
  FreeMem(tr, sizeof(struct timerequest));
}

PRIntervalTime _MD_Interval_Per_Sec(void) {
  return ticksPerSec;
}

PRIntervalTime _MD_Get_Interval(void) {
  PRIntervalTime retval = 0;
  struct timerequest *tr = 
    AllocMem(sizeof(struct timerequest), MEMF_CLEAR| MEMF_PUBLIC);

  if (!(OpenDevice(TIMERNAME, UNIT_ECLOCK, (struct IORequest *)tr, 0))) {
    struct timeval tv;
    struct EClockVal ec;
    struct Library *TimerBase = (struct Library *)tr->tr_node.io_Device;
    ReadEClock(&ec);
    retval = ec.ev_lo;
    CloseDevice((struct IORequest *)tr);
  }
  FreeMem(tr, sizeof(struct timerequest));
  return retval;
}


PR_IMPLEMENT(PRTime)
PR_Now(void)
{
  PRTime retval = 0;
  struct timerequest *tr = 
    AllocMem(sizeof(struct timerequest), MEMF_CLEAR| MEMF_PUBLIC);

  if (!(OpenDevice(TIMERNAME, UNIT_MICROHZ, (struct IORequest *)tr, 0))) {
    struct timeval tv;
    struct Library *TimerBase = (struct Library *)tr->tr_node.io_Device;
    GetSysTime(&tv);
    retval = tv.tv_sec << 32 | tv.tv_usec;
    CloseDevice((struct IORequest *)tr);
  }
  FreeMem(tr, sizeof(struct timerequest));
  return retval;

}

