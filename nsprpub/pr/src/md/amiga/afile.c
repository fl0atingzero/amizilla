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
#include <sys/syslimits.h>
#include <errno.h>

#include "primpl.h"

PRInt32 _PR_MD_PIPEAVAILABLE(PRFileDesc *fd) {
    if (WaitForChar(fd->secret->md.osfd, 0) == TRUE)
        return 1;
    return 0;
}

/**
 * Map DOS's IoErr() into an NSPR error
 */
void _MD_MapIOErr(LONG err) {
    PRInt32 nsprErr;

    switch (err) {
    case ERROR_NO_FREE_STORE:        
    case ERROR_TASK_TABLE_FULL:
        nsprErr = PR_OUT_OF_MEMORY_ERROR;
        break;

    case ERROR_BAD_TEMPLATE:
    case ERROR_BAD_NUMBER:
    case ERROR_REQUIRED_ARG_MISSING:
    case ERROR_KEY_NEEDS_ARG:
    case ERROR_TOO_MANY_ARGS:
    case ERROR_UNMATCHED_QUOTES:
        nsprErr = PR_INVALID_ARGUMENT_ERROR;
        break;

    case ERROR_LINE_TOO_LONG:
        nsprErr = PR_NAME_TOO_LONG_ERROR;
        break;

    case ERROR_FILE_NOT_OBJECT:
        nsprErr = PR_FILE_NOT_FOUND_ERROR;
        break;

    case ERROR_INVALID_RESIDENT_LIBRARY:
        nsprErr = PR_LOAD_LIBRARY_ERROR;
        break;

    case ERROR_NO_DEFAULT_DIR:
    case ERROR_OBJECT_IN_USE:
    case ERROR_OBJECT_EXISTS:
    case ERROR_DIR_NOT_FOUND:
    case ERROR_OBJECT_NOT_FOUND:
        nsprErr = PR_FILE_NOT_FOUND_ERROR;
        break;

    case ERROR_BAD_STREAM_NAME:
    case ERROR_OBJECT_TOO_LARGE:
    case ERROR_ACTION_NOT_KNOWN:
    case ERROR_INVALID_COMPONENT_NAME:
    case ERROR_INVALID_LOCK:
    case ERROR_OBJECT_WRONG_TYPE:
    case ERROR_COMMENT_TOO_BIG:
        nsprErr = PR_NAME_TOO_LONG_ERROR;
        break;

    case ERROR_DISK_FULL:
    case ERROR_DELETE_PROTECTED:
    case ERROR_WRITE_PROTECTED:
    case ERROR_READ_PROTECTED:
    case ERROR_NOT_A_DOS_DISK:
    case ERROR_NO_DISK:
        nsprErr = PR_ILLEGAL_ACCESS_ERROR;
        break;

    case ERROR_NOT_IMPLEMENTED:
        nsprErr = PR_NOT_IMPLEMENTED_ERROR;
        break;

    case ERROR_DIRECTORY_NOT_EMPTY:
        nsprErr = PR_DIRECTORY_NOT_EMPTY_ERROR;
        break;

    case ERROR_NO_MORE_ENTRIES:
    case ERROR_IS_SOFT_LINK:
    case ERROR_OBJECT_LINKED:
    case ERROR_BAD_HUNK:
    case ERROR_RECORD_NOT_LOCKED:
    case ERROR_LOCK_COLLISION:
    case ERROR_LOCK_TIMEOUT:
    case ERROR_DISK_NOT_VALIDATED:
    case ERROR_DISK_WRITE_PROTECTED:
    case ERROR_RENAME_ACROSS_DEVICES:
    case ERROR_TOO_MANY_LEVELS:
    case ERROR_DEVICE_NOT_MOUNTED:
    case ERROR_SEEK_ERROR:
        nsprErr = PR_IO_ERROR;
        break;
    default:
        nsprErr = PR_UNKNOWN_ERROR;
    }
    PR_SetError(nsprErr, err);
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
	/* owner mode is ignored */
	BPTR lock = (BPTR)NULL, file = (BPTR)NULL;
    LONG lockflags = (osflags & PR_WRONLY || osflags & PR_RDWR) ? 
        EXCLUSIVE_LOCK : SHARED_LOCK;
    LONG openflags = (osflags & PR_WRONLY || osflags & PR_RDWR) ?
        MODE_READWRITE : MODE_NEWFILE;

    if (strlen(name) > PATH_MAX) {
        PR_SetError(PR_NAME_TOO_LONG_ERROR, 0);
        return -1;
    }

	/* dependent if write access is wanted get exclusive lock */
    lock = Lock(name, lockflags);
    
    if (lock != (BPTR)NULL) {
        if (osflags & PR_EXCL) {
            PR_SetError(PR_FILE_EXISTS_ERROR, 0);
            goto error;
        } 

        file = OpenFromLock(lock);
        if (file != (BPTR)NULL) {
			/* lock is now unusable, don't unlock or so, 
             * thus lock is set to zero
             */
			lock = (BPTR)NULL;

			if(osflags & PR_TRUNCATE) {
				if(SetFileSize(file, 0, OFFSET_BEGINNING) == -1) {
                    _MD_MapIOErr(IoErr());
                    goto error;
				}
            }

            if(osflags & PR_APPEND)
                Seek(file, OFFSET_END, 0);
		} else {
            _MD_MapIOErr(IoErr());
            goto error;
		}
	} else {
		/* file does not exists, check if it should be created */
        if(!(osflags & PR_CREATE_FILE)) {
            PR_SetError(PR_FILE_NOT_FOUND_ERROR, 0);
            goto error;
        }

        file = Open(name, openflags);
        if(file == (BPTR)NULL) {
            _MD_MapIOErr(IoErr());
            goto error;
        }
    }

	return file;

error:
    if (lock != (BPTR)NULL)
        UnLock(lock);

    if (file != (BPTR)NULL)
        Close(file);
    return -1;
}

