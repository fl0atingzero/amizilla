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

/* 
 * both devices/timer.h and sys/time.h (included from primpl.h) define 
 * struct timeval. sys/time.h detects the other definiton while 
 * devices/timer.h does not, hence we must include device/timer.h first.
 */
#include <devices/timer.h>

#include "primpl.h"

/*
 * Amiga specificy includes
 */
#include <dos/dos.h>
#include <exec/memory.h>
#include <proto/dos.h>
#include <proto/exec.h>

/* File I/O related */
/*
 * Opens a file for reading, writing, or both. Also used to create a file.
 *
 * The function has the following parameters:
 * 
 * name             The pathname of the file to be opened.
 * osflags          File status flags. PR_Open performs a bitwise OR of the following bit flags:
 *
 *  PR_RDONLY       Open for reading only.
 *  PR_WRONLY       Open for writing only.
 *  PR_RDWR         Open for reading and writing.
 *  PR_CREATE_FILE  If the file does not exist, the file is created. If the file exists, this flag has no effect.
 *  PR_APPEND       The file pointer is set to the end of the file prior to each write.
 *  PR_TRUNCATE     If the file exists, its length is truncated to 0.
 *  PR_SYNC         If set, each write will wait for both the file data and file status to be physically updated.
 *  PR_EXCL         Used with PR_CREATE_FILE; if the file does not exist, the file is created. If the file already
 *                  exists, no action and NULL is returned
 *
 *                  In most cases, only one of the first three flags may be used. If the flags parameter does include any
 *                  of the first three flags (PR_RDONLY, PR_WRONLY, or PR_RDWR), the open file can't be read or written,
 *                  which is not useful.
 *
 * mode             Access permission bits of the file mode, if the file is created when PR_CREATE_FILE is on.
 * 
 *                  The mode parameter is currently applicable only on Unix platforms. It may apply to other platforms 
 *                  in the future. Possible values of the mode parameter include the following:
 *
 * 00400            Read by owner.
 * 00200            Write by owner.
 * 00100            Execute (search if a directory) by owner.
 * 00040            Read by group.
 * 00020            Write by group.
 * 00010            Execute by group.
 * 00004            Read by others.
 * 00002            Write by others.
 * 00001            Execute by others. 
 */
PRInt32 _Open(const char *name, PRIntn osflags, PRIntn mode) {
	// owner mode is ignored
	BPTR lock,file = -1;

	// dependent if write access is wanted get exclusive lock
	if( NULL != ( lock = ( osflags & PR_WRONLY | osflags & PR_RDWR ) ? Lock( name,EXCLUSIVE_LOCK ) : Lock( name,SHARED_LOCK ) ) ) {
		// open file
		if( NULL != ( file = OpenFromLock( lock ) ) ) {
			// lock is now unusable, don't unlock or so, thus lock is set to zero
			lock = NULL;

			if( osflags & PR_TRUNCATE )
				if( -1 == SetFileSize( file,0,OFFSET_BEGINNING ) ) {
					// TODO: set error?
					file = -1;
				}

			if( osflags & PR_APPEND )
				Seek( file,OFFSET_END,0 );
		}
		else {
			UnLock( lock );
			// TODO: set error?
			file = -1;
		}
	}
	else {
		// file does not exists, check if it should be created
		if( osflags & PR_CREATE_FILE ) {
			if( NULL != ( file = ( osflags & PR_RDONLY | osflags & PR_RDWR ) ? Open( name,MODE_READWRITE ) : Open( name,MODE_NEWFILE ) ) ) {

				// if PR_EXCL is set free resource after craetion and return NULL
				if( osflags & PR_EXCL ) {
					// we may should check for returned error code?
					Close( file );
					file = -1;
				}
			}
			else { 
				// TODO: set error?
				file = -1;
			}
		}
		else { 
			// TODO: set error?
			file = -1;
		}
	}

	return file;
}

/*
 * Deletes a file.
 *
 * The function has the following parameter:
 *
 * name             The pathname of the file to be deleted.
*/
PRStatus _Delete(const char *name) {
	if( DOSFALSE == DeleteFile( name ) )
		return PR_FAILURE;
	else
		return PR_SUCCESS;
}

