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

#ifndef nspr_amigaos_threads_h___
#define nspr_amigaos_threads_h___

#include <primpl.h>

#include <exec/ports.h>
#include <dos/var.h>

/*
 * Returns the number of threads awoken or 0 if a timeout occurred;
 */
#define _MD_PAUSE_CPU                     _PauseCpu
#define _MD_CLEANUP_BEFORE_EXIT           _CleanupBeforeExit
#define _MD_EXIT                          _Exit


/* Threads related */
#define _MD_CURRENT_THREAD                PR_GetCurrentThread

void _PR_MD_Wait(PRThread *thread, PRBool interruptable);
void _PR_MD_Signal(PRThread *thread);

/*
 * Structure passed to the process spawning thread 
 */
struct _MDProcess {
    struct PRThread *executeThread;
    PRLock *lock;       /* I need to wait until the process */
    PRCondVar *condVar; /* thread is done with the PRProcessAttr structure */
    char *const *argv;  /* program arguments */
    char *const *envp;  /* environment */
    const PRProcessAttr *attr; /* process attributes */
    PRInt32 returnCode; /* return code from the process */
};


// Stubs

#define _MD_CREATE_PROCESS _CreateProcess
#define _MD_DETACH_PROCESS _DetachProcess
#define _MD_WAIT_PROCESS _WaitProcess
#define _MD_KILL_PROCESS _KillProcess
#define _MD_INIT_SEGS()
#define _MD_EARLY_INIT _MD_Early_Init
#define _MD_FINAL_INIT()
#define _MD_INIT_FILEDESC

#define _MD_ALLOC_SEGMENT
#define _MD_FREE_SEGMENT

#endif /* nspr_amigaos_threads_h___ */