/*
 * Deletes a file.
 *
 * The function has the following parameter:
 *
 * name             The pathname of the file to be deleted.
*/
PRStatus _Delete(const char *name) {
    if (strlen(name) > PATH_MAX) {
        PR_SetError(PR_NAME_TOO_LONG_ERROR, 0);
        return PR_FAILURE;
    }

	if( DOSFALSE == DeleteFile( name ) ) {
        _MD_MapIOErr(IoErr());
		return PR_FAILURE;
    } else
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
	BPTR lock = (BPTR)NULL;
   
	PRStatus status = PR_FAILURE;

    if (info == NULL) {
        PR_SetError(PR_OUT_OF_MEMORY_ERROR, 0);
        goto error;
    }

    if (strlen(fn) > PATH_MAX) {
        PR_SetError(PR_NAME_TOO_LONG_ERROR, 0);
        goto error;
    }

	if((lock = Lock(fn, SHARED_LOCK)) != (BPTR)NULL) {
		if(Examine(lock, info) != DOSFALSE) {
			finfo->type = (info->fib_DirEntryType < 0) 
                ? PR_FILE_FILE : PR_FILE_DIRECTORY;
			finfo->size = info->fib_Size;
            finfo->creationTime = ((info->fib_Date.ds_Days + 2922)* 1440 + 
                info->fib_Date.ds_Minute) * 60 + 
                info->fib_Date.ds_Tick / TICKS_PER_SECOND;
            finfo->modifyTime = finfo->creationTime;
            status = PR_SUCCESS;
		}
	} else {
        _MD_MapIOErr(IoErr());
	}

error:
	if(lock != (BPTR)NULL)
		UnLock(lock);
	if(info != (BPTR)NULL)
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
    if (strlen(from) > PATH_MAX || strlen(to) > PATH_MAX) {
        PR_SetError(PR_NAME_TOO_LONG_ERROR, 0);
        return PR_FAILURE;
    }


	if( DOSFALSE != Rename( from,to ) )
		return PR_SUCCESS;

    _MD_MapIOErr(IoErr());
	return PR_FAILURE;
}

/*
 * Determines the accessibility of a file.
 */
PRStatus _Access(const char *name, PRAccessHow how) {
	struct FileInfoBlock *info;
	BPTR lock;   
	PRStatus status = PR_FAILURE;

    if (strlen(name) > PATH_MAX) {
        PR_SetError(PR_NAME_TOO_LONG_ERROR, 0);
        return PR_FAILURE;
    }

    info = PR_NEWZAP(struct FileInfoBlock);
    if (info == NULL) {
        PR_SetError(PR_OUT_OF_MEMORY_ERROR, 0);
        goto end;
    }

	lock = Lock(name, SHARED_LOCK);
    if (lock == (BPTR)NULL) {
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
    } else {
        _MD_MapIOErr(IoErr());
    }
end:
    if (lock != (BPTR)NULL) {
        UnLock(lock);
    }

    if (info != (BPTR)NULL) {
        PR_Free(info);
    }
    return status;
}

/*
 * Closes a file descriptor.
 */
