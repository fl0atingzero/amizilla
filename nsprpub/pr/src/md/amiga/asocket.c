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
 * Contributor(s): Tom Parker <tom@carrott.org>
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

#include "primpl.h"

void _MD_INIT_IO(void) {
#warning _MD_INIT_IO not implemented
    assert(0);
}

PRInt32 _MD_CLOSE_SOCKET(PRInt32 osfd) {
#warning _MD_CLOSE_SOCKET not implemented
    assert(0);
}

PRInt32 _MD_CONNECT(
    PRFileDesc *fd, const PRNetAddr *addr,
    PRUint32 addrlen, PRIntervalTime timeout) {
#warning _MD_CONNECT not implemented
    assert(0);
}

PRInt32 _MD_ACCEPT(
    PRFileDesc *fd, PRNetAddr *addr,
    PRUint32 *addrlen, PRIntervalTime timeout) {
#warning _MD_ACCEPT not implemented
    assert(0);
}

PRInt32 _MD_BIND(PRFileDesc *fd, const PRNetAddr *addr, PRUint32 addrlen) {
#warning _MD_BIND not implemented
    assert(0);
}

PRInt32 _MD_LISTEN(PRFileDesc *fd, PRIntn backlog) {
#warning _MD_LISTEN not implemented
    assert(0);
}

PRInt32 _MD_SHUTDOWN(PRFileDesc *fd, PRIntn how) {
#warning _MD_SHUTDOWN not implemented
    assert(0);
}

PRInt32 _MD_RECV(PRFileDesc *fd, void *buf, PRInt32 amount, 
                               PRIntn flags, PRIntervalTime timeout) {
#warning _MD_RECV not implemented
    assert(0);
}

PRInt32 _MD_SEND(
    PRFileDesc *fd, const void *buf, PRInt32 amount, PRIntn flags, 
    PRIntervalTime timeout) {
#warning _MD_SEND not implemented
    assert(0);
}

PRInt32 _MD_ACCEPT_READ(PRFileDesc *sd, PRInt32 *newSock, 
                                PRNetAddr **raddr, void *buf, PRInt32 amount,
                                PRIntervalTime timeout) {
#warning _MD_ACCEPT_READ not implemented
    assert(0);
}


PRInt32 _MD_SENDFILE(
    PRFileDesc *sock, PRSendFileData *sfd, 
    PRInt32 flags, PRIntervalTime timeout) {
#warning _MD_SENDFILE not implemented
    assert(0);
}

PRStatus _MD_GETSOCKNAME(
    PRFileDesc *fd, PRNetAddr *addr, PRUint32 *addrlen) {
#warning _MD_GETSOCKNAME not implemented
    assert(0);
}

PRStatus _MD_GETPEERNAME(
    PRFileDesc *fd, PRNetAddr *addr, PRUint32 *addrlen) {
#warning _MD_GETPEERNAME not implemented
    assert(0);
}

PRStatus _MD_GETSOCKOPT(
    PRFileDesc *fd, PRInt32 level, PRInt32 optname, char* optval, PRInt32* optlen) {
#warning _MD_GETSOCKOPT not implemented
    assert(0);
}

PRStatus _MD_SETSOCKOPT(
    PRFileDesc *fd, PRInt32 level, PRInt32 optname,
    const char* optval, PRInt32 optlen) {
#warning _MD_SETSOCKOPT not implemented
    assert(0);
}

PRInt32 _MD_RECVFROM(
    PRFileDesc *fd, void *buf, PRInt32 amount, PRIntn flags,
    PRNetAddr *addr, PRUint32 *addrlen, PRIntervalTime timeout) {
#warning _MD_RECVFROM not implemented
    assert(0);
}

PRInt32 _MD_SENDTO(
    PRFileDesc *fd, const void *buf, PRInt32 amount, PRIntn flags,
    const PRNetAddr *addr, PRUint32 addrlen, PRIntervalTime timeout) {
#warning _MD_SENDTO not implemented
    assert(0);
}

PRInt32 _MD_SOCKETPAIR(int af, int type, int flags, PRInt32 *osfd) {
#warning _MD_SOCKETPAIR not implemented
    assert(0);
}

PRInt32 _MD_SOCKET(int af, int type, int flags) {
#warning _MD_SOCKET not implemented
    assert(0);
}

PRInt32 _MD_SOCKETAVAILABLE(PRFileDesc *fd) {
#warning _MD_SOCKETAVAILABLE not implemented
    assert(0);
}

PRInt32 _PR_MD_PIPEAVAILABLE(PRFileDesc *fd) {
#warning _MD_PIPEAVAILABLE not implemented
    assert(0);
}

PRInt32 _MD_PR_POLL(PRPollDesc *pds, PRIntn npds, PRIntervalTime timeout) {
#warning _MD_PR_POLL not implemented
    assert(0);
}

void *_MD_GET_SP(PRThread *thread) {
#warning _MD_GET_SP not implemented
    assert(0);
}
