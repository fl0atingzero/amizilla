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
#include <primpl.h>
#include <devices/inputevent.h>
#include <devices/input.h>


/* Input handler which does gathers the data and signals the 
 * InputEventThread
 * Input - a0 - InputEvent structure
 * Input - a1 - InputData which contains a buffer to put the data and 
 * the process to signal when there is data
 * Output - d0 the new InputEvent structure (it is always the same as the input)
 * NOTE: This function CANNOT access A4-relative data since restore_a4
 * isn't called (it clobbers a0)
 */
struct InputEvent *InputEventHandler(struct InputEvent *ie __asm("a0"), struct InputData *ip __asm("a1")) {
	struct InputEvent *ie2 = ie;
	struct ExecBase *SysBase = NULL;
    register struct InputEvent *retval __asm("d0");
    int pos = 0;
	if (SysBase == NULL) {
		SysBase = *(struct ExecBase **)4L;
	}
    while (ie && pos < 5) {
		switch (ie->ie_Class) {
		case IECLASS_RAWKEY:
			ip->data[pos] = ie->ie_Code | (int)ie->ie_position.ie_addr;
		default:				
			ip->data[pos] = (int)ie->ie_position.ie_addr;
		}
        ie = ie->ie_NextEvent;
		if (ip->data[pos])
			pos++;
    }

	if (pos) {
		ip->num = pos;
		Signal((struct Task *)ip->p, SIGBREAKF_CTRL_F);
	}
	retval = ie2;
	return retval;
}

/*
 * Doesn't belong here but doesn't need restore-a4
 */
void SETVARSINST(struct Library *lib __asm("a0"), int argc, void (*func)(int)) {
  asm("jsr a0@(-36:W);");
}
