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

#ifndef nspr_amigaos_dir_h___
#define nspr_amigaos_dir_h___

#include <dos/dos.h>

/*
 * Here we define all machine dependent (MD) translation for
 * the dir nspr api (src/io/prdir.c). The implemented
 * functions can be fund in (src/md/amiga/adir.c)
 */

#define _MD_OPEN_DIR         _OpenDir
#define _MD_READ_DIR         _ReadDir
#define _MD_CLOSE_DIR        _CloseDir
#define _MD_MKDIR            _MakeDir
#define _MD_MAKE_DIR         _MakeDir
#define _MD_RMDIR            _RemoveDir
#ifdef MOZ_UNICODE
#define _MD_OPEN_DIR_UTF16   _OpenDirUtf16
#define _MD_READ_DIR_UTF16   _ReadDirUtf16
#define _MD_CLOSE_DIR_UTF16  _CloseDirUtf16
#endif /* MOZ_UNICODE */


struct _MDDir {
  BPTR                  lock;
  struct FileInfoBlock *info;
};

NSPR_API(PRStatus)   _OpenDir(struct _MDDir *md,const char *name);
NSPR_API(char*)      _ReadDir(struct _MDDir *md, PRIntn flags);
NSPR_API(PRStatus)   _CloseDir(struct _MDDir *md);
NSPR_API(PRStatus)   _MakeDir(const char *name, PRIntn mode);
NSPR_API(PRStatus)   _RemoveDir(const char *name);
#ifdef MOZ_UNICODE
NSPR_API(PRStatus)   _OpenDirUtf16(struct _MDDir *md,const PRUnichar *name);
NSPR_API(PRUnichar*) _ReadDirUtf16(struct _MDDir *md, PRIntn flags);
NSPR_API(PRStatus)   _CloseDirUtf16(struct _MDDir *md);
#endif /* MOZ_UNICODE */

#endif /* nspr_amigaos_dir_h___ */


