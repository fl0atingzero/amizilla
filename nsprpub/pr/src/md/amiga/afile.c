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

/* 
 * both devices/timer.h and sys/time.h (included from primpl.h) define 
 * struct timeval. sys/time.h detects the other definiton while 
 * devices/timer.h does not, hence we must include device/timer.h first.
 */
#include <devices/timer.h>
#include <sys/ioctl.h>
#include <errno.h>

#include "primpl.h"

PRInt32 _PR_MD_PIPEAVAILABLE(PRFileDesc *fd) {
    PRInt32 result;

    if (ioctl(fd->secret->md.osfd, FIONREAD, &result) < 0) {
        _PR_MD_MAP_SOCKETAVAILABLE_ERROR(errno);
        return -1;
    }
    return result;
}

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
	struct FileInfoBlock *info = PR_NEWZAP(struct FileInfoBlock);
	BPTR lock;
   
	PRStatus status = PR_SUCCESS;

    if (info == NULL) {
        PR_SetError(PR_OUT_OF_MEMORY_ERROR, 0);
        return PR_FAILURE;
    }

	if((lock = Lock(fn, SHARED_LOCK)) != NULL) {
		if(Examine(lock, info) != DOSFALSE) {
			finfo->type = (info->fib_DirEntryType < 0) 
                ? PR_FILE_FILE : PR_FILE_DIRECTORY;
			finfo->size = info->fib_Size;
            finfo->creationTime = ((info->fib_Date.ds_Days + 2922)* 1440 + 
                info->fib_Date.ds_Minute) * 60 + 
                info->fib_Date.ds_Tick / TICKS_PER_SECOND;
            finfo->modifyTime = finfo->creationTime;                
		}
	} else {
		status = PR_FAILURE;
	}

	if( lock != NULL )
		UnLock( lock );
	if( info != NULL )
       PR_Free(info);

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
    PRFileInfo tmp;
    if (_GetFileInfo(fn, &tmp) == PR_SUCCESS) {
        info->type = tmp.type;
        info->creationTime = tmp.creationTime;
        info->modifyTime = tmp.modifyTime;
        LL_I2L(tmp.size, info->size);
        return PR_SUCCESS;
    } else {
        return PR_FAILURE;
    }
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
	struct FileInfoBlock *info = PR_NEWZAP(struct FileInfoBlock);
	BPTR lock;   
	PRStatus status = PR_FAILURE;

    if (info == NULL) {
        PR_SetError(PR_OUT_OF_MEMORY_ERROR, 0);
        goto end;
    }

	lock = Lock(name, SHARED_LOCK);
    if (lock == NULL) {
        PR_SetError(PR_FILE_NOT_FOUND_ERROR, 0);
        goto end;
    }

    if(Examine(lock, info) != DOSFALSE) {
        LONG protection = info->fib_Protection;
        /* TODO: MuFS access checking */
        switch (how) {
        case PR_ACCESS_EXISTS:
            status = PR_SUCCESS;
            break;
        case PR_ACCESS_READ_OK:
            if (((protection & FIBF_READ) == 0) || (protection & (FIBF_OTR_READ | FIBF_GRP_READ))) {
                status = PR_SUCCESS;
            }
            break;
        case PR_ACCESS_WRITE_OK:
            if (((protection & FIBF_WRITE) == 0) || (protection & (FIBF_OTR_WRITE | FIBF_GRP_WRITE))) {
                status = PR_SUCCESS;
            }
            break;
        }       
    }
end:
    if (lock != NULL) {
        UnLock(lock);
    }

    if (info != NULL) {
        PR_Free(info);
    }
    return status;
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
    PRThread *me = PR_CurrentThread();

    if (_PR_PENDING_INTERRUPT(me)) {
        PR_ClearInterrupt();
		PR_SetError(PR_PENDING_INTERRUPT_ERROR, 0);
		return -1;
	}

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

    if( amount != ( rv = Write( osfd, buf, amount ) ) ) {
      fprintf(stderr, "Didn't write amount(%d) bytes, wrote %d\n", amount, rv);
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
    LONG retval = -1;
    switch( whence ) {
    case PR_SEEK_CUR:
	    retval = Seek(osfd, offset, OFFSET_CURRENT );
	    break;
    case PR_SEEK_END:
	    retval = Seek(osfd, offset, OFFSET_END );
	    break;
    case PR_SEEK_SET:
    default:
	    retval = Seek(osfd, offset, OFFSET_BEGINNING );
	    break;
    }

    if (retval != -1) {
        retval = Seek (osfd, 0, OFFSET_CURRENT);
    }

    return retval;
}

/*
 * Moves the current read-write file pointer by an offset expressed as a 64-bit integer.
 */
PRInt64 _Seek64 (PRFileDesc *fd, PRInt64 offset, PRSeekWhence whence) {
    PRInt32 off;
    PRInt64 retval;
    static PRInt64 bigone = LL_INIT(1,0);
    if (LL_CMP(offset, >, bigone)) {
        return PR_FILE_TOO_BIG_ERROR;
    }

    LL_L2I(off, offset);
    off = _Seek(fd, off, whence);
    LL_I2L(off, retval);
    return retval;
}

/*
 * Synchronizes any buffered data for a file descriptor to its backing device (disk).
 */
PRStatus _Sync(PRFileDesc *fd) {
    /* No op */
}

PRInt32 _MD_WRITEV(
    PRFileDesc *fd, const struct PRIOVec *iov,
    PRInt32 iov_size, PRIntervalTime timeout) {
#warning _MD_WRITEV not implemented
    assert(0);
}

PRStatus _MD_LOCKFILE(PRInt32 osfd) {
#warning _MD_LOCKFILE not implemented
    assert(0);
}

extern PRStatus _MD_TLOCKFILE(PRInt32 osfd) {
#warning _MD_TLOCKFILE not implemented
    assert(0);
}

extern PRStatus _MD_UNLOCKFILE(PRInt32 osfd) {
#warning _MD_UNLOCKFILE not implemented
    assert(0);
}

PRInt32 _MD_STAT(const char *name, struct stat *buf) {
#warning _MD_STAT not implemented
    assert(0);
}

/*
 * Initialize fd->secret->inheritable for a newly created fd.
 * If 'imported' is false, the osfd (i.e., fd->secret->md.osfd)
 * was created by NSPR and hence has the OS-dependent default
 * inheritable attribute.  If 'imported' is true, the osfd was
 * not created by NSPR and hence a system call is required to
 * query its inheritable attribute.  Since we may never need to
 * know the inheritable attribute of a fd, a platform may choose
 * to initialize fd->secret->inheritable of an imported fd to
 * _PR_TRI_UNKNOWN and only pay the cost of the system call
 * (in _PR_MD_QUERY_FD_INHERITABLE) when necessary.
 */
void _MD_INIT_FD_INHERITABLE(PRFileDesc *fd, PRBool imported) {
#warning _MD_INIT_FD_INHERITABLE not implemented
 }

/*
 * If fd->secret->inheritable is _PR_TRI_UNKNOWN and we need to
 * know the inheritable attribute of the fd, call this function
 * to find that out.  This typically requires a system call.
 */
void _MD_QUERY_FD_INHERITABLE(PRFileDesc *fd) {
#warning _MD_QUERY_FD_INHERITABLE not implemented
    assert(0);
}

int _MD_ERRNO(void) {
    return errno;
}