/*
 * Gets information about a file with a specified pathname. File size is expressed as a 32-bit integer.
 *
 * The function has the following parameters:
 *
 * fn               The pathname of the file to get information about.
 * info             A pointer to a file information object (see PRFileInfo). On output,
 *                  PR_GetFileInfo writes information about the given file to the file information object. 
 */
PRStatus _GetFileInfo(const char *fn,PRFileInfo *finfo) {
	struct FileInfoBlock *info;
	BPTR lock;

	PRStatus status = PR_SUCCESS;

	if( NULL != ( lock = Lock( fn,SHARED_LOCK ) ) && NULL != ( info = (struct FileInfoBlock*)AllocMem( sizeof( struct FileInfoBlock),MEMF_ANY ) ) ) {
		if( DOSFALSE != Examine( lock,info ) ) {
			finfo->type         = (info->fib_DirEntryType < 0) ? PR_FILE_FILE : PR_FILE_DIRECTORY;
			finfo->size         = info->fib_Size;
			//TODO: finfo->creationTime = (PRInt64)0; // TODO: Convert amiga time to nspr time 
			finfo->modifyTime   = finfo->creationTime;
		}
	}
	else {
		// seterror

		status = PR_FAILURE;
	}

	if( lock != NULL )
		UnLock( lock );
	if( info != NULL )
		FreeMem( info,sizeof( struct FileInfoBlock) );

	return status;
}

/*
 * Gets information about a file with a specified pathname. File size is expressed as a 64-bit integer.
 *
 * fn               The pathname of the file to get information about.
 * info             A pointer to a file information object (see PRFileInfo). On output,
 *                  PR_GetFileInfo writes information about the given file to the file information object. 
 */
PRStatus _GetFileInfo64(const char *fn,PRFileInfo64 *info) {
}

/*
 * Renames a file.
 */
PRStatus _Rename(const char *from, const char *to) {
	if( DOSFALSE != Rename( from,to ) )
		return PR_SUCCESS;

	return PR_FAILURE;
}

/*
 * Determines the accessibility of a file.
 */
PRStatus _Access(const char *name, PRAccessHow how) {
}

/*
 * Closes a file descriptor.
 */
PRStatus _Close(PRInt32 osfd) {
	// TODO: check for error from Close
	if( osfd != NULL )
		Close( (BPTR)osfd );

	return PR_SUCCESS;
}

/*
 * Reads bytes from a file or socket.
 */
PRInt32 _Read(PRFileDesc *fd, void *buf, PRInt32 amount) {
    PRInt32 rv;
    BPTR osfd = fd->secret->md.osfd;

    if( -1 == ( rv = Read( osfd, buf, amount ) ) ) {
	    // TODO: set error?
    }

    return rv;
}

/*
 * Writes a buffer of data to a file or socket.
 */
PRInt32 _Write(PRFileDesc *fd, const void *buf, PRInt32 amount) {
    PRInt32 rv;
    BPTR osfd = fd->secret->md.osfd;

    if( amount == ( rv = Write( osfd, buf, amount ) ) ) {
	    // TODO: set error?
    }

    return rv;
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
PRInt32 _Seek (PRFileDesc *fd, PRInt32 offset, PRSeekWhence whence) {
    BPTR osfd = fd->secret->md.osfd;

    switch( whence ) {
    case PR_SEEK_CUR:
	    return Seek( osfd,offset, OFFSET_CURRENT );
	    break;
    case PR_SEEK_END:
	    return Seek( osfd,offset, OFFSET_END );
	    break;
    case PR_SEEK_SET:
    default:
	    return Seek( osfd,offset, OFFSET_BEGINNING );
	    break;
    }
}

/*
 * Moves the current read-write file pointer by an offset expressed as a 64-bit integer.
 */
PRInt64 _Seek64 (PRFileDesc *fd, PRInt64 offset, PRSeekWhence whence) {
}

/*
 * Synchronizes any buffered data for a file descriptor to its backing device (disk).
 */
PRStatus _Sync(PRFileDesc *fd) {
}




