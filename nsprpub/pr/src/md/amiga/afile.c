/* -*- Mode: C++; tab-width: 8; c-basic-offset: 8 -*- */
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

#include "primpl.h"

/* File I/O related */
/*
 * Opens a file for reading, writing, or both. Also used to create a file.
 */
PRFileDesc* _Open(const char *name, PRIntn osflags, PRIntn mode) {
}

/*
 * Deletes a file.
 */
PRStatus _Delete(const char *name) {
}

/*
 * Gets information about a file with a specified pathname. File size is expressed as a 32-bit integer.
 */
PRStatus _GetFileInfo(const char *fn,PRFileInfo *info) {
}

/*
 * Gets information about a file with a specified pathname. File size is expressed as a 64-bit integer.
 */
PRStatus _GetFileInfo64(const char *fn,PRFileInfo64 *info) {
}

/*
 * Renames a file.
 */
PRStatus _Rename(const char *from, const char *to) {
}

/*
 * Determines the accessibility of a file.
 */
PRStatus _Access(const char *name, PRAccessHow how) {
}

/*
 * Closes a file descriptor.
 */
PRStatus _Close(PRFileDesc *osfd) {
}

/*
 * Reads bytes from a file or socket.
 */
PRInt32 _Read(PRFileDesc *fd, void *buf, PRInt32 amount) {
}

/*
 * Writes a buffer of data to a file or socket.
 */
PRInt32 _Write(PRFileDesc *fd, const void *buf, PRInt32 amount) {
}

/*
 * Writes data to a socket from multiple buffers.
 */
PRInt32 _WriteV(PRFileDesc *fd, const struct PRIOVec *iov,PRInt32 iov_size, PRIntervalTime timeout) {
}

/*
 * Gets an open file's information. File size is expressed as a 32-bit integer.
 */
PRStatus _GetOpenFileInfo(const PRFileDesc *fd, PRFileInfo *info) {
}

/*
 * Gets an open file's information. File size is expressed as a 64-bit integer.
 */
PRStatus _GetOpenFileInfo64(const PRFileDesc *fd, PRFileInfo64 *info) {
}
 
/*
 * Moves the current read-write file pointer by an offset expressed as a 32-bit integer.
 */
PRInt32 _Seek64 (PRFileDesc *fd, PRInt32 offset, int whence) {
}

/*
 * Moves the current read-write file pointer by an offset expressed as a 64-bit integer.
 */
PRInt64 _Seek64 (PRFileDesc *fd, PRInt64 offset, int whence) {
}

/*
 * Synchronizes any buffered data for a file descriptor to its backing device (disk).
 */
PRStatus _Sync(PRFileDesc *fd) {
}


/*
 * Opens the directory with the specified pathname.
 */
PRDir* _OpenDir(PRDir *md,const char *name) {
}

/*
 * Gets a pointer to the next entry in the directory.
 */
PRDirEntry* _ReadDir(PRDir *md, PRIntn flags) {
}

/*
 * Closes the specified directory.
 */
PRStatus _CloseDir(PRDir *md) {
}

/*
 * Creates a directory with a specified name and access mode.
 */
PRStatus _MakeDir(const char *name,PRIntn mode) {
}

/*
 * Removes a directory with a specified name.
 */
PRStatus _RemoveDir(const char *name) {
}




