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

#ifndef nspr_amigaos_defs_h___
#define nspr_amigaos_defs_h___

#include <dirent.h>
#include <errno.h>


#define _PR_SI_ARCHITECTURE "m68k"
#define _PR_SI_SYSNAME "Amiga compatible"

struct _MDFileMap {
    PRIntn prot;
    PRIntn flags;
    PRBool isAnonFM; /* when true, PR_CloseFileMap() must close the related fd */
};

struct _MDDir {
        DIR *d;
};

struct _MDProcess {
    pid_t pid;
};

struct _MDFileDesc {
    int osfd;
};

#define HAVE_BSD_FLOCK 1
#define PR_DIRECTORY_SEPARATOR          '/'
#define PR_DIRECTORY_SEPARATOR_STR      "/"
#define PR_PATH_SEPARATOR               ':'
#define PR_PATH_SEPARATOR_STR           ":"

#define _PR_STAT_HAS_ONLY_ST_ATIME
#define _PR_NO_LARGE_FILES

#define USE_SETJMP

typedef struct stat _MDStat64;
typedef PRInt64 _MDOff64_t;

typedef PRIntn (*_MD_Fstat64)(PRIntn osfd, _MDStat64 *buf);
typedef PRIntn (*_MD_Open64)(const char *path, int oflag, ...);
typedef PRIntn (*_MD_Stat64)(const char *path, _MDStat64 *buf);
typedef _MDOff64_t (*_MD_Lseek64)(PRIntn osfd, _MDOff64_t, PRIntn whence);
typedef void* (*_MD_Mmap64)(
    void *addr, PRSize len, PRIntn prot, PRIntn flags,
    PRIntn fildes, _MDOff64_t offset);
struct _MD_IOVector
{
    _MD_Open64 _open64;
    _MD_Mmap64 _mmap64;
    _MD_Stat64 _stat64;
    _MD_Fstat64 _fstat64;
    _MD_Lseek64 _lseek64;
};
extern struct _MD_IOVector _md_iovector;

#endif /* nspr_netbsd_defs_h___ */
