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

/*
 * Amiga specificy includes
 */
#include <dos/dos.h>
#include <exec/memory.h>
//#include <proto/dos.h>
#include <proto/exec.h>

/*
 * Opens the directory with the specified pathname.
 */
PRStatus _OpenDir(struct _MDDir *md,const char *name) {
	// Lock and check for directory
	if( NULL != ( md->lock = Lock( name,SHARED_LOCK ) ) && NULL != ( md->info = (struct FileInfoBlock*)AllocMem( sizeof( struct FileInfoBlock),MEMF_ANY ) ) ) {
		if( DOSFALSE != Examine( md->lock,md->info ) && md->info->fib_DirEntryType >=0 ) {
			return PR_SUCCESS;
		}
	}

	if( md->info != NULL )
		FreeMem( md->info,sizeof( struct FileInfoBlock) );

	if( md->lock != NULL )
		UnLock( md->lock );

	return PR_FAILURE;
}

/*
 * Gets a pointer to the next entry in the directory.
 */
char* _ReadDir(struct _MDDir *md, PRIntn flags) {
	if( DOSFALSE != ExNext( md->lock,md->info ) ) {
		return md->info->fib_FileName;
	}
}

/*
 * Closes the specified directory.
 */
PRStatus _CloseDir(struct _MDDir *md) {
	if( md->info != NULL )
		FreeMem( md->info,sizeof( struct FileInfoBlock) );

	if( md->lock != NULL )
		UnLock( md->lock );

	return PR_SUCCESS;
}

/*
 * Creates a directory with a specified name and access mode.
 */
PRStatus _MakeDir(const char *name,PRIntn mode) {
	BPTR lock;

	if( NULL != ( lock = CreateDir( name ) ) )
		UnLock( lock );
	else
		return PR_FAILURE;

	return PR_SUCCESS;
}

/*
 * Removes a directory with a specified name.
 */
PRStatus _RemoveDir(const char *name) {
	if( DOSFALSE != DeleteFile( name ) )
		return PR_SUCCESS;

	return PR_FAILURE;
}











