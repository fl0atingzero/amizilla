/* -*- Mode: C++; tab-width: 8; c-basic-offset: 8 -*- */
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

#include <assert.h>

#include "primpl.h"

/*
 * Amiga specificy includes
 */
#include <exec/memory.h>
#include <proto/exec.h>

#warning _pr_interruptTable NULL
_PRInterruptTable _pr_interruptTable[] = {};

void _InitCpus() {
#warning unimplemented function
   assert(0);
}

void _WakeupCpus() { 
#warning unimplemented function
   assert(0);
}

void _StartInterrupts(void) { 
#warning unimplemented function
   assert(0);
}

void _StopInterrupts(void) { 
#warning unimplemented function
   assert(0);
}

void _EnableClockInterrupts(void) { 
#warning unimplemented function
   assert(0);
}

void _DisableClockInterrupts(void) { 
#warning unimplemented function
   assert(0);
}

void _BlockClockInterrupts(void) {
#warning unimplemented function
   assert(0);
}

void _UnblockClockInterrupts(void) { 
#warning unimplemented function
   assert(0);
}

void _ClockInterrupt(void) {
#warning unimplemented function
   assert(0);
}

PRStatus _Wait(PRThread *thread, PRIntervalTime timeout) { 
#warning unimplemented function
   assert(0);
}

PRStatus _WakeupWaiter(PRThread *thread) {
#warning unimplemented function
   assert(0);
}

void _InitStack(PRThreadStack *ts, PRIntn redzone) {
#warning unimplemented function
   assert(0);
}

void _ClearStack(PRThreadStack* ts) {
#warning unimplemented function
   assert(0);
}


_PRCPU *_CurrentCpu(void) {
#warning _CurrentCpu not implemented
	assert(0);
}

void _SetCurrentCpu(_PRCPU *cpu) {
#warning _SetCurrentCpu not implemented
	assert(0);
}

void _InitRunningCpu(_PRCPU *cpu) {
#warning _InitRunningCpu not implemented
	assert(0);
}

PRInt32 _PauseCpu(PRIntervalTime timeout) {
#warning unimplemented function
   assert(0);
}

void _CleanupBeforeExit(void) {
#warning unimplemented function
   assert(0);
}

void _Exit(PRIntn status) {
#warning unimplemented function
   assert(0);
}

void _InitLocks(void) {
#warning unimplemented function
   assert(0);
}

PRStatus _NewLock(struct _MDLock *md) {
#warning unimplemented function
   assert(0);
}

void _FreeLock(struct _MDLock *md) {
#warning unimplemented function
   assert(0);
}

void _Lock(struct _MDLock *md) {
#warning unimplemented function
   assert(0);
}

PRIntn _TestAndLock(struct _MDLock *md) {
#warning unimplemented function
   assert(0);
}

void _UnLock(struct _MDLock *md) {
#warning unimplemented function
   assert(0);
}

void _IOQLock(void) {
#warning unimplemented function
   assert(0);
}

void _IOQUnLock(void) {
#warning unimplemented function
   assert(0);
}

void _NewSem(struct _MDSemaphore *md, PRUintn value) {
#warning unimplemented function
   assert(0);
}

void _DestroySem(struct _MDSemaphore *md) {
#warning unimplemented function
   assert(0);
}

PRStatus _TimedWaitSem(struct _MDSemaphore *md, PRIntervalTime timeout) {
#warning unimplemented function
   assert(0);
}

PRStatus _WaitSem(struct _MDSemaphore *md) {
#warning unimplemented function
   assert(0);
}

void _PostSem(struct _MDSemaphore *md) {
#warning unimplemented function
   assert(0);
}

PRInt32 _NewCV(struct _MDCVar *md) {
#warning unimplemented function
   assert(0);
}

void _FreeCV(struct _MDCVar *md) {
#warning unimplemented function
   assert(0);
}

void _WaitCV(struct _MDCVar *mdCVar, struct _MDLock *mdLock, PRIntervalTime timeout) {
#warning unimplemented function
   assert(0);
}

void _NotifyCV(struct _MDCVar *md, struct _MDLock *lock) {
#warning unimplemented function
   assert(0);
}

