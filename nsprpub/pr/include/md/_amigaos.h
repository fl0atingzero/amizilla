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

#ifndef nspr_amigaos_h___
#define nspr_amigaos_h___

#include "prtypes.h"
#include "prio.h"
#include <dirent.h>
//#include <errno.h>


#define _PR_SI_ARCHITECTURE   "m68k"
#define _PR_SI_SYSNAME        "Amiga compatible"

typedef enum { FAILURE = -1, SUCCESS = 0, TIMEDOUT = 1, INTERRUPTED = 2} _PR_MD_Timeout;
_PR_MD_Timeout _PR_Sleep(PRIntervalTime);

struct _MDFileMap {
    PRIntn prot;
    PRIntn flags;
  PRBool isAnonFM; // when true, PR_CloseFileMap() must close the related fd 
};

/**
 * Used for malloc
 */
struct _MDMemPtr {
  PRCList list;
  PRUint32 size;
};

#define HAVE_BSD_FLOCK 1
#define PR_HAVE_AMIGA_NAMED_SHARED_MEMORY
#define _PR_HAVE_SOCKADDR_LEN

#define HAVE_STACK_GROWING_UP
#undef USE_SETJMP

#define PR_DIRECTORY_SEPARATOR          '/'
#define PR_DIRECTORY_SEPARATOR_STR      "/"
#define PR_PATH_SEPARATOR               ';'
#define PR_PATH_SEPARATOR_STR           ";"

#define _MD_DEFAULT_STACK_SIZE	65536L  // TODO: check if fits for amigaOS

#define _PR_ATHREADS

#define _MD_GET_ENV getenv
#define _MD_PUT_ENV putenv
#define _MD_GETHOSTNAME _MD_gethostname

void *PR_MD_malloc( size_t size );
void *PR_MD_calloc( size_t n, size_t size );
void *PR_MD_realloc( void* old_blk, size_t size );
void  PR_MD_free( void *ptr );
void _PR_Init_Memory( void );
void _PR_Release_Memory( void );

#include "_amigaos_dir.h"
#include "_amigaos_file.h"
#include "_amigaos_threads.h"
#include "_amigaos_time.h"
#include "_amiga_errors.h"

/*
 * Amiga specific includes
 */
#include <exec/memory.h>
#include <exec/ports.h>
#include <proto/utility.h>
#include <dos/dostags.h>
#include <exec/ports.h>
#include <proto/dos.h>
#include <proto/exec.h>

#endif /* nspr_amigaos_h___ */



