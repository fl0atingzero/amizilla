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

/*
 * Define the interprocess named semaphore functions.
 * There are three implementations:
 * 1. POSIX semaphore based;
 * 2. System V semaphore based;
 * 3. unsupported (fails with PR_NOT_IMPLEMENTED_ERROR).
 */

#include "primpl.h"
#include "obsolete/prsem.h"
#include <errno.h>
#include <fcntl.h>

/* Stolen from ptsynch.c */

#define SEMAPHORE_MAGIC_COOKIE 0xdeadbeef

/**************************************************************/
/**************************************************************/
/**************************SEMAPHORES**************************/
/**************************************************************/
/**************************************************************/
PR_IMPLEMENT(void) PR_PostSem(PRSemaphore *semaphore)
{
    PR_Lock(semaphore->cvar->lock);
    PR_NotifyCondVar(semaphore->cvar);
    semaphore->count += 1;
    PR_Unlock(semaphore->cvar->lock);
}  /* PR_PostSem */

PR_IMPLEMENT(PRStatus) PR_WaitSem(PRSemaphore *semaphore)
{
    PRStatus status = PR_SUCCESS;
    PR_Lock(semaphore->cvar->lock);
    while ((semaphore->count == 0) && (PR_SUCCESS == status))
        status = PR_WaitCondVar(semaphore->cvar, PR_INTERVAL_NO_TIMEOUT);
    if (PR_SUCCESS == status) semaphore->count -= 1;
    PR_Unlock(semaphore->cvar->lock);
    return status;
}  /* PR_WaitSem */

PR_IMPLEMENT(void) PR_DestroySem(PRSemaphore *semaphore) {
    PR_DestroyLock(semaphore->cvar->lock);
    PR_DestroyCondVar(semaphore->cvar);
    PR_DELETE(semaphore);
}  /* PR_DestroySem */

PR_IMPLEMENT(PRSemaphore*) PR_NewSem(PRUintn value) {
    PRSemaphore *semaphore;

    if (!_pr_initialized) _PR_ImplicitInitialization();

    semaphore = PR_NEWZAP(PRSemaphore);
    if (NULL != semaphore) {
        PRLock *lock = PR_NewLock();
        if (NULL != lock) {
            semaphore->cvar = PR_NewCondVar(lock);
            if (NULL != semaphore->cvar) {
                semaphore->count = value;
                return semaphore;
            }
            PR_DestroyLock(lock);
        }
        PR_DELETE(semaphore);
    }
    return NULL;
}


static PRSem *readSemCookie(PRFileDesc *osfd) {
    PRInt32 cookie;
    PRInt32 size;

    PR_Read(osfd, &cookie, sizeof(cookie));
    cookie = ntohl(cookie);
    if (cookie != SEMAPHORE_MAGIC_COOKIE) {
        /* Any better error code for this */
        PR_SetError(PR_OPERATION_NOT_SUPPORTED_ERROR, 0);
        return NULL;
    } else {
        char buf[20];

        PR_Read(osfd, &size, sizeof(size));
        size = ntohl(size);
        memset(buf, 0, sizeof(buf));
        PR_Read(osfd, buf, size);
        return (struct PRSem *)atol(buf);
    }
}

PR_IMPLEMENT(PRSem *) PR_OpenSemaphore(
    const char *name,PRIntn flags, PRIntn mode, PRUintn value)
{
    PRSem *sem = NULL;
    PRIntn i;
    char osname[PR_IPC_NAME_SIZE];
    PRFileDesc *osfd = NULL;
    int cookie;

    if (_PR_MakeNativeIPCName(name, osname, sizeof(osname), _PRIPCSem)
        == PR_FAILURE) {
        return NULL;
    }

    /* Make sure the file exists before calling ftok. */
    if (flags & PR_SEM_CREATE) {
        PRFileInfo fi;
        int openflags = PR_CREATE_FILE;
        
        if (flags & PR_SEM_EXCL)
            openflags |= PR_EXCL;

        osfd = PR_Open(osname, openflags, mode);
        if (osfd == NULL) {
            goto error;
        }

        if (PR_GetOpenFileInfo(osfd, &fi) == PR_SUCCESS && fi.size > 0) {
            if ((sem = readSemCookie(osfd)) == NULL)
                goto error;
        } else {    
            char buf[20];
            sem = PR_NEWZAP(PRSem);
            if (sem == NULL) {
                PR_SetError(PR_OUT_OF_MEMORY_ERROR, 0);
                goto error;
            }
            sem->sem = PR_NewSem(value);
            sem->owner = FindTask(NULL);
            if (sem->sem == NULL) {
                PR_SetError(PR_OUT_OF_MEMORY_ERROR, 0);
                goto error;
            }

            cookie = htonl(SEMAPHORE_MAGIC_COOKIE);
            PR_Write(osfd, &cookie, sizeof(cookie));
            sprintf(buf, "%ld", sem);
            cookie = htonl(strlen(buf));
            PR_Write(osfd, &cookie, sizeof(cookie));
            PR_Write(osfd, buf, strlen(buf));
        }
    } else {
        osfd = PR_Open(osname, PR_RDONLY, mode);
        if (osfd == NULL) {
            goto error;
        }

        sem = readSemCookie(osfd);
        if (sem == NULL)
            goto error;
    }

    PR_Close(osfd);
    return sem;
error:
    if (osfd != NULL)
        PR_Close(osfd);

    PR_FREEIF(sem);
    return NULL;
}

PR_IMPLEMENT(PRStatus) PR_WaitSemaphore(PRSem *sem) {
    return PR_WaitSem(sem->sem);
}

PR_IMPLEMENT(PRStatus) PR_PostSemaphore(PRSem *sem) {
    PR_PostSem(sem->sem);
    return PR_SUCCESS;
}

PR_IMPLEMENT(PRStatus) PR_CloseSemaphore(PRSem *sem) {
    if (sem->owner == FindTask(NULL)) {
        PR_DestroySem(sem->sem);
        PR_DELETE(sem);
    }
    return PR_SUCCESS;
}

PR_IMPLEMENT(PRStatus) PR_DeleteSemaphore(const char *name) {
    char osname[PR_IPC_NAME_SIZE];

    if (_PR_MakeNativeIPCName(name, osname, sizeof(osname), _PRIPCSem)
        == PR_FAILURE) {
        return PR_FAILURE;
    }
    
    return PR_Delete(osname);
}
