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


/*
 * Here we define all machine dependent (MD) translation for
 * the threads/cpu nspr api (src/threads/**.c). The implemented
 * functions can be fund in (src/md/amiga/athreads.c)
 */

#define _MD_INIT_CPUS                     _MD_INIT_CPUS
#define _MD_WAKEUP_CPUS                   _MD_WAKEUP_CPUS


/* Interrupts related */
#define _MD_START_INTERRUPTS              _MD_START_INTERRUPTS
#define _MD_STOP_INTERRUPTS               _MD_STOP_INTERRUPTS
#define _MD_ENABLE_CLOCK_INTERRUPTS       _MD_ENABLE_CLOCK_INTERRUPTS
#define _MD_DISABLE_CLOCK_INTERRUPTS      _MD_DISABLE_CLOCK_INTERRUPTS
#define _MD_BLOCK_CLOCK_INTERRUPTS        _MD_BLOCK_CLOCK_INTERRUPTS
#define _MD_UNBLOCK_CLOCK_INTERRUPTS      _MD_UNBLOCK_CLOCK_INTERRUPTS
#define _MD_CLOCK_INTERRUPT               _MD_CLOCK_INTERRUPT

/* The _PR_MD_WAIT_LOCK and _PR_MD_WAKEUP_WAITER functions put to sleep and
 * awaken a thread which is waiting on a lock or cvar.
 */
#define _MD_WAIT                          _MD_WAIT
#define _MD_WAKEUP_WAITER                 _MD_WAKEUP_WAITER
     
/* Stack debugging */
#define _MD_INIT_STACK                    _MD_INIT_STACK
#define _MD_CLEAR_STACK                   _MD_CLEAR_STACK

/* CPU related */
// #define _MD_GET_INTSOFF
// #define _MD_SET_INTSOFF
#define _MD_CURRENT_CPU()                 _CurrentCpu
#define _MD_SET_CURRENT_CPU               _MD_SET_CURRENT_CPU
#define _MD_INIT_RUNNING_CPU              _MD_INIT_RUNNING_CPU

/*
 * Returns the number of threads awoken or 0 if a timeout occurred;
 */
#define _MD_PAUSE_CPU                     _MD_PAUSE_CPU
#define _MD_CLEANUP_BEFORE_EXIT           _MD_CLEANUP_BEFORE_EXIT
#define _MD_EXIT                          _MD_EXIT

/* Locks related */
#define _MD_INIT_LOCKS                    _MD_INIT_LOCKS
#define _MD_NEW_LOCK                      _MD_NEW_LOCK
#define _MD_FREE_LOCK                     _MD_FREE_LOCK
#define _MD_LOCK                          _MD_LOCK

/* Return 0 on success, a nonzero value on failure. */
#define _MD_TEST_AND_LOCK                 _MD_TEST_AND_LOCK
#define _MD_UNLOCK                        _MD_UNLOCK
#define _MD_IOQ_LOCK                      _MD_IOQ_LOCK
#define _MD_IOQ_UNLOCK                    _MD_IOQ_UNLOCK

/* Semaphore related -- only for native threads */
#define _MD_NEW_SEM                       _MD_NEW_SEM
#define _MD_DESTROY_SEM                   _MD_DESTROY_SEM
#define _MD_TIMED_WAIT_SEM                _MD_TIMED_WAIT_SEM
#define _MD_WAIT_SEM                      _MD_WAIT_SEM
#define _MD_POST_SEM                      _MD_POST_SEM

/* Condition Variables related -- only for native threads */
#define _MD_NEW_CV                        _MD_NEW_CV
#define _MD_FREE_CV                       _MD_FREE_CV
#define _MD_WAIT_CV                       _MD_WAIT_CV
#define _MD_NOTIFY_CV                     _MD_NOTIFY_CV
#define _MD_NOTIFYALL_CV                  _MD_NOTIFYALL_CV

/* Threads related */
#define _MD_CURRENT_THREAD                PR_GetCurrentThread //_MD_CURRENT_THREAD
// #define _MD_GET_ATTACHED_THREAD
#define _MD_LAST_THREAD                   _LastThread
#define _MD_SET_CURRENT_THREAD            _MD_SET_CURRENT_THREAD
#define _MD_SET_LAST_THREAD               _MD_SET_LAST_THREAD
#define _MD_INIT_THREAD                   _MD_INIT_THREAD
#define _MD_EXIT_THREAD                   _MD_EXIT_THREAD
#define _MD_INIT_ATTACHED_THREAD          _MD_INIT_ATTACHED_THREAD
#define _MD_SUSPEND_THREAD                _MD_SUSPEND_THREAD
#define _MD_RESUME_THREAD                 _MD_RESUME_THREAD
#define _MD_SUSPEND_CPU                   _MD_SUSPEND_CPU
#define _MD_RESUME_CPU                    _MD_RESUME_CPU
#define _MD_BEGIN_SUSPEND_ALL             _MD_BEGIN_SUSPEND_ALL
#define _MD_END_SUSPEND_ALL               _MD_END_SUSPEND_ALL
#define _MD_BEGIN_RESUME_ALL              _MD_BEGIN_RESUME_ALL
#define _MD_END_RESUME_ALL                _MD_END_RESUME_ALL
#define _MD_CLEAN_THREAD                  _MD_CLEAN_THREAD
#define _MD_CREATE_PRIMORDIAL_USER_THREAD _MD_CREATE_PRIMORDIAL_USER_THREAD
#define _MD_CREATE_USER_THREAD            _MD_CREATE_USER_THREAD
#define _MD_CREATE_THREAD                 _MD_CREATE_THREAD
#define _MD_JOIN_THREAD                   _MD_JOIN_THREAD
#define _MD_END_THREAD                    _MD_END_THREAD
#define _MD_YIELD                         _MD_YIELD
#define _MD_SET_PRIORITY                  _MD_SET_PRIORITY
#define _MD_SUSPENDALL                    _MD_SUSPENDALL
#define _MD_RESUMEALL                     _MD_RESUMEALL
#define _MD_INIT_CONTEXT                  _MD_INIT_CONTEXT
#define _MD_SWITCH_CONTEXT                _MD_SWITCH_CONTEXT
#define _MD_RESTORE_CONTEXT               _MD_RESTORE_CONTEXT

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

extern struct _PRCPU *_CurrentCpu;

NSPR_API(PRThread*) _LastThread(void);

#endif /* nspr_amigaos_threads_h___ */



