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

#include "prtypes.h"
#include "prio.h"
#include <dirent.h>
//#include <errno.h>


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
#define PR_PATH_SEPARATOR               ';'
#define PR_PATH_SEPARATOR_STR           ";"

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

/* Machine-dependent (MD) data structures */

/** may not be suitable for amiga */
struct _MDThread {
};

/** may not be suitable for amiga */
struct _MDThreadStack {
};

/** may not be suitable for amiga */
struct _MDLock {
};

/** may not be suitable for amiga */
struct _MDSemaphore {
};

/** may be suitable for amiga */
struct _MDCVar {
};

/** may not be suitable for amiga */
struct _MDSegment {
};

/** may not be suitable for amiga */
struct _MDCPU {
};

/* CPU Stuff */

// #define _MD_INIT_CPUS _MD_init_cpus
// #define _MD_WAKEUP_CPUS _MD_wakeup_cpus
// #define _MD_START_INTERRUPTS _MD_start_interrupts
// #define _MD_STOP_INTERRUPTS _MD_stop_interrupts
// #define _MD_DISABLE_CLOCK_INTERRUPTS _MD_disable_clock_interrupts
// #define _MD_BLOCK_CLOCK_INTERRUPTS _MD_block_clock_interrupts
// #define _MD_UNBLOCK_CLOCK_INTERRUPTS _MD_unblock_clock_interrupts
// #define _MD_CLOCK_INTERRUPT _MD_clock_interrupt
// #define _MD_INIT_STACK _MD_init_stack
// #define _MD_CLEAR_STACK _MD_clear_stack
// #define _MD_GET_INTSOFF _MD_get_intsoff
// #define _MD_SET_INTSOFF _MD_set_intsoff
#define _MD_CURRENT_CPU _MD_current_cpu
// #define _MD_SET_CURRENT_CPU _MD_set_current_cpu
// #define _MD_INIT_RUNNING_CPU _MD_init_running_cpu
// #define _MD_PAUSE_CPU _MD_pause_cpu

/* CPU Stuff */

// NSPR_API(void) _MD_init_cpus();
// NSPR_API(void) _MD_wakeup_cpus();
// NSPR_API(void) _MD_start_interrupts(void);
// NSPR_API(void) _MD_stop_interrupts(void);
// NSPR_API(void) _MD_disable_clock_interrupts(void);
// NSPR_API(void) _MD_block_clock_interrupts(void);
// NSPR_API(void) _MD_unblock_clock_interrupts(void);
// NSPR_API(void) _MD_clock_interrupt(void);
// NSPR_API(void) _MD_init_stack(PRThreadStack *ts, PRIntn redzone);
// NSPR_API(void) _MD_clear_stack(PRThreadStack* ts);
// NSPR_API(PRInt32) _MD_get_intsoff(void);
// NSPR_API(void) _MD_set_intsoff(PRInt32 _val);
// NSPR_API(_PRCPU*) _MD_current_cpu(void);
// NSPR_API(void) _MD_set_current_cpu(_PRCPU *cpu);
// NSPR_API(void) _MD_init_running_cpu(_PRCPU *cpu);
// NSPR_API(PRInt32) _MD_pause_cpu(PRIntervalTime timeout);



/* File I/O */

/* don't need any I/O initializations */
// #define _MD_INIT_IO()
// #define _MD_INIT_FILEDESC(fd)

// #define _MD_MAKE_NONBLOCK _MD_make_nonblock
// #define _MD_SET_FD_INHERITABLE _MD_set_fd_inheritable
// #define _MD_INIT_FD_INHERITABLE _MD_init_fd_inheritable
// #define _MD_QUERY_FD_INHERITABLE _MD_query_fd_inheritable
#define _MD_OPEN _Open
#define _MD_OPEN_FILE _Open
#define _MD_DELETE _Delete
#define _MD_GETFILEINFO _GetFileInfo
#define _MD_GETFILEINFO64 _GetFileInfo64
#define _MD_RENAME _Rename
#define _MD_ACCESS _Access
#define _MD_CLOSE_FILE _Close
#define _MD_READ _Read
#define _MD_WRITE _Write
#define _MD_WRITEV _Writev
#define _MD_GETOPENFILEINFO _GetOpenFileInfo
#define _MD_GETOPENFILEINFO64 _GetOpenFileInfo64
#define _MD_LSEEK _Seek
#define _MD_LSEEK64 _Seek64
#define _MD_FSYNC _Sync
#define _MD_OPEN_DIR _OpenDir
#define _MD_READ_DIR _ReadDir
#define _MD_CLOSE_DIR _CloseDir
#define _MD_MKDIR _MakeDir
#define _MD_MAKE_DIR _MakeDir
#define _MD_RMDIR _RemoveDir

// #define _MD_STAT stat
// #define _MD_PR_POLL _MD_pr_poll

/* File I/O */

// NSPR_API(void) _MD_init_io(void);
// NSPR_API(void) _MD_make_nonblock(PRFileDesc *fd);
// NSPR_API(void) _MD_init_fd_inheritable(PRFileDesc *fd, PRBool imported);
// NSPR_API(void) _MD_query_fd_inheritable(PRFileDesc *fd);
NSPR_API(PRFileDesc *) _Open(const char *name, PRIntn osflags, PRIntn mode);
NSPR_API(PRStatus) _Delete(const char *name);
NSPR_API(PRStatus) _GetFileInfo(const char *fn, PRFileInfo *info);
NSPR_API(PRStatus) _GetFileInfo64(const char *fn, PRFileInfo64 *info);
NSPR_API(PRStatus) _Rename(const char *from, const char *to);
NSPR_API(PRStatus) _Access(const char *name, PRAccessHow how);
NSPR_API(PRStatus) _Close(PRFileDesc *osfd);
NSPR_API(PRInt32) _Read(PRFileDesc *fd, void *buf, PRInt32 amount);
NSPR_API(PRInt32) _Write(PRFileDesc *fd, const void *buf, PRInt32 amount);
NSPR_API(PRInt32) _Writev(PRFileDesc *fd, const PRIOVec *iov, PRInt32 iov_size, PRIntervalTime timeout);
NSPR_API(PRStatus) _GetOpenFileInfo(const PRFileDesc *fd, PRFileInfo *info);
NSPR_API(PRStatus) _GetOpenFileInfo64(const PRFileDesc *fd, PRFileInfo64 *info);
NSPR_API(PRInt32) _Seek(PRFileDesc *fd, PRInt32 offset, PRSeekWhence whence);
NSPR_API(PRInt64) _Seek64(PRFileDesc *fd, PRInt64 offset, PRSeekWhence whence);
NSPR_API(PRStatus) _Sync(PRFileDesc *fd);
NSPR_API(PRDir*) _OpenDir(PRDir *md,const char *name);
NSPR_API(PRDirEntry*) _ReadDir(PRDir *md, PRIntn flags);
NSPR_API(PRStatus) _CloseDir(PRDir *md);
NSPR_API(PRStatus) _MakeDir(const char *name, PRIntn mode);
NSPR_API(PRStatus) _RemoveDir(const char *name);
// NSPR_API(PRInt32) _MD_stat(const char *name, struct stat *buf);
// NSPR_API(PRInt32) _MD_pr_poll(PRPollDesc *pds, PRIntn npds, PRIntervalTime timeout);

#endif /* nspr_amigaos_defs_h___ */