PRStatus _Close(PRInt32 osfd) {
	/* TODO: check for error from Close */
	if(osfd != (PRInt32)NULL)
		Close((BPTR)osfd);

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
        _MD_MapIOErr(IoErr());
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
        _MD_MapIOErr(IoErr());
    }

    return rv;
}

/*
 * Gets an open file's information. File size is expressed as a 32-bit integer.
 */
PRStatus _GetOpenFileInfo(const PRFileDesc *fd, PRFileInfo *finfo) {
	struct FileInfoBlock *info = PR_NEWZAP(struct FileInfoBlock);
    PRStatus retval = PR_FAILURE;
    if (info) {
        if(ExamineFH(fd->secret->md.osfd, info) != DOSFALSE) {
            finfo->type = (info->fib_DirEntryType < 0) 
                ? PR_FILE_FILE : PR_FILE_DIRECTORY;
            finfo->size = info->fib_Size;
            finfo->creationTime = ((info->fib_Date.ds_Days + 2922)* 1440 + 
                info->fib_Date.ds_Minute) * 60 + 
                info->fib_Date.ds_Tick / TICKS_PER_SECOND;
            finfo->modifyTime = finfo->creationTime;
            retval = PR_SUCCESS;
        } else {
            _MD_MapIOErr(IoErr());
        }
    } 
    
    if (info != NULL) {
        PR_Free(info);
    }
    return retval;
}

/*
 * Gets an open file's information. File size is expressed as a 64-bit integer.
 */
