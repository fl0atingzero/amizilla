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

#include "_amigaos_dir.h"
#include "_amigaos_file.h"

#include "prtypes.h"
#include "prio.h"
#include <dirent.h>
//#include <errno.h>


#define _PR_SI_ARCHITECTURE   "m68k"
#define _PR_SI_SYSNAME        "Amiga compatible"

struct _MDFileMap {
    PRIntn prot;
    PRIntn flags;
    PRBool isAnonFM; /* when true, PR_CloseFileMap() must close the related fd */
};

struct _MDProcess {
    pid_t pid;
};

#define HAVE_BSD_FLOCK 1

#define HAVE_LONG_LONG

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


/* Thread stuff */

// linsk to the threads/pcthr.c shiuld be reolaced with amiga solution 
#define _MD_CURRENT_THREAD() PR_GetCurrentThread()
// #define _MD_GET_ATTACHED_THREAD _MD_get_attached_thread
// #define _MD_LAST_THREAD _MD_last_thread
// #define _MD_SET_CURRENT_THREAD _MD_set_current_THREAD
// #define _MD_SET_LAST_THREAD _MD_set_last_thread
// #define _MD_INIT_THREAD _MD_init_thread
// #define _MD_EXIT_THREAD _MD_exit_thread
// #define _MD_INIT_ATTACHED_THREAD _MD_init_attached_thread

// #define _MD_SUSPEND_THREAD _MD_suspend_thread
// #define _MD_RESUME_THREAD _MD_resume_thread
// #define _MD_SUSPEND_CPU _MD_suspend_cpu
// #define _MD_RESUME_CPU _MD_resume_cpu
// #define _MD_BEGIN_SUSPEND_ALL _MD_begin_suspend_all
// #define _MD_END_SUSPEND_ALL _MD_end_suspend_all
// #define _MD_BEGIN_RESUME_ALL _MD_begin_resume_all
// #define _MD_END_RESUME_ALL _MD_end_resume_all

// #define _MD_GET_SP _MD_get_sp

// #define _MD_CLEAN_THREAD _MD_clean_thread
// #define _MD_CREATE_PRIMORDIAL_USER_THREAD _MD_create_primordial_user_thread
// #define _MD_CREATE_USER_THREAD _MD_create_user_thread
// #define _MD_INIT_PRIMORDIAL_THREAD _MD_init_primordial_thread
// #define _MD_CREATE_THREAD _MD_create_thread
// #define _MD_YIELD _MD_yield
// #define _MD_SET_PRIORITY _MD_set_priority

// #define _MD_SUSPENDALL _MD_suspendall
// #define _MD_RESUMEALL _MD_resumeall

// #define _MD_SWITCH_CONTEXT _MD_switch_context
// #define _MD_RESTORE_CONTEXT _MD_restore_context

// #define _MD_WAIT _MD_wait
// #define _MD_WAKEUP_WAITER _MD_wakeup_waiter

// #define _MD_SETTHREADAFFINITYMASK _MD_setthreadaffinitymask
// #define _MD_GETTHREADAFFINITYMASK _MD_getthreadaffinitymask



/* File I/O */

/* don't need any I/O initializations */
// #define _MD_INIT_IO()
// #define _MD_INIT_FILEDESC(fd)

// #define _MD_SET_FD_INHERITABLE _MD_set_fd_inheritable
// #define _MD_MAKE_NONBLOCK _MD_make_nonblock
// #define _MD_INIT_FD_INHERITABLE _MD_init_fd_inheritable
// #define _MD_QUERY_FD_INHERITABLE _MD_query_fd_inheritable
#define _MD_WRITEV _Writev

// #define _MD_STAT stat
// #define _MD_PR_POLL _MD_pr_poll

/* File I/O */

// NSPR_API(void) _MD_init_io(void);
// NSPR_API(void) _MD_make_nonblock(PRFileDesc *fd);
// NSPR_API(void) _MD_init_fd_inheritable(PRFileDesc *fd, PRBool imported);
// NSPR_API(void) _MD_query_fd_inheritable(PRFileDesc *fd);
NSPR_API(PRInt32) _Writev(PRFileDesc *fd, const PRIOVec *iov, PRInt32 iov_size, PRIntervalTime timeout);

// NSPR_API(PRInt32) _MD_stat(const char *name, struct stat *buf);
// NSPR_API(PRInt32) _MD_pr_poll(PRPollDesc *pds, PRIntn npds, PRIntervalTime timeout);

#endif /* nspr_amigaos_h___ */



