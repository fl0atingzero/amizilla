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

#ifndef nspr_amigaos_threads_h___
#define nspr_amigaos_threads_h___

#include <primpl.h>

/*
 * Here we define all machine dependent (MD) translation for
 * the threads/cpu nspr api (src/threads/**.c). The implemented
 * functions can be fund in (src/md/amiga/athreads.c)
 */

#define _MD_INIT_CPUS                     _InitCpus
#define _MD_WAKEUP_CPUS                   _WakeupCpus


/* Interrupts related */
#define _MD_START_INTERRUPTS              _StartInterrupts
#define _MD_STOP_INTERRUPTS               _StopInterrupts
#define _MD_ENABLE_CLOCK_INTERRUPTS       _EnableClockInterrupts
#define _MD_DISABLE_CLOCK_INTERRUPTS      _DisableClockInterrupts
#define _MD_BLOCK_CLOCK_INTERRUPTS        _BlockClockInterrupts
#define _MD_UNBLOCK_CLOCK_INTERRUPTS      _UnblockClockInterrupts
#define _MD_CLOCK_INTERRUPT               _ClockInterrupt

/* The _PR_MD_WAIT_LOCK and _PR_MD_WAKEUP_WAITER functions put to sleep and
 * awaken a thread which is waiting on a lock or cvar.
 */
#define _MD_WAIT                          _Wait
#define _MD_WAKEUP_WAITER                 _WakeupWaiter
     
/* Stack debugging */
#define _MD_INIT_STACK                    _InitStack
#define _MD_CLEAR_STACK                   _ClearStack

/* CPU related */
// #define _MD_GET_INTSOFF
// #define _MD_SET_INTSOFF
#define _MD_CURRENT_CPU()                   _CurrentCpu
#define _MD_SET_CURRENT_CPU               _SetCurrentCpu
#define _MD_INIT_RUNNING_CPU              _InitRunningCpu

/*
 * Returns the number of threads awoken or 0 if a timeout occurred;
 */
#define _MD_PAUSE_CPU                     _PauseCpu
#define _MD_CLEANUP_BEFORE_EXIT           _CleanupBeforeExit
#define _MD_EXIT                          _Exit

/* Locks related */
#define _MD_INIT_LOCKS                    _InitLocks
#define _MD_NEW_LOCK                      _NewLock
#define _MD_FREE_LOCK                     _FreeLock
#define _MD_LOCK                          _Lock

/* Return 0 on success, a nonzero value on failure. */
#define _MD_TEST_AND_LOCK                 _TestAndLock
#define _MD_UNLOCK                        _UnLock
#define _MD_IOQ_LOCK                      _IOQLock
#define _MD_IOQ_UNLOCK                    _IOQUnLock

/* Semaphore related -- only for native threads */
#define _MD_NEW_SEM                       _NewSem
#define _MD_DESTROY_SEM                   _DestroySem
#define _MD_TIMED_WAIT_SEM                _TimedWaitSem
#define _MD_WAIT_SEM                      _WaitSem
#define _MD_POST_SEM                      _PostSem

/* Condition Variables related -- only for native threads */
#define _MD_NEW_CV                        _NewCV
#define _MD_FREE_CV                       _FreeCV
#define _MD_WAIT_CV                       _WaitCV
#define _MD_NOTIFY_CV                     _NotifyCV
#define _MD_NOTIFYALL_CV                  _NotifyAllCV

/* Threads related */
#define _MD_CURRENT_THREAD                PR_GetCurrentThread //_MD_CURRENT_THREAD
// #define _MD_GET_ATTACHED_THREAD
#define _MD_LAST_THREAD                   _LastThread
#define _MD_SET_CURRENT_THREAD            _SetCurrentThread
#define _MD_SET_LAST_THREAD               _SetLastThread
#define _MD_INIT_THREAD                   _InitThread
#define _MD_EXIT_THREAD                   _ExitThread
#define _MD_INIT_ATTACHED_THREAD          _InitAttachedThread
#define _MD_SUSPEND_THREAD                _SuspendThread
#define _MD_RESUME_THREAD                 _ResumeThread
#define _MD_SUSPEND_CPU                   _SuspendCpu
#define _MD_RESUME_CPU                    _ResumeCpu
#define _MD_BEGIN_SUSPEND_ALL             _BeginSuspendAll
#define _MD_END_SUSPEND_ALL               _EndSuspendAll
#define _MD_BEGIN_RESUME_ALL              _BeginResumeAll
#define _MD_END_RESUME_ALL                _EndResumeAll
#define _MD_CLEAN_THREAD                  _CleanThread
#define _MD_CREATE_PRIMORDIAL_USER_THREAD _CreatePrimordialUserThread
#define _MD_CREATE_USER_THREAD            _CreateUserThread
#define _MD_CREATE_THREAD                 _CreateThread
#define _MD_JOIN_THREAD                   _JoinThread
#define _MD_END_THREAD                    _EndThread
#define _MD_YIELD                         _Yield
#define _MD_SET_PRIORITY                  _SetPriority
#define _MD_SUSPENDALL                    _SuspendAll
#define _MD_RESUMEALL                     _ResumeAll
#define _MD_INIT_CONTEXT                  _InitContext
#define _MD_SWITCH_CONTEXT                _SwitchContext
#define _MD_RESTORE_CONTEXT               _RestoreContext

/*
 * Define threading functions and objects as native AmigaOS
 */
struct _MDThread {
  /* from beos
    thread_id	tid;	// BeOS thread handle 
    sem_id		joinSem;	// sems used to synchronzie joining 
    PRBool	is_joining;	// TRUE if someone is currently waiting to join this thread
  */
};