void _NotifyAllCV(struct _MDCVar *md, struct _MDLock *lock) {
#warning unimplemented function
   assert(0);
}

PRThread *_GetAttachedThread(void) {
#warning unimplemented function
   assert(0);
}

PRThread *_LastThread(void) {
#warning unimplemented function
   assert(0);
}

void _SetCurrentThread(PRThread *thread) {
#warning unimplemented function
   assert(0);
}

void _SetLastThread(PRThread *thread) {
#warning unimplemented function
   assert(0);
}

PRStatus _InitThread(PRThread *thread) {
#warning unimplemented function
   assert(0);
}

void _ExitThread(PRThread *thread) {
#warning unimplemented function
   assert(0);
}

PRStatus _InitAttachedThread(PRThread *thread) {
#warning unimplemented function
   assert(0);
}

void _SuspendThread(PRThread *thread) {
#warning unimplemented function
   assert(0);
}

void _ResumeThread(PRThread *thread) {
#warning unimplemented function
   assert(0);
}

/*
void _SuspendCpu(_PRCPU  *cpu) {
#warning unimplemented function
   assert(0);
}

void _ResumeCpu(_PRCPU  *cpu) {
#warning unimplemented function
   assert(0);
}
*/

void _BeginSuspendAll(void) {
#warning unimplemented function
   assert(0);
}

void _EndSuspendAll(void) {
#warning unimplemented function
   assert(0);
}

void _BeginResumeAll(void) {
#warning unimplemented function
   assert(0);
}

void _EndResumeAll(void) {
#warning unimplemented function
   assert(0);
}

void _CleanThread(PRThread *thread) {
#warning unimplemented function
   assert(0);
}

void _CreatePrimordialUserThread(PRThread *thread) {
#warning unimplemented function
   assert(0);
}

PRThread *_CreateUserThread(PRUint32 stacksize, void (*start)(void *), void *arg) {
#warning unimplemented function
   assert(0);
}

PRStatus _CreateThread(PRThread *thread, void (*start)(void *), PRThreadPriority priority, PRThreadScope scope, PRThreadState state, PRUint32 stackSize) {
#warning unimplemented function
   assert(0);
}

void _Yield(void) {
#warning unimplemented function
   assert(0);
}

void _SetPriority(struct _MDThread *md, PRThreadPriority newPri) {
#warning unimplemented function
   assert(0);
}

void _SuspendAll(void) {
#warning unimplemented function
   assert(0);
}

void _ResumeAll(void) {
#warning unimplemented function
   assert(0);
}

void _InitContext(PRThread *thread, char *top, void (*start) (void), PRBool *status) {
#warning unimplemented function
   assert(0);
}

void _SwitchContext(PRThread *thread) {
#warning unimplemented function
   assert(0);
}

void _RestoreContext(PRThread *thread) {
#warning unimplemented function
   assert(0);
}

/* Process control */

extern PRProcess * _MD_CREATE_PROCESS(
    const char *path,
    char *const *argv,
    char *const *envp,
    const PRProcessAttr *attr) {
#warning _MD_CREATE_PROCESS not implemented
    assert(0);
}

PRStatus _MD_DETACH_PROCESS(PRProcess *process) {
#warning _MD_DETACH_PROCESS not implemented
    assert(0);
}

PRStatus _MD_WAIT_PROCESS(PRProcess *process, PRInt32 *exitCode) {
#warning _MD_WAIT_PROCESS not implemented
    assert(0);
}

PRStatus _MD_KILL_PROCESS(PRProcess *process) {
#warning _MD_KILL_PROCESS not implemented
    assert(0);
}

PRIntervalTime _MD_GET_INTERVAL(void) {
#warning _MD_GET_INTERVAL not implemented
    assert(0);
}

PRIntervalTime _MD_INTERVAL_PER_SEC(void) {
#warning _MD_INTERVAL_PER_SEC not implemented
    assert(0);
}

/*extern void _PR_IntsOn(_PRCPU *cpu) {
#warning _PR_IntsOn not implemented
    assert(0);
}*/
