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

#include "primpl.h"

/*
 * Amiga specificy includes
 */
#include <exec/memory.h>
#include <proto/exec.h>

void _InitCpus() {
}

void _WakeupCpus() { 
}

void _StartInterrupts(void) { 
}

void _StopInterrupts(void) { 
}

void _EnableClockInterrupts(void) { 
}

void _DisableClockInterrupts(void) { 
}

void _BlockClockInterrupts(void) {
}

void _UnblockClockInterrupts(void) { 
}

void _ClockInterrupt(void) {
}

PRStatus _Wait(PRThread *thread, PRIntervalTime timeout) { 
}

PRStatus _WakeupWaiter(PRThread *thread) {
}

void _InitStack(PRThreadStack *ts, PRIntn redzone) {
}

void _ClearStack(PRThreadStack* ts) {
}

/*
_PRCPU *_CurrentCpu(void) {
}

void _SetCurrentCpu(_PRCPU *cpu) {
}

void _InitRunningCpu(_PRCPU *cpu) {
}
*/

PRInt32 _PauseCpu(PRIntervalTime timeout) {
}

void _CleanupBeforeExit(void) {
}

void _Exit(PRIntn status) {
}

void _InitLocks(void) {
}

PRStatus _NewLock(struct _MDLock *md) {
}

void _FreeLock(struct _MDLock *md) {
}

void _Lock(struct _MDLock *md) {
}

PRIntn _TestAndLock(struct _MDLock *md) {
}

void _UnLock(struct _MDLock *md) {
}

void _IOQLock(void) {
}

void _IOQUnLock(void) {
}

void _NewSem(struct _MDSemaphore *md, PRUintn value) {
}

void _DestroySem(struct _MDSemaphore *md) {
}

PRStatus _TimedWaitSem(struct _MDSemaphore *md, PRIntervalTime timeout) {
}

PRStatus _WaitSem(struct _MDSemaphore *md) {
}

void _PostSem(struct _MDSemaphore *md) {
}

PRInt32 _NewCV(struct _MDCVar *md) {
}

void _FreeCV(struct _MDCVar *md) {
}

void _WaitCV(struct _MDCVar *mdCVar, struct _MDLock *mdLock, PRIntervalTime timeout) {
}

void _NotifyCV(struct _MDCVar *md, struct _MDLock *lock) {
}

void _NotifyAllCV(struct _MDCVar *md, struct _MDLock *lock) {
}

PRThread *_GetAttachedThread(void) {
}

PRThread *_LastThread(void) {
}

void _SetCurrentThread(PRThread *thread) {
}

void _SetLastThread(PRThread *thread) {
}

PRStatus _InitThread(PRThread *thread) {
}

void _ExitThread(PRThread *thread) {
}

PRStatus _InitAttachedThread(PRThread *thread) {
}

void _SuspendThread(PRThread *thread) {
}

void _ResumeThread(PRThread *thread) {
}

/*
void _SuspendCpu(_PRCPU  *cpu) {
}

void _ResumeCpu(_PRCPU  *cpu) {
}
*/

void _BeginSuspend_all(void) {
}

void _EndSuspend_all(void) {
}

void _BeginResume_all(void) {
}

void _EndResume_all(void) {
}

void _CleanThread(PRThread *thread) {
}

void _CreatePrimordialUserThread(PRThread *thread) {
}

PRThread *_CreateUserThread(PRUint32 stacksize, void (*start)(void *), void *arg) {
}

PRStatus _CreateThread(PRThread *thread, void (*start)(void *), PRThreadPriority priority, PRThreadScope scope, PRThreadState state, PRUint32 stackSize) {
}

void _Yield(void) {
}

void _SetPriority(struct _MDThread *md, PRThreadPriority newPri) {
}

void _SuspendAll(void) {
}

void _ResumeAll(void) {
}

void _InitContext(PRThread *thread, char *top, void (*start) (void), PRBool *status) {
}

void _SwitchContext(PRThread *thread) {
}

void _RestoreContext(PRThread *thread) {
}












