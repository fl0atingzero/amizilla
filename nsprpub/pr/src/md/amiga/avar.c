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

#include "primpl.h"


static void PrintLinks(PRCList *list) {
  PRCList *link;
  PRThread *me = PR_CurrentThread();
  if (!PR_CLIST_IS_EMPTY(list)) {
    for (link = PR_LIST_HEAD(list); link != list; link = PR_NEXT_LINK(link)) {
      PRThread *thread = _PR_THREAD_CONDQ_PTR(link);
      PR_fprintf(PR_STDERR, "%lx\tfor %lx, thread %lx is on the queue\n", me, list, thread);
    }
  } else {
    PR_fprintf(PR_STDERR, "Nobody on queue %lx\n", list);
  }
}

/*
** Create a new condition variable.
**
** 	"lock" is the lock used to protect the condition variable.
**
** Condition variables are synchronization objects that threads can use
** to wait for some condition to occur.
**
** This may fail if memory is tight or if some operating system resource
** is low. In such cases, a NULL will be returned.
*/
PR_IMPLEMENT(PRCondVar*) PR_NewCondVar(PRLock *lock) {
    PRCondVar *retval = PR_NEWZAP(PRCondVar);
    if (retval) {
      retval->lock = lock;
      PR_INIT_CLIST(&(retval->condQ));
    }
    return retval;
}

/*
** Destroy a condition variable. There must be no thread
** waiting on the condvar. The caller is responsible for guaranteeing
** that the condvar is no longer in use.
**
*/
PR_IMPLEMENT(void) PR_DestroyCondVar(PRCondVar *cvar) {
    PR_Free(cvar);
}

/*
** The thread that waits on a condition is blocked in a "waiting on
** condition" state until another thread notifies the condition or a
** caller specified amount of time expires. The lock associated with
** the condition variable will be released, which must have be held
** prior to the call to wait.
**
** Logically a notified thread is moved from the "waiting on condition"
** state and made "ready." When scheduled, it will attempt to reacquire
** the lock that it held when wait was called.
**
** The timeout has two well known values, PR_INTERVAL_NO_TIMEOUT and
** PR_INTERVAL_NO_WAIT. The former value requires that a condition be
** notified (or the thread interrupted) before it will resume from the
** wait. If the timeout has a value of PR_INTERVAL_NO_WAIT, the effect
** is to release the lock, possibly causing a rescheduling within the
** runtime, then immediately attempting to reacquire the lock and resume.
**
** Any other value for timeout will cause the thread to be rescheduled
** either due to explicit notification or an expired interval. The latter
** must be determined by treating time as one part of the monitored data
** being protected by the lock and tested explicitly for an expired
** interval.
**
** Returns PR_FAILURE if the caller has not locked the lock associated
** with the condition variable or the thread was interrupted (PR_Interrupt()).
** The particular reason can be extracted with PR_GetError().
*/
PR_IMPLEMENT(PRStatus) PR_WaitCondVar(PRCondVar *cvar, PRIntervalTime timeout) {
  PRThread *me = PR_GetCurrentThread();
  if (cvar->lock->owner != me) {
    return PR_FAILURE;
  }
  //PR_fprintf(PR_STDERR, "%lx Wait on condvar, timeout is %ld, cv is %lx\n", me, timeout, cvar);

  me->state = _PR_COND_WAIT;
  me->wait.cvar = cvar;
  PR_APPEND_LINK(&me->waitQLinks, &(cvar->condQ));
  PR_Unlock(cvar->lock);
  //PR_fprintf(PR_STDERR, "%lx, done unlock of cvar %lx, lock %lx\n", me, cvar, cvar->lock);

  if (timeout == PR_INTERVAL_NO_WAIT) {
    //PR_fprintf(PR_STDERR, "%lx not waiting for condvar, sleep(0)\n", me);
    PR_Sleep(0);
  } else if (timeout == PR_INTERVAL_NO_TIMEOUT) {
    _PR_MD_Wait(me);
  } else {
    PR_Sleep(timeout);
  }
  //PR_fprintf(PR_STDERR, "%lx woke up from condvar sleep on %lx\n", me, cvar);
  me->state = _PR_RUNNING;
  PR_Lock(cvar->lock);
  //PR_fprintf(PR_STDERR, "%lx going for cvar lock %lx, cvar is %lx\n", me, cvar->lock, cvar);
  //PR_fprintf(PR_STDERR, "%lx got cvar lock %lx, owner is now %lx, cvar is %lx\n", me, cvar->lock, cvar->lock->owner, cvar);
  /*  PR_Sleep(0); /* Try to make the scheduler more fair */
  return PR_SUCCESS;
}

/*
** Notify ONE thread that is currently waiting on 'cvar'. Which thread is
** dependent on the implementation of the runtime. Common sense would dictate
** that all threads waiting on a single condition have identical semantics,
** therefore which one gets notified is not significant. 
**
** The calling thead must hold the lock that protects the condition, as
** well as the invariants that are tightly bound to the condition, when
** notify is called.
**
** Returns PR_FAILURE if the caller has not locked the lock associated
** with the condition variable.
*/
PR_IMPLEMENT(PRStatus) PR_NotifyCondVar(PRCondVar *cvar) {
  PRThread *me = PR_GetCurrentThread();
  PRThread *thread;
  PRCList *next;

  PR_ASSERT(cvar->lock->owner == me);
  //PR_fprintf(PR_STDERR, "%lx going to notify thread of cond var %lx, owner is %lx\n", me, cvar, cvar->lock->owner);
  
  if (!PR_CLIST_IS_EMPTY(&(cvar->condQ))) {
    //PrintLinks(&(cvar->condQ));
    next = cvar->condQ.next;
    thread = _PR_THREAD_CONDQ_PTR(next);
    PR_REMOVE_LINK(next);
    //PR_fprintf(PR_STDERR, "%lx notifying thread %lx of condvar %lx\n", me, thread, cvar);
    _PR_MD_Signal(thread);

  } 
  //PR_fprintf(PR_STDERR, "%lx done with notifycondvar %lx\n", me, cvar);
  return PR_SUCCESS;
}

/*
** Notify all of the threads waiting on the condition variable. The order
** that the threads are notified is indeterminant. The lock that protects
** the condition must be held.
**
** Returns PR_FAILURE if the caller has not locked the lock associated
** with the condition variable.
*/
PR_IMPLEMENT(PRStatus) PR_NotifyAllCondVar(PRCondVar *cvar) {
  PRThread *me = PR_GetCurrentThread();
 
  //PR_fprintf(PR_STDERR, "%lx going to notify all threads for cv %lx\n", me, cvar);

  if (cvar->lock->owner != me) {
    return PR_FAILURE;
  }

  if (!PR_CLIST_IS_EMPTY(&(cvar->condQ))) {
    PRCList *foo = &(cvar->condQ);
    PRCList *next;    
    for (next = PR_LIST_HEAD(foo); next != foo;) {
      PRThread *thread = _PR_THREAD_CONDQ_PTR(next);
      PRCList *tmp = next;
      next = PR_NEXT_LINK(next);
      PR_REMOVE_LINK(tmp);
      
      //PR_fprintf(PR_STDERR, "%lx notifying thread %lx of condvar %lx\n", me, thread, cvar);
      _PR_MD_Signal(thread);
    }
  }
  //  PrintLinks(&(cvar->condQ));
  return PR_SUCCESS;
}
