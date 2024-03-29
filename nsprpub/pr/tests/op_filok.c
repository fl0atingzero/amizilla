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

/***********************************************************************
**
** Name: op_filok.c
**
** Description: Test Program to verify the PR_Open finding an existing file.
**
** Modification History:
** 03-June-97 AGarcia- Initial version
***********************************************************************/

/***********************************************************************
** Includes
***********************************************************************/
/* Used to get the command line option */
#include "prinit.h"
#include "prmem.h"
#include "prio.h"
#include "prerror.h"
#include <stdio.h>

#ifdef XP_MAC
#include "prlog.h"
#define printf PR_LogPrint
#else
#endif

/*
 * The name of a file that is guaranteed to exist
 * on every machine of a particular OS.
 */
#ifdef VMS
#define EXISTING_FILENAME "SYS$LOGIN:LOGIN.COM"
#elif XP_UNIX
#define EXISTING_FILENAME "/bin/sh"
#elif defined(WIN32)
#define EXISTING_FILENAME "c:/autoexec.bat"
#elif defined(OS2)
#define EXISTING_FILENAME "c:/config.sys"
#elif defined(BEOS)
#define EXISTING_FILENAME "/boot/beos/bin/sh"
#elif defined(XP_AMIGAOS)
#define EXISTING_FILENAME "s:startup-sequence"
#else
#error "Unknown OS"
#endif

static PRFileDesc *t1;

int main(int argc, char **argv)
{

#ifdef XP_MAC
	SetupMacPrintfLog("pr_open_re.log");
#endif
	
    PR_STDIO_INIT();

	t1 = PR_Open(EXISTING_FILENAME, PR_RDONLY, 0666);

	if (t1 == NULL) {
		printf ("error code is %d \n", PR_GetError());
		printf ("File %s should be found\n",
				EXISTING_FILENAME);
		return 1;
	} else {
		if (PR_Close(t1) == PR_SUCCESS) {
			printf ("Test passed \n");
			return 0;
		} else {
			printf ("cannot close file\n");
			printf ("error code is %d\n", PR_GetError());
			return 1;
		}
	}
}			
