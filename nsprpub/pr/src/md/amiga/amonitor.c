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
#include <string.h>

/*
** Create a new monitor. Monitors are re-entrant locks with a single built-in
** condition variable.
**
** This may fail if memory is tight or if some operating system resource
** is low.
*/
PR_IMPLEMENT(PRMonitor*) PR_NewMonitor(void) {
    PRMonitor *retval;

    if (!_pr_initialized) _PR_ImplicitInitialization();

    retval = PR_NEWZAP(PRMonitor);
    if (retval != NULL) {
        PRLock *lock = PR_NewLock();
        if (lock != NULL) {
            PRCondVar *cvar = PR_NewCondVar(lock);
            if (cvar != NULL) {
                retval->cvar = cvar;
                return retval;
            } else {
                PR_DestroyLock(lock);
            }
        } else {
            PR_Free(retval);
        }
    }
    return NULL;     
}

/*
** Destroy a monitor. The caller is responsible for guaranteeing that the
** monitor is no longer in use. There must be no thread waiting on the monitor's
** condition variable and that the lock is not held.
**
*/
PR_IMPLEMENT(void) PR_DestroyMonitor(PRMonitor *mon) {
    if (mon->name != NULL)
        PR_Free(mon->name);
    PR_DestroyLock(mon->cvar->lock);
    PR_DestroyCondVar(mon->cvar);
    PR_Free(mon);
}

/*
** Enter the lock associated with the monitor. If the calling thread currently
** is in the monitor, the call to enter will silently succeed. In either case,
** it will increment the entry count by one.
*/
PR_IMPLEMENT(void) PR_EnterMonitor(PRMonitor *mon) {
    PRThread *me = PR_GetCurrentThread();
    //printf("%lx entering monitor %lx, owner is %lx, count is %lx\n", me, mon, mon->cvar->lock->owner, mon->entryCount);
    if (mon->cvar->lock->owner != me) {
        PR_Lock(mon->cvar->lock);
    } 
    mon->entryCount++;
    //printf("%lx done entermonitor, owner is now %lx\n", mon->cvar->lock->owner);
    PR_ASSERT(mon->cvar->lock->owner == me);
}

/*
** Decrement the entry count associated with the monitor. If the decremented
** entry count is zero, the monitor is exited. Returns PR_FAILURE if the
** calling thread has not entered the monitor.
*/
PR_IMPLEMENT(PRStatus) PR_ExitMonitor(PRMonitor *mon) {
    PRThread *me = PR_GetCurrentThread();
    //printf("%lx exitting monitor %lx, owner is %lx, count is %lx\n", me, mon, mon->cvar->lock->owner, mon->entryCount);
    if (mon->cvar->lock->owner != me) {
        return PR_FAILURE;
    }
    PR_ASSERT(mon->entryCount > 0);
    if (--mon->entryCount == 0) {
        PR_Unlock(mon->cvar->lock);
    }
    return PR_SUCCESS;
}

/*
** Wait for a notify on the monitor's condition variable. Sleep for "ticks"
** amount of time (if "ticks" is PR_INTERVAL_NO_TIMEOUT then the sleep is
** indefinite).
**
** While the thread is waiting it exits the monitor (as if it called
** PR_ExitMonitor as many times as it had called PR_EnterMonitor).  When
** the wait has finished the thread regains control of the monitors lock
** with the same entry count as before the wait began.
**
** The thread waiting on the monitor will be resumed when the monitor is
** notified (assuming the thread is the next in line to receive the
** notify) or when the "ticks" timeout elapses.
**
** Returns PR_FAILURE if the caller has not entered the monitor.
*/
PR_IMPLEMENT(PRStatus) PR_Wait(PRMonitor *mon, PRIntervalTime ticks) {
    PRThread *me = PR_GetCurrentThread();
    PRStatus retval;
    int count = mon->entryCount;

    //printf("%lx is waiting on monitor %lx, ticks are %ld\n", me, mon, ticks);

    mon->entryCount = 0;
    if (mon->cvar->lock->owner != me) {
        return PR_FAILURE;
    }
    retval = PR_WaitCondVar(mon->cvar, ticks);
    //printf("%lx is done waiting on monitor", me);
    mon->entryCount = count;
    return retval;
}

/*
** Notify a thread waiting on the monitor's condition variable. If a thread
** is waiting on the condition variable (using PR_Wait) then it is awakened
** and attempts to reenter the monitor.
*/
PR_IMPLEMENT(PRStatus) PR_Notify(PRMonitor *mon) {
    PRThread *me = PR_GetCurrentThread();
    //printf("%lx notifying monitor %lx, owner is %lx, count is %lx\n", me, mon, mon->cvar->lock->owner, mon->entryCount);
    if (mon->cvar->lock->owner != me) {
        return PR_FAILURE;
    }

    return PR_NotifyCondVar(mon->cvar);
}

/*
** Notify all of the threads waiting on the monitor's condition variable.
** All of threads waiting on the condition are scheduled to reenter the
** monitor.
*/
PR_IMPLEMENT(PRStatus) PR_NotifyAll(PRMonitor *mon) {
    PRThread *me = PR_GetCurrentThread();
    //printf("%lx notifyall on monitor %lx, owner is %lx, count is %lx\n", me, mon, mon->cvar->lock->owner, mon->entryCount);
    if (mon->cvar->lock->owner != me) {
        return PR_FAILURE;
    }
    return PR_NotifyAllCondVar(mon->cvar);
}

/*
** Create a new named monitor (named for debugging purposes).
**  Monitors are re-entrant locks with a built-in condition variable.
**
** This may fail if memory is tight or if some operating system resource
** is low.
*/
PR_IMPLEMENT(PRMonitor*) PR_NewNamedMonitor(const char* name) {
    PRMonitor *retval = PR_NewMonitor();
    if (retval != NULL) {
        retval->name = PR_Malloc(strlen(name) + 1);
        if (retval->name == NULL) {
            PR_DestroyMonitor(retval);
            retval = NULL;
        } else {
            strcpy(retval->name, name);
        }
    }
    return retval;
}
