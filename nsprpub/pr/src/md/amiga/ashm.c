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
#include <prshm.h>
#include <prerr.h>
#include <prmem.h>
#include "primpl.h"
#include <fcntl.h>
#include <errno.h>

extern PRLogModuleInfo *_pr_shm_lm;

#define SHARED_MEMORY_MAGIC_COOKIE 0xadeadc03

static PRStatus readShmCookie(PRFileDesc *osfd, PRSharedMemory *shm) {
    PRInt32 cookie;

    PR_Read(osfd, &cookie, sizeof(cookie));
    cookie = ntohl(cookie);
    if (cookie != SHARED_MEMORY_MAGIC_COOKIE) {
        /* Any better error code for this */
        PR_SetError(PR_OPERATION_NOT_SUPPORTED_ERROR, 0);
        return PR_FAILURE;
    } else {
        char buf[20];
        PRInt32 length;
        PR_Read(osfd, &length, sizeof(length));
        length = ntohl(length);
        memset(buf, 0, sizeof(buf));
        PR_Read(osfd, buf, length);
        shm->handle = (struct _MDSharedMemory *)atol(buf);
        Forbid();
        shm->handle->count++;
        Permit();
    }
    return PR_SUCCESS;
}

PRSharedMemory * _MD_OpenSharedMemory( 
    const char *name,
    PRSize      size,
    PRIntn      flags,
    PRIntn      mode
) {
    PRStatus rc = PR_SUCCESS;
    int cookie;
    PRSharedMemory *shm = NULL;
    PRFileDesc *osfd = NULL;
    char ipcname[PR_IPC_NAME_SIZE];

    rc = _PR_MakeNativeIPCName( name, ipcname, PR_IPC_NAME_SIZE, _PRIPCShm );
    if (PR_FAILURE == rc) {
        _PR_MD_MAP_DEFAULT_ERROR(errno);
        PR_LOG(_pr_shm_lm, PR_LOG_DEBUG, 
            ("_MD_OpenSharedMemory(): _PR_MakeNativeIPCName() failed: %s", name ));
        goto error;
    }

    shm = PR_NEWZAP(PRSharedMemory);
    if (NULL == shm) {
        PR_SetError(PR_OUT_OF_MEMORY_ERROR, 0);
        PR_LOG(_pr_shm_lm, PR_LOG_DEBUG, ( "PR_OpenSharedMemory: New PRSharedMemory out of memory")); 
        goto error;
    }

    shm->ipcname = (char *)PR_MALLOC(strlen(ipcname) + 1);
    if (NULL == shm->ipcname) {
        PR_SetError(PR_OUT_OF_MEMORY_ERROR, 0);
        PR_LOG(_pr_shm_lm, PR_LOG_DEBUG, ("PR_OpenSharedMemory: New shm->ipcname out of memory")); 
        goto error;
    }

    /* copy args to struct */
    strcpy(shm->ipcname, ipcname);
    shm->size = size; 
    shm->mode = mode; 
    shm->flags = flags;
    shm->ident = _PR_SHM_IDENT;

    /* create the file first */
    if (flags & PR_SHM_CREATE)  {
        int openflags = PR_CREATE_FILE;
        PRFileInfo fi;
        if (flags & PR_SHM_EXCL)
            openflags |= PR_EXCL;

        osfd = PR_Open(shm->ipcname, openflags, mode);
        if (osfd == NULL) {
            goto error;
        } 

        if (PR_GetOpenFileInfo(osfd, &fi) == PR_SUCCESS && fi.size > 0) {
            if (readShmCookie(osfd, shm) == PR_FAILURE) {
                goto error;
            }
        } else {
            char buf[20];
            /* I use AllocVec so someone else can delete it */
            shm->handle = (struct _MDSharedMemory *)AllocVec(size + sizeof(struct _MDSharedMemory), MEMF_PUBLIC | MEMF_CLEAR);
            if (shm->handle == NULL) {
                goto error;
            }
            shm->handle->count = 1;
            cookie = htonl(SHARED_MEMORY_MAGIC_COOKIE);
            PR_Write(osfd, &cookie, sizeof(cookie));
            sprintf(buf, "%ld", shm->handle);
            cookie = htonl(strlen(buf));
            PR_Write(osfd, &cookie, sizeof(cookie));
            PR_Write(osfd, buf, strlen(buf));
        }
        PR_Close(osfd);
    } else {
        osfd = PR_Open(ipcname, PR_RDONLY, mode);
        if (NULL == osfd) {
            goto error;
        }
        if (readShmCookie(osfd, shm) == PR_FAILURE) 
            goto error;

        PR_Close(osfd);
    }

    return shm;

error:
    if (osfd != NULL)
        PR_Close(osfd);
    PR_FREEIF(shm->handle);
    PR_FREEIF(shm->ipcname);
    PR_FREEIF(shm);
    return NULL;
}

void * _MD_AttachSharedMemory( PRSharedMemory *shm, PRIntn flags ) {
    return (void *)((char *)shm->handle + sizeof(struct _MDSharedMemory));
}

PRStatus _MD_DetachSharedMemory( PRSharedMemory *shm, void *addr ) {
    return PR_SUCCESS;
}


extern PRStatus _MD_CloseSharedMemory( PRSharedMemory *shm ) {
    PR_ASSERT( shm->ident == _PR_SHM_IDENT );

    Forbid();
    shm->handle->count--;
    if (shm->handle->count == 0) {
        FreeVec(shm->handle);
    }
    Permit();

    PR_FREEIF(shm->ipcname);
    PR_DELETE(shm);

    return PR_SUCCESS;
}

PRStatus _MD_DeleteSharedMemory(const char *name) {
    PRStatus rc;
    char ipcname[PR_IPC_NAME_SIZE];

    rc = _PR_MakeNativeIPCName(name, ipcname, PR_IPC_NAME_SIZE, _PRIPCShm);
    if (rc == PR_FAILURE) {
        PR_SetError( PR_UNKNOWN_ERROR , errno );
        PR_LOG( _pr_shm_lm, PR_LOG_DEBUG, 
            ("_MD_DeleteSharedMemory(): _PR_MakeNativeIPCName() failed: %s", name ));
        return PR_FAILURE;
    }

    return PR_Delete(ipcname);
}