struct _MDThreadStack {
  /* from beos
    PRInt8	notused;
  */
};

/*
 * Lock and Semaphore related definitions
 */
struct _MDLock {
  /* from beos
    sem_id semaphoreID;
    int32  benaphoreCount;
  */
};

struct _MDCVar {
  /* from beos
    sem_id sem1;
    sem_id sem2;
    int16  count;
  */
};

struct _MDSemaphore {
  /* from beos
    sem_id sid;
  */
};

/*
 * CPU-related definitions
 */
struct _MDCPU {
  /* from beos
    int8		unused;
  */
};

/*
 * Process-related definitions
 */
struct _MDProcess {
  /* from beos
    pid_t pid;
  */
};

struct _MDSegment {
  /* from beos
    PRInt8 notused;
  */
};


NSPR_API(void)     _InitCpus();
NSPR_API(void)     _WakeupCpus();
NSPR_API(void)     _StartInterrupts(void);
NSPR_API(void)     _StopInterrupts(void);
NSPR_API(void)     _EnableClockInterrupts(void);
NSPR_API(void)     _DisableClockInterrupts(void);
NSPR_API(void)     _BlockClockInterrupts(void);
NSPR_API(void)     _UnblockClockInterrupts(void);
NSPR_API(void)     _ClockInterrupt(void);

NSPR_API(PRStatus) _Wait(PRThread *thread, PRIntervalTime timeout);
NSPR_API(PRStatus) _WakeupWaiter(PRThread *thread);

NSPR_API(void)     _InitStack(PRThreadStack *ts, PRIntn redzone);
NSPR_API(void)     _ClearStack(PRThreadStack* ts);

extern struct _PRCPU *_CurrentCpu;
// NSPR_API(_PRCPU*)  _CurrentCpu(void);
// NSPR_API(void)     _SetCurrentCpu(_PRCPU *cpu);
// NSPR_API(void)     _InitRunningCpu(_PRCPU *cpu);

NSPR_API(PRInt32)  _PauseCpu(PRIntervalTime timeout);
NSPR_API(void)     _CleanupBeforeExit(void);
NSPR_API(void)     _Exit(PRIntn status);

NSPR_API(void)     _InitLocks(void);
NSPR_API(PRStatus) _NewLock(struct _MDLock *md);
NSPR_API(void)     _FreeLock(struct _MDLock *md);
NSPR_API(void)     _Lock(struct _MDLock *md);

NSPR_API(PRIntn)   _TestAndLock(struct _MDLock *md);
NSPR_API(void)     _UnLock(struct _MDLock *md);
NSPR_API(void)     _IOQLock(void);
NSPR_API(void)     _IOQUnLock(void);

NSPR_API(void)     _NewSem(struct _MDSemaphore *md, PRUintn value);
NSPR_API(void)     _DestroySem(struct _MDSemaphore *md);
NSPR_API(PRStatus) _TimedWaitSem(struct _MDSemaphore *md, PRIntervalTime timeout);
NSPR_API(PRStatus) _WaitSem(struct _MDSemaphore *md);
NSPR_API(void)     _PostSem(struct _MDSemaphore *md);

NSPR_API(PRInt32)  _NewCV(struct _MDCVar *md);
NSPR_API(void)     _FreeCV(struct _MDCVar *md);
NSPR_API(void)     _WaitCV(struct _MDCVar *mdCVar, struct _MDLock *mdLock, PRIntervalTime timeout);
NSPR_API(void)     _NotifyCV(struct _MDCVar *md, struct _MDLock *lock);
NSPR_API(void)     _NotifyAllCV(struct _MDCVar *md, struct _MDLock *lock);


//NSPR_API(PRThread*) _CurrentThread(void);
NSPR_API(PRThread*) _GetAttachedThread(void);
NSPR_API(PRThread*) _LastThread(void);
NSPR_API(void)      _SetCurrentThread(PRThread *thread);
NSPR_API(void)      _SetLastThread(PRThread *thread);
NSPR_API(PRStatus)  _InitThread(PRThread *thread);
NSPR_API(void)      _ExitThread(PRThread *thread);
NSPR_API(PRStatus)  _InitAttachedThread(PRThread *thread);
NSPR_API(void)      _SuspendThread(PRThread *thread);
NSPR_API(void)      _ResumeThread(PRThread *thread);
// NSPR_API(void)      _SuspendCpu(_PRCPU *cpu);
// NSPR_API(void)      _ResumeCpu(_PRCPU *cpu);
NSPR_API(void)      _BeginSuspend_all(void);
NSPR_API(void)      _EndSuspend_all(void);
NSPR_API(void)      _BeginResume_all(void);
NSPR_API(void)      _EndResume_all(void);
NSPR_API(void)      _CleanThread(PRThread *thread);
NSPR_API(void)      _CreatePrimordialUserThread(PRThread *thread);
NSPR_API(PRThread*) _CreateUserThread(PRUint32 stacksize, void (*start)(void *), void *arg);
NSPR_API(PRStatus)  _CreateThread(PRThread *thread, void (*start)(void *), PRThreadPriority priority, PRThreadScope scope, PRThreadState state, PRUint32 stackSize);
NSPR_API(void)      _Yield(void);
NSPR_API(void)      _SetPriority(struct _MDThread *md, PRThreadPriority newPri);
NSPR_API(void)      _SuspendAll(void);
NSPR_API(void)      _ResumeAll(void);
NSPR_API(void)      _InitContext(PRThread *thread, char *top, void (*start) (void), PRBool *status);
NSPR_API(void)      _SwitchContext(PRThread *thread);
NSPR_API(void)      _RestoreContext(PRThread *thread);

#endif /* nspr_amigaos_threads_h___ */













