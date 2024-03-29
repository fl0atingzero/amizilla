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
 * Copyright (C) 2003 Netscape Communications Corporation.  All
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

#include "nspr.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    PRAddrInfo *ai;
    void *iter;
    PRNetAddr addr;

    ai = PR_GetAddrInfoByName(argv[1], PR_AF_UNSPEC, PR_AI_ADDRCONFIG);
    if (ai == NULL) {
        fprintf(stderr, "PR_GetAddrInfoByName failed: (%d, %d)\n",
            PR_GetError(), PR_GetOSError());
        exit(1);
    }
    printf("%s\n", PR_GetCanonNameFromAddrInfo(ai));
    iter = NULL;
    while ((iter = PR_EnumerateAddrInfo(iter, ai, 0, &addr)) != NULL) {
        char buf[128];
        PR_NetAddrToString(&addr, buf, sizeof buf);
        printf("%s\n", buf);
    }
    PR_FreeAddrInfo(ai);
    return 0;
}
