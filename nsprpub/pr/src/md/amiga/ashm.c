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

PRSharedMemory * _MD_OpenSharedMemory( 
    const char *name,
    PRSize      size,
    PRIntn      flags,
    PRIntn      mode
) {
    PRStatus rc = PR_SUCCESS;
    int cookie;
    char buf[10];
    PRSharedMemory *shm;
    char        ipcname[PR_IPC_NAME_SIZE];

    rc = _PR_MakeNativeIPCName( name, ipcname, PR_IPC_NAME_SIZE, _PRIPCShm );
    if ( PR_FAILURE == rc ) {
        _PR_MD_MAP_DEFAULT_ERROR( errno );
        PR_LOG( _pr_shm_lm, PR_LOG_DEBUG, 
            ("_MD_OpenSharedMemory(): _PR_MakeNativeIPCName() failed: %s", name ));
        return( NULL );
    }

    shm = PR_NEWZAP( PRSharedMemory );
    if ( NULL == shm ) {
        PR_SetError(PR_OUT_OF_MEMORY_ERROR, 0 );
        PR_LOG(_pr_shm_lm, PR_LOG_DEBUG, ( "PR_OpenSharedMemory: New PRSharedMemory out of memory")); 
        return( NULL );
    }

    shm->ipcname = (char*)PR_MALLOC( strlen( ipcname ) + 1 );
    if ( NULL == shm->ipcname ) {
        PR_SetError(PR_OUT_OF_MEMORY_ERROR, 0 );
        PR_LOG(_pr_shm_lm, PR_LOG_DEBUG, ( "PR_OpenSharedMemory: New shm->ipcname out of memory")); 
        return( NULL );
    }

    /* copy args to struct */
    strcpy( shm->ipcname, ipcname );
    shm->size = size; 
    shm->mode = mode; 
    shm->flags = flags;
    shm->ident = _PR_SHM_IDENT;

    /* create the file first */
    if ( flags & PR_SHM_CREATE )  {
        int osfd = open( shm->ipcname, (O_RDWR | O_CREAT), shm->mode );
        if ( -1 == osfd ) {
            _PR_MD_MAP_OPEN_ERROR( errno );
            PR_FREEIF( shm->ipcname );
            PR_DELETE( shm );
            return( NULL );
        } 
        cookie = htonl(SHARED_MEMORY_MAGIC_COOKIE);
        write(osfd, &cookie, sizeof(cookie));
        sprintf(buf, "%lx", shm);
        write(osfd, buf, strlen(buf));
        if ( close(osfd) == -1 ) {
            _PR_MD_MAP_CLOSE_ERROR( errno );
            PR_FREEIF( shm->ipcname );
            PR_DELETE( shm );
            return( NULL );
        }
    } else {
        int osfd = open(ipcname, O_RDONLY, mode);
        char buf[10];
        if (-1 == osfd) {
            _PR_MD_MAP_OPEN_ERROR(errno);
            return NULL;
        }

        read(osfd, &cookie, sizeof(cookie));
        cookie = ntohl(cookie);
        if (cookie != SHARED_MEMORY_MAGIC_COOKIE) {
            /* Any better error code for this */
            PR_SetError(PR_OPERATION_NOT_SUPPORTED_ERROR, 0);
        } else {
            read(osfd, buf, sizeof(buf));
            shm = (struct PRSharedMemory *)atol(buf);
        }
    }

    shm->handle = PR_Realloc(shm->handle, size);
    return( shm );
}

void * _MD_AttachSharedMemory( PRSharedMemory *shm, PRIntn flags ) {
    return shm->handle;
}

PRStatus _MD_DetachSharedMemory( PRSharedMemory *shm, void *addr ) {
    return PR_SUCCESS;
}


extern PRStatus _MD_CloseSharedMemory( PRSharedMemory *shm ) {
    PR_ASSERT( shm->ident == _PR_SHM_IDENT );

    PR_FREEIF(shm->ipcname);
    PR_DELETE(shm->handle);
    PR_DELETE(shm);

    return PR_SUCCESS;
}

PRStatus _MD_DeleteSharedMemory( const char *name ) {
    PRStatus rc = PR_SUCCESS;
    key_t   key;
    int     id;
    PRIntn  urc;
    char        ipcname[PR_IPC_NAME_SIZE];

    rc = _PR_MakeNativeIPCName( name, ipcname, PR_IPC_NAME_SIZE, _PRIPCShm );
    if ( PR_FAILURE == rc )
    {
        PR_SetError( PR_UNKNOWN_ERROR , errno );
        PR_LOG( _pr_shm_lm, PR_LOG_DEBUG, 
            ("_MD_DeleteSharedMemory(): _PR_MakeNativeIPCName() failed: %s", name ));
        return(PR_FAILURE);
    }

    urc = unlink( ipcname );
    if ( -1 == urc ) {
        _PR_MD_MAP_UNLINK_ERROR( errno );
        PR_LOG( _pr_shm_lm, PR_LOG_DEBUG, 
            ("_MD_DeleteSharedMemory(): unlink() failed: %s", ipcname ));
        return(PR_FAILURE);
    }
    return PR_SUCCESS;
}
