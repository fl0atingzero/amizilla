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

#include "primpl.h"

PR_IMPLEMENT(PRLock*) PR_NewLock(void)
{
    PRLock *lock;

    if (!_pr_initialized) _PR_ImplicitInitialization();

    lock = PR_NEWZAP(PRLock);
    if (lock) {
        PR_INIT_CLIST(&(lock->waitQ));
    }
    return lock;
}

PR_IMPLEMENT(void) PR_Lock(PRLock *lock)
{
  PRThread *me = PR_GetCurrentThread();

  //printf("%lx going to lock %lx, owner is %lx\n", me, lock, lock->owner);
  Forbid();
  PR_ASSERT(lock->owner == NULL || lock->owner != me);
  if (lock->owner != NULL && lock->owner != me) {
      PR_APPEND_LINK(&me->waitQLinks, &lock->waitQ);
      me->wait.lock = lock;
      me->state = _PR_LOCK_WAIT;
      _PR_MD_Wait(me, PR_FALSE);
      me->state = _PR_RUNNING;
  }

  lock->owner = me;
  PR_APPEND_LINK(&lock->links, &me->lockList);
  Permit();
  //printf("%lx got lock %lx, owner is %lx\n", me, lock, lock->owner);
}


/*
** Unlock the lock.
*/
PR_IMPLEMENT(PRStatus) PR_Unlock(PRLock *lock)
{
    PRThread *me = PR_GetCurrentThread();

    //printf("%lx is going to unlock %lx, owner %lx\n", me, lock, lock->owner);
    Forbid();
    PR_ASSERT(lock->owner != NULL);
    PR_ASSERT(lock->owner == me);
    PR_REMOVE_LINK(&lock->links);

    if (!PR_CLIST_IS_EMPTY(&(lock->waitQ))) {
        PRCList *next = PR_LIST_HEAD(&lock->waitQ);
        PRThread *thread = _PR_THREAD_CONDQ_PTR(next);
        PR_REMOVE_LINK(next);
        lock->owner = thread;
        PR_ASSERT(thread->state != _PR_RUNNING);
        PR_ASSERT(thread->state == _PR_LOCK_WAIT);
        PR_ASSERT(thread->wait.lock == lock);
        _PR_MD_Signal(thread);
    } else {
        lock->owner = NULL;
    }
    Permit();
    //printf("%lx done unlock of %lx, owner is %lx\n", me, lock, lock->owner);
}

PR_IMPLEMENT(void)PR_DestroyLock(PRLock *lock) {
    PR_Free(lock);
}

void _PR_InitLocks(void){
}
