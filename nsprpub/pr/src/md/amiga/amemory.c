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

#include <assert.h>
#include <sys/param.h>

#include "primpl.h"

static PRCList memoryList;

static struct SignalSemaphore memoryLock;

/*
 * Better than Forbid/Permit since it only blocks NSPR-related things 
 */
static void _PR_ObtainMemoryLock(void) {
    ObtainSemaphore(&memoryLock);

}

static void _PR_ReleaseMemoryLock(void) {
    ReleaseSemaphore(&memoryLock);
}

void _PR_Init_Memory(void) {
    PR_INIT_CLIST(&memoryList);
    InitSemaphore(&memoryLock);
}

void _PR_Release_Memory(void) {
    if (!PR_CLIST_IS_EMPTY(&memoryList)) {
        PRCList *next;
        for (next = PR_LIST_HEAD(&memoryList); next != &memoryList;) {
            struct _MDMemPtr *mp = (struct _MDMemPtr *)next;
            PRCList *tmp = next;
            next = PR_NEXT_LINK(next);
            FreeMem(mp, mp->size);
        }
    }
}
            
void *PR_MD_malloc( size_t size ) {
    struct _MDMemPtr *pr; 
    if (!_pr_initialized) _PR_ImplicitInitialization();

    pr = AllocMem(size + sizeof(struct _MDMemPtr), 
        MEMF_PUBLIC | MEMF_CLEAR);
    if (pr == NULL) {
        return NULL;
    }

    pr->size = size + sizeof(struct _MDMemPtr);
    //printf("Allocating memory %lx, size %d\n", pr, pr->size);
    _PR_ObtainMemoryLock();
    PR_APPEND_LINK((PRCList *)pr, &memoryList);
    _PR_ReleaseMemoryLock();
    return ((char *)pr + sizeof(struct _MDMemPtr));
}

void *PR_MD_calloc( size_t n, size_t size ) {
    return PR_MD_malloc(n * size);
}

void *PR_MD_realloc( void* old_blk, size_t size ) {
    if (old_blk == NULL) {
        return PR_MD_malloc(size);
    } else {
        void *newblock = PR_MD_malloc(size);
        if (newblock == NULL) {
            return old_blk;
        } else {
            struct _MDMemPtr *ob = (struct _MDMemPtr *)
                ((char *)old_blk - sizeof(struct _MDMemPtr));
            int sz = MIN(ob->size, size);
            memcpy(newblock, old_blk, sz);
            PR_MD_free(old_blk);
            return newblock;
        }
    }
}

void PR_MD_free( void *ptr ) {
    if (ptr != NULL) {
        struct _MDMemPtr *mp = (struct _MDMemPtr *)
            ((char *)ptr - sizeof(struct _MDMemPtr));
        _PR_ObtainMemoryLock();
        PR_REMOVE_LINK((PRCList *)mp);
        _PR_ReleaseMemoryLock();
        FreeMem(mp, mp->size);
    }
}

