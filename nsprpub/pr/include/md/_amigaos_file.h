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

#ifndef nspr_amigaos_file_h___
#define nspr_amigaos_file_h___

#include <dos/dos.h>
#include <dos/dosextens.h>

/*
 * Here we define all machine dependent (MD) translation for
 * the file nspr api (src/io/prfile.c). The implemented
 * functions can be fund in (src/md/amiga/afile.c)
 */

#define _MD_OPEN                 _Open
#define _MD_OPEN_FILE            _Open
#define _MD_DELETE               _Delete
#define _MD_GETFILEINFO          _GetFileInfo
#define _MD_GETFILEINFO64        _GetFileInfo64
#define _MD_RENAME               _Rename
#define _MD_ACCESS               _Access
#define _MD_CLOSE_FILE           _Close
#define _MD_READ                 _Read
#define _MD_WRITE                _Write
#define _MD_GETOPENFILEINFO      _GetOpenFileInfo
#define _MD_GETOPENFILEINFO64    _GetOpenFileInfo64
#define _MD_LSEEK                _Seek
#define _MD_LSEEK64              _Seek64
#define _MD_FSYNC                _Sync
#define _MD_SET_FD_INHERITABLE(fd, inh) (PR_SUCCESS)
#ifdef MOZ_UNICODE
#define _MD_OPEN_FILE_UTF16      _OpenUtf16
#define _MD_GETFILEINFO64_UTF16  _GetOpenFileInfo64Utf16
#endif /* MOZ_UNICODE */

/* Since amitcp.library socket's are private per thread, I need to
 * keep track of who created it so I can duped it to the thread who wants it
 */
typedef struct {
    int type;
    int domain;
    int protocol;
    int private_idx;
} _MDSocket;

struct _MDFileDesc {
    BPTR osfd;
};

struct _MDSharedMemory {
    PRInt32 count;
};

NSPR_API(PRInt32)  _Open(const char *name, PRIntn osflags, PRIntn mode);
NSPR_API(PRStatus) _Delete(const char *name);
NSPR_API(PRStatus) _GetFileInfo(const char *fn, PRFileInfo *info);
NSPR_API(PRStatus) _GetFileInfo64(const char *fn, PRFileInfo64 *info);
NSPR_API(PRStatus) _Rename(const char *from, const char *to);
NSPR_API(PRStatus) _Access(const char *name, PRAccessHow how);
NSPR_API(PRStatus) _Close(PRInt32 osfd);
NSPR_API(PRInt32)  _Read(PRFileDesc *fd, void *buf, PRInt32 amount);
NSPR_API(PRInt32)  _Write(PRFileDesc *fd, const void *buf, PRInt32 amount);
NSPR_API(PRStatus) _GetOpenFileInfo(const PRFileDesc *fd, PRFileInfo *info);
NSPR_API(PRStatus) _GetOpenFileInfo64(const PRFileDesc *fd, PRFileInfo64 *info);
NSPR_API(PRInt32)  _Seek(PRFileDesc *fd, PRInt32 offset, PRSeekWhence whence);
NSPR_API(PRInt64)  _Seek64(PRFileDesc *fd, PRInt64 offset, PRSeekWhence whence);
NSPR_API(PRStatus) _Sync(PRFileDesc *fd);
#ifdef MOZ_UNICODE
NSPR_API(PRInt32)  _OpenUtf16(const PRUnichar *name, PRIntn osflags, PRIntn mode);
NSPR_API(PRStatus) _GetOpenFileInfo64Utf16(const PRFileDesc *fd, PRFileInfo64 *info);
#endif /* MOZ_UNICODE */

#endif /* nspr_amigaos_file_h___ */
