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

static _PR_MD_Timeout _PR_Sleep(PRIntervalTime timeout) {

    PRThread *thread = PR_GetCurrentThread();
    struct timerequest *timerIO = thread->sleepRequest;
    _PR_MD_Timeout retval = FAILURE;
    struct Message *msg;

    if (timeout == PR_INTERVAL_NO_TIMEOUT)
        goto done;

    if (_PR_PENDING_INTERRUPT(thread)) {
        printf("%lx sleep got a pending interrupt\n", thread);
        PR_ClearInterrupt();
        PR_SetError(PR_PENDING_INTERRUPT_ERROR, 0);
        return INTERRUPTED;
    }

    if (thread->state == _PR_RUNNING)
        thread->state = _PR_SUSPENDED;

    timerIO->tr_node.io_Command = TR_ADDREQUEST;

    timerIO->tr_time.tv_secs = timeout / _PR_MD_INTERVAL_PER_SEC();
    timerIO->tr_time.tv_micro = timeout % _PR_MD_INTERVAL_PER_SEC() * (1000000 / _PR_MD_INTERVAL_PER_SEC());

    //printf("%lx, Beginning IO for sleep\n", thread);
    thread->io_pending = PR_TRUE;

    thread->sleepRequestUsed = PR_TRUE;
    SendIO((struct IORequest *)timerIO);
    _PR_MD_Wait(thread, PR_TRUE);

    if (_PR_PENDING_INTERRUPT(thread)) {
        PR_ClearInterrupt();
        printf("%lx, Sleep got interrupted\n", thread);
        PR_SetError(PR_PENDING_INTERRUPT_ERROR, 0);
        retval = INTERRUPTED;
    } else {   
        retval = (thread->state == _PR_RUNNING) ? SUCCESS : TIMEDOUT;
    }

    thread->state = _PR_RUNNING;

    while(GetMsg(thread->port))
        ;

    // printf("%lx, got msg %lx\n", thread, msg);
    if (!(CheckIO((struct IORequest *)timerIO))) {
        //printf("%lx abort io\n", thread);
        AbortIO((struct IORequest *)timerIO);
        //printf("%lx wait IO\n", thread);
        WaitIO((struct IORequest *)timerIO);
    }
    thread->io_pending = PR_FALSE;
 done:
    //printf("%lx done sleep returning\n", thread);
    return retval;
}

PR_IMPLEMENT(PRStatus) PR_Sleep(PRIntervalTime timeout) { 
    _PR_MD_Timeout retval = _PR_Sleep(timeout);
    return (retval == SUCCESS || retval == TIMEDOUT) ? PR_SUCCESS : PR_FAILURE;
}

void _MD_Interval_Init(void) {
}



PRIntervalTime _MD_Get_Interval(void) {
    PRIntervalTime retval = 0;
    struct timerequest *tr = PR_NEWZAP(struct timerequest);

    if (!(OpenDevice(TIMERNAME, UNIT_MICROHZ, (struct IORequest *)tr, 0))) {
        tr->tr_node.io_Command = TR_GETSYSTIME;
        DoIO((struct IORequest *)tr);
        retval = (tr->tr_time.tv_micro * _MD_INTERVAL_PER_SEC() / 1000000) + tr->tr_time.tv_secs * _MD_INTERVAL_PER_SEC();
        CloseDevice((struct IORequest *)tr);
    }
    PR_Free(tr);
    return retval;
}


PR_IMPLEMENT(PRTime)
    PR_Now(void)
{
    PRTime retval = LL_INIT(0,0);
    struct timerequest *tr = PR_NEWZAP(struct timerequest);
    PRInt64 secs, mil;
    
    if (!(OpenDevice(TIMERNAME, UNIT_MICROHZ, (struct IORequest *)tr, 0))) {
        struct timeval tv;
        struct Library *TimerBase = (struct Library *)tr->tr_node.io_Device;
        GetSysTime(&tv);
        /* retval = tv.tv_sec * 1000000 + tv.tv_usec */
        LL_I2L(secs, tv.tv_sec);
        LL_I2L(mil, 1000000);
        LL_MUL(secs, secs, mil);
        LL_I2L(mil, tv.tv_usec);
        LL_ADD(retval, secs, mil);
        
        CloseDevice((struct IORequest *)tr);
    }
    PR_Free(tr);
    return retval;
}