PRStatus _GetOpenFileInfo64(const PRFileDesc *fd, PRFileInfo64 *info) {
    PRFileInfo tmp;
    if (_GetOpenFileInfo(fd, &tmp) == PR_SUCCESS) {
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
 * Moves the current read-write file pointer by an offset expressed as a 32-bit integer.
 */
PRInt32 _Seek (PRFileDesc *fd, PRInt32 offset, PRSeekWhence whence) {
    BPTR osfd = fd->secret->md.osfd;
    LONG retval = -1;
    LONG mode = 0;

    switch( whence ) {
    case PR_SEEK_CUR:
        mode = OFFSET_CURRENT;
	    break;
    case PR_SEEK_END:
        mode = OFFSET_END;
	    break;
    case PR_SEEK_SET:
    default:
        mode = OFFSET_BEGINNING;
	    break;
    }

    retval = Seek(osfd, offset, mode);
    if (retval != -1) {
        retval = Seek (osfd, 0, OFFSET_CURRENT);
    } else {
        LONG t = Seek(osfd, 0, OFFSET_CURRENT);
        PRFileInfo fi;        
        if (_GetOpenFileInfo(fd, &fi) == PR_SUCCESS) {
            if (fi.size < t + offset) {
                /* File is too small, extend the file */
                LONG size = SetFileSize(osfd, t + offset, OFFSET_BEGINNING);
                return _Seek(fd, offset, whence);
            }
        }
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
    return PR_SUCCESS;
}

PRInt32 _MD_WRITEV(
    PRFileDesc *fd, const struct PRIOVec *tiov,
    PRInt32 iov_size, PRIntervalTime timeout) {
    PRInt32 written = 0;
    PRStatus res;
    PRIOVec *iov = tiov;
    
    while (iov_size--) {
        res = PR_Send(fd, iov->iov_base, iov->iov_len, 0, timeout);
        if (res == -1)
            break;
        written += res;
        if (res < iov->iov_len) 
            break;
        iov++;
    }
    return written;
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
    return stat(name, buf);
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
    if (imported && fd->methods->file_type != PR_DESC_SOCKET_TCP && 
        fd->methods->file_type != PR_DESC_SOCKET_UDP) {
        fd->secret->inheritable = _PR_TRI_UNKNOWN;
    } else {
        fd->secret->inheritable = _PR_TRI_TRUE;
    }
}

/*
 * If fd->secret->inheritable is _PR_TRI_UNKNOWN and we need to
 * know the inheritable attribute of the fd, call this function
 * to find that out.  This typically requires a system call.
 */
void _MD_QUERY_FD_INHERITABLE(PRFileDesc *fd) {
    /* It is already known with the needToClose flag */
}

int _MD_ERRNO(void) {
    return errno;
}

PRStatus _PR_MD_CREATE_FILE_MAP(PRFileMap *fmap, PRInt64 size) {
    fmap->md.isAnonFM = PR_FALSE;
    if (PR_Seek(fmap->fd, size + sizeof(long), PR_SEEK_SET) == -1)
        return PR_FAILURE;
    if (PR_Seek(fmap->fd, 0, PR_SEEK_SET) == -1)
        return PR_FAILURE;
    return PR_SUCCESS;
}

PRInt32 _PR_MD_GET_MEM_MAP_ALIGNMENT(void) {
    return 4;
}

void *_PR_MD_MEM_MAP(PRFileMap *fmap, PROffset64 offset, PRUint32 len) {
    struct _MDMemMap *memory = NULL;
    char *addr;
    long mem = 0;

    if (PR_Seek(fmap->fd, 0, PR_SEEK_SET) == -1)
        goto error;

    if (PR_Read(fmap->fd, &mem, sizeof(mem)) != sizeof(mem))
        goto error;

    mem = ntohl(mem);
    if (mem == 0) {
        long t;
        memory = (struct _MDMemMap *)PR_Malloc(len + sizeof(struct _MDMemMap));
        if (memory == NULL) {
            goto error;
        }
        PR_Seek(fmap->fd, 0, PR_SEEK_SET);
        t = htonl((unsigned long)memory);
        PR_Write(fmap->fd, &t, sizeof(t));
        memory->offset = offset;
        memory->len = len;
        memory->map = fmap;        
    } else {
        memory = (struct _MDMemMap *)mem;
    }
    addr = (char *)memory + sizeof(struct _MDMemMap);
    PR_AtomicIncrement(&memory->count);

    if (PR_Seek64(fmap->fd, offset + sizeof(long), PR_SEEK_SET) == -1)
        goto error;

    if (PR_Read(fmap->fd, addr, len) == -1)
        goto error;

    return addr;

error:
    if (memory != NULL && mem == 0)
        PR_Free(memory);
    return NULL;
}

PRStatus _PR_MD_MEM_UNMAP(void *addr, PRUint32 len) {
    struct _MDMemMap *memory = (struct _MDMemMap *)((char *)addr - sizeof(struct _MDMemMap));
    if (PR_AtomicDecrement(&memory->count) == 0) {
        if (memory->map->prot == PR_PROT_READWRITE) {
            PR_Seek64(memory->map->fd, memory->offset + sizeof(long), PR_SEEK_SET);
            PR_Write(memory->map->fd, addr, memory->len);
        }
        PR_Free(memory);
    }
    return PR_SUCCESS;
}

PRStatus  _PR_MD_CLOSE_FILE_MAP(PRFileMap *fmap) {
    if (fmap->md.isAnonFM == PR_TRUE) {
        return PR_Close(fmap->fd);
    }
    PR_Free(fmap);
    return PR_SUCCESS;
}


PRStatus _md_ExportFileMapAsString(PRFileMap *fm, PRSize bufSize, char *buf) {
    PRIntn  written;
    written = PR_snprintf( buf, bufSize, "%ld:%d", fm->fd->secret->md.osfd, fm->prot);

    return((written == -1)? PR_FAILURE : PR_SUCCESS);
}

PRFileMap * _md_ImportFileMapFromString(const char *fmstring) {
    PRStatus    rc;
    PRInt32     osfd;
    PRIntn      prot; /* really: a PRFileMapProtect */
    PRFileDesc  *fd;
    PRFileMap   *fm = NULL; /* default return value */
    PRFileInfo64 info;

    PR_sscanf( fmstring, "%ld:%d", &osfd, &prot );

    fflush(stdout);
    /* import the os file descriptor */
    fd = PR_ImportFile( osfd );
    if ( NULL == fd ) {
        goto Finished;
    }

    rc = PR_GetOpenFileInfo64( fd, &info );
    if ( PR_FAILURE == rc )  {
        goto Finished;
    }

    fm = PR_CreateFileMap( fd, info.size, (PRFileMapProtect)prot );

Finished:
    return(fm);
}

PRFileMap * _md_OpenAnonFileMap(const char *dirName, PRSize size, PRFileMapProtect prot) {
    char tempname[PATH_MAX]={0,};
    PRFileMap *retval = NULL;
    PRFileDesc *desc = NULL;
    snprintf(tempname, sizeof(tempname) - 1, "%s/tempfile.XXXXXX", dirName);
    mktemp(tempname);
   
    desc = PR_Open(tempname, PR_RDWR |  PR_CREATE_FILE | PR_EXCL, 0);
    if (desc == NULL) {
        goto error;
    }

    retval = PR_CreateFileMap(desc, size, prot);
    if (retval == NULL)
        goto error;

    retval->md.isAnonFM = PR_TRUE;

    return retval;
error:
    if (desc != NULL)
        PR_Close(desc);

    if (retval != NULL)
        PR_CloseFileMap(retval);

    return NULL;
}
