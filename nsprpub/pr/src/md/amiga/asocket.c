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
 * Contributor(s): Tom Parker <tom@carrott.org>
 *               : Jeff Shepherd <jshepher@jshepher.dyndns.org>
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
#include <assert.h>
#include <errno.h>
/* 
 * both devices/timer.h and sys/time.h (included from primpl.h) define 
 * struct timeval. sys/time.h detects the other definiton while 
 * devices/timer.h does not, hence we must include device/timer.h first.
 */
#include <devices/timer.h>
#include <sys/ioctl.h>
#include <amitcp/socketbasetags.h>
#include "primpl.h"

#define  AMITCP_BASE_NAME me->AmiTCP_Base
#include "amitcp.h"

#define BTOCPTR(ptr) ((void *)((ptr) << 2))

/*
 * Architecture:
 * As you may or may not know, sockets provided AmiTCP library only works on a 
 * per-process/per-thread basis -- ie, you just can't share the 
 * library reference and just pass the socket descriptor around. 
 *
 * There is a way to share sockets by using 
 * Dup2Socket/ReleaseSocket/ObtainSocket. What this implementation does is 
 * spawn a "Socket thread" which is the keeper of all the sockets. When a 
 * thread creates a socket either by calling socket() or accept(), the code
 * "passes" the socket to the Socket Thread by first calling Dup2Socket,
 * ReleaseSocket and notifies the Socket Thread. The Socket Thread then calls
 * ObtainSocket to get a copy of the socket. Socket file descriptors are 
 * actually stored as thread-local variables using the GetThreadPrivate,
 * NewThreadPrivateIndex functions. If a thread uses a socket created
 * by another thread, it asks the Socket Thread to obtain a copy of it
 * Socket cleanup per-thread is handled automatically by the destructor
 * of the thread-local variable code
 * Because we have a limited number of thread-local variables, slots are
 * reused when they are freed up. Since it is possible for one thread to
 * close a socket and another thread still try to use the closed socket
 * (and even the thread-local variable slot has been reused), each socket
 * has a sequence number attached to it. Every socket function validates
 * its private sequence number with that of the socket thread.
 *
 * For a large number of sockets in use, the code dynamically ups the socket
 * table size.
 */
#define MSG_RECEIVE  1
#define MSG_OBTAIN   2
#define MSG_CHECK    3
#define MSG_CLOSE    4
#define MSG_DONE     5

/* Structure of the thread-local variable socket */
struct SharedSocket {
    PRUint32 sequenceNumber;
    PRInt32 fd;
};

/* Message sent to the Socket Thread */
struct SocketMsg {
    PRInt16 type; /* One of MSG_RECEIVE, MSG_OBTAIN, MSG_CLOSE, MSG_CHECK, MSG_DONE */
    union {
        struct {
            int type;
            int domain;
            int protocol;
            PRUint32 id;
        } receive; /* Structure used for MSG_RECEIVE */

        struct {
            PRUint32 private_idx;
        } obtain; /* Structure used for MSG_OBTAIN */

        struct {
            PRUint32 private_idx;
            PRUint32 sequenceNumber;            
        } close; /* Structure used for MSG_CLOSE */

        struct {
            PRUint32 private_idx;
            PRUint32 sequenceNumber;
        } check; /* Structure used for MSG_CHECK */
    } msg; 
};

/* Reply from the socket thread */
struct ReplyMsg {
    PRInt32 errno; /* Any errors encountered */

    union {
        struct {
            PRUint32 private_idx;
            PRUint32 sequenceNumber;
        } receive; /* Structure used for MSG_RECEIVE */

        struct {
            PRInt32 id;
            PRUint32 sequenceNumber;
        } obtain; /* Structure used for MSG_OBTAIN */

        struct {
            PRStatus status;
        } check; /* Structure used for MSG_CHECK */
    } msg;        
};
    

static void SocketThread(void *);

/* Global messages/replies to the socket thread */
static struct SocketMsg msg;
static struct ReplyMsg reply;
/* If you want to talk to the socket thread, lock this lock first */
static PRLock *communicationLock;

/* locks and condition variables to talk to the socket thread */
static PRLock *msgLock;
static PRLock *replyLock;
static PRCondVar *msgCondVar;
static PRCondVar *replyCondVar;

/* The Socket Thread */
static PRThread *sockThread;

/* Destructor for the ThreadPrivate socket descriptor */
static void closeOpenSocketDTOR(void *prm) {
    PRThread *me = PR_GetCurrentThread();
    if (me->state != _PR_DEAD_STATE) {
        /* just a precaution */
        struct SharedSocket *ss = (struct SharedSocket *)prm;
        printf("%lx closing socket(DTOR) %d\n", me, ss->fd);
        TCP_CloseSocket(ss->fd);
        PR_Free(ss);
    }
}

/*
 * Initialize the locks and socket thread
 */
void _MD_INIT_IO(void) {
    communicationLock = PR_NewLock();
    msgCondVar = PR_NewCondVar(msgLock = PR_NewLock());
    replyCondVar = PR_NewCondVar(replyLock = PR_NewLock());
    PR_Lock(msgLock);
    sockThread = PR_CreateThread(PR_SYSTEM_THREAD, 
                                 SocketThread, NULL, PR_PRIORITY_NORMAL, 
                                 PR_LOCAL_THREAD, 
                                 PR_JOINABLE_THREAD, 0);
    sockThread->daemon = PR_TRUE;
    printf("msgLock is %lx, replyLock is %lx, communicationslock is %lx, msgCondVar is %lx, replyCOndVar is %lx\n", msgLock, replyLock, communicationLock, msgCondVar, replyCondVar);
    printf("Socket thread is %lx\n", sockThread);
    /* Wait until the socket thread wakes up */
    PR_WaitCondVar(msgCondVar, PR_INTERVAL_NO_TIMEOUT);
    PR_Unlock(msgLock);
}


/*
 * Clean up all the locks and the socket thread 
 */
void _PR_CleanupSocket(void) {
    PRIntervalTime waitTime = PR_MillisecondsToInterval(100);
    PR_Lock(communicationLock);
    PR_Lock(msgLock);
    PR_Lock(replyLock);
    msg.type = MSG_DONE;
    PR_NotifyCondVar(msgCondVar);
    PR_Unlock(msgLock);
    PR_WaitCondVar(replyCondVar, waitTime);
    PR_Unlock(replyLock);
    PR_Unlock(communicationLock);
    PR_JoinThread(sockThread);
    PR_DestroyCondVar(msgCondVar);
    PR_DestroyCondVar(replyCondVar);
    PR_DestroyLock(communicationLock);
    PR_DestroyLock(msgLock);
    PR_DestroyLock(replyLock);
}

/* Wait for a socket to become available for read/write
 * Returns > 0 if the socket is ready
 * Returns 0 if the socket has been timed out, interrupted
 * Returns -1 on error
 */
#define TYPE_READ 0
#define TYPE_WRITE 1
static int local_io_wait(int fd, int type, PRIntervalTime timeout) {
    fd_set fd_read;
    fd_set fd_write;
    fd_set fd_except;
    PRThread *me = PR_GetCurrentThread();
    LONG flags = (1L << me->port->mp_SigBit) | (1L << me->interruptSignal);
    struct timeval tv;
    int sel;

    if (timeout != PR_INTERVAL_NO_TIMEOUT) {
        tv.tv_sec = timeout / _PR_MD_INTERVAL_PER_SEC();
        tv.tv_micro = timeout % _PR_MD_INTERVAL_PER_SEC() * (1000000 / _PR_MD_INTERVAL_PER_SEC());
    }

    printf("Local_io_wait(%lx) fd %d, type %d, timeout %d, flags %lx\n", me, fd, type, timeout, me->flags);
    FD_ZERO(&fd_read);
    FD_ZERO(&fd_write);
    FD_ZERO(&fd_except);

    FD_SET(fd, &fd_except);
    if (type == TYPE_READ) {
        FD_SET(fd, &fd_read);
    } else {
        FD_SET(fd, &fd_write);
    }

    printf("WaitSelect(%lx) flags are %d\n", me, me->flags);
    me->state = _PR_IO_WAIT;
    sel = TCP_WaitSelect(fd + 1, &fd_read, &fd_write, &fd_except,
        (timeout == PR_INTERVAL_NO_TIMEOUT) ? NULL : &tv, &flags);

    /* See if someone is trying to kill me by setting my state to dead */
    if (me->state == _PR_DEAD_STATE) {
        printf("Thread %x was forceably killed from WaitSelect\n", me);
        longjmp(me->jmpbuf, 1);
    }

    me->state = _PR_RUNNING;
    printf("WaitSelect(%lx) returned %d, flags is %lx\n", me, sel, me->flags);
    if (sel < 0) {
        _PR_MD_MAP_SELECT_ERROR(TCP_Errno());
    } else {
        if (flags & (1 << me->interruptSignal)) {
            printf("WaitSelect(%lx) Interrupted, flags are %lx\n", me, me->flags);
            PR_SetError(PR_PENDING_INTERRUPT_ERROR, 0);
        } else if (sel == 0) {
            PR_SetError(PR_IO_TIMEOUT_ERROR, 0);
        }
    }
    return sel;
}

/**
 * Adds 64 new available sockets sockets 
 */
static void increaseSocketTable(void) {
    PRThread *me = PR_GetCurrentThread();
    int num = TCP_GetDTableSize();
    struct TagItem tags[] = {
        { SBTM_SETVAL(SBTC_DTABLESIZE), num + 64 },
        { TAG_DONE, NULL }
    };

    TCP_SocketBaseTagList(tags);
}

/**
 * Sends a newly created socket to the socket thread 
 */
static PRStatus sendSocketToThread(int fd, _MDSocket *sock) {
    PRThread *me = PR_GetCurrentThread();
    PRStatus retval = PR_SUCCESS;
    PRBool isInterruptsBlocked;

    int fd2 = -1;
    struct SharedSocket *ss = PR_NEWZAP(struct SharedSocket);

    if (ss == NULL) {
        PR_SetError(PR_OUT_OF_MEMORY_ERROR, 0);
        goto error;
    }

    ss->fd = fd;
    fd2 = TCP_Dup2Socket(fd, -1);    
    if (fd2 < 0) {
        if (TCP_Errno() == EMFILE) {
            increaseSocketTable();
            fd2 = TCP_Dup2Socket(fd, -1);
        }
    }

    if (fd2 < 0) {            
        printf("Dup2Socket returned %d, errno is %d\n", fd2, TCP_Errno());
        goto error;
    }
    isInterruptsBlocked = PR_IsInterruptsBlocked();
    PR_BlockInterrupt();
    PR_Lock(communicationLock);
    PR_Lock(msgLock);
    PR_Lock(replyLock);
    msg.msg.receive.id = TCP_ReleaseSocket(fd2, -1);
    msg.msg.receive.type = sock->type;
    msg.msg.receive.domain = sock->domain;
    msg.msg.receive.protocol = sock->protocol;
    msg.type = MSG_RECEIVE;
    PR_NotifyCondVar(msgCondVar);
    PR_Unlock(msgLock);
    PR_ASSERT(PR_WaitCondVar(replyCondVar, PR_INTERVAL_NO_TIMEOUT) == PR_SUCCESS);
    if (reply.msg.receive.private_idx != -1) {
        sock->private_idx = reply.msg.receive.private_idx;
        ss->sequenceNumber = reply.msg.receive.sequenceNumber;
        printf("sendSocketToThread(%lx) fd %d, private_idx %d, sequence number is %d\n", me, fd, sock->private_idx, ss->sequenceNumber);
        PR_SetThreadPrivate(sock->private_idx, (void *)ss);
    } else {
        printf("sendSocketToThread(%lx) error %d\n", reply.errno);

        retval = PR_FAILURE;
        PR_SetError(PR_UNKNOWN_ERROR, reply.errno);
        PR_Lock(msgLock);
        msg.type = MSG_CLOSE;
        msg.msg.close.private_idx = sock->private_idx;
        msg.msg.close.sequenceNumber = ss->sequenceNumber;
        PR_NotifyCondVar(msgCondVar);
        PR_Unlock(msgLock);
        PR_WaitCondVar(replyCondVar, PR_INTERVAL_NO_TIMEOUT);
    }
    PR_Unlock(replyLock);
    PR_Unlock(communicationLock);
    if (!isInterruptsBlocked)
        PR_UnblockInterrupt();
    if (retval == PR_FAILURE)
        goto error;

    return retval;
error:
    printf("sendsocket failed, closing socket\n");
    if (fd2 >= 0) {
        TCP_CloseSocket(fd2);
    }

    if (ss != NULL) {
        PR_Free(ss);
    }
    return PR_FAILURE;
}

/* The keeper of the sockets
 * It gets sockets handed to it from threads and also
 * gives sockets to other threads which share
 * the same socket
 */
static void SocketThread(void *notused) {
    PRBool done = PR_FALSE;
    PRStatus rc;
    PRThread *me = PR_GetCurrentThread();
    int i;
    PRUint32 idx;
    PRBool found;
    int sequenceNumber = 0;
    int num;
    struct SharedSocket *ss;

    printf("In socket thread\n");
    /* Max number for the thread private data */
    num = -1;
    PR_Lock(msgLock);
    PR_NotifyCondVar(msgCondVar);
    while(!done) {
        int retval, fd;
        PR_WaitCondVar(msgCondVar,PR_INTERVAL_NO_TIMEOUT);
        PR_Lock(replyLock);
        printf("Socket thread got msg %d\n", msg.type);
        switch (msg.type) {
        case MSG_OBTAIN:
            reply.msg.obtain.id = -1;
            ss = (struct SharedSocket *)
                PR_GetThreadPrivate(msg.msg.obtain.private_idx);
            if (ss != NULL) {
                fd = TCP_Dup2Socket(ss->fd, -1);
                if (fd < 0) {                    
                    if (TCP_Errno() == EMFILE) {
                        increaseSocketTable();
                        fd = TCP_Dup2Socket(ss->fd, -1);
                    }
                }                
                if (fd >= 0) {
                    reply.msg.obtain.id = TCP_ReleaseSocket(fd, -1);
                    reply.msg.obtain.sequenceNumber = ss->sequenceNumber;
                } else {
                    reply.msg.obtain.id = -1;
                    reply.errno = TCP_Errno();
                    printf("Dup2socket failed: %d\n", reply.errno);
                }
            } else {
                reply.errno = EBADF;
            }
            break;

        case MSG_RECEIVE:
            reply.msg.receive.private_idx = -1;
            rc = PR_SUCCESS;
            found = PR_FALSE;
            for (idx = 0; idx < num+ 1; idx++) {
                if (PR_GetThreadPrivate(idx) == NULL) {
                    found = PR_TRUE;
                    break;
                }
            }

            if (!found) {
                rc = PR_NewThreadPrivateIndex(&idx, closeOpenSocketDTOR);
                if (rc != PR_SUCCESS) {
                    printf("NewPrivateIndex failed: %d\n", PR_GetError());
                }
            }

            if (rc == PR_SUCCESS) {               
                ss = PR_NEWZAP(struct SharedSocket);
                if (ss == NULL) {
                    reply.errno = ENOMEM;
                    break;
                }

                if (idx > num)
                    num = idx;
                ss->fd = TCP_ObtainSocket(msg.msg.receive.id, 
                    msg.msg.receive.type, 
                    msg.msg.receive.domain, msg.msg.receive.protocol);

                /* If we can't obtain, we may be out of sockets,
                 * expand and try again
                 */
                if (ss->fd < 0) {
                    increaseSocketTable();
                    ss->fd = TCP_ObtainSocket(msg.msg.receive.id, 
                        msg.msg.receive.type, 
                        msg.msg.receive.domain, msg.msg.receive.protocol);
                }

                if (ss->fd < 0) {
                    reply.errno = TCP_Errno();
                    PR_Free(ss);
                } else {
                    printf("Socket thread assigning sequence number %d to private_idx %d\n", sequenceNumber, idx);
                    reply.msg.receive.private_idx = idx;
                    reply.msg.receive.sequenceNumber = sequenceNumber++;
                    ss->sequenceNumber = reply.msg.receive.sequenceNumber;
                    PR_SetThreadPrivate(idx, (void *)ss);
                }
            } else {
                reply.msg.receive.private_idx = -1;
                reply.errno = ENFILE;
                PR_Free(ss);
            }
            break;

        case MSG_CLOSE:
            ss = (struct SharedSocket *)
                PR_GetThreadPrivate(msg.msg.close.private_idx);
            printf("Socket thread closing private_idx %d, socket %d, sequence number %d\n", msg.msg.close.private_idx, ss->fd, ss->sequenceNumber);
            if (msg.msg.close.sequenceNumber == ss->sequenceNumber) {
                PR_SetThreadPrivate(msg.msg.close.private_idx, NULL);
            }
            break;

        case MSG_CHECK:
            ss = (struct SharedSocket *)
                PR_GetThreadPrivate(msg.msg.check.private_idx);
            printf("Socket check private_idx %d, seq %d(%d)\n", msg.msg.check.private_idx, msg.msg.check.sequenceNumber, (ss != NULL) ? ss->sequenceNumber : -1);
            reply.msg.check.status = (ss != NULL && ss->sequenceNumber == 
                msg.msg.check.sequenceNumber) ? PR_SUCCESS : PR_FAILURE;
            break;

        case MSG_DONE:
            done = PR_TRUE;
            break;
        }
        PR_NotifyCondVar(replyCondVar);
        PR_Unlock(replyLock); 
    }
    PR_Unlock(msgLock);
    printf("Socket thread all done\n");
}
                
/* Obtains the socket from the thread-local variable
 * and possibly obtains the socket from the socket thread
 * Also does a sanity check of the socket descriptor
 */
static int _MD_Ensure_Socket(PRInt32 osfd) {
    _MDSocket *sock = (_MDSocket *)osfd;
    PRThread *me = PR_GetCurrentThread();
    struct SharedSocket *ss;
    int fd;
    PRBool isInterruptsBlocked;

    if (sock == NULL || sock->private_idx == -1) {
        return -1;
    }

    ss = (struct SharedSocket *)PR_GetThreadPrivate(sock->private_idx);
    printf("_MD_Ensure_Socket(%lx), fd from osfd %lx, private_idx %d, is %lx(%d)\n", me, osfd, sock->private_idx, ss, (ss != NULL) ? ss->fd : -1);
    if (ss == NULL) {
        PRInt32 id;

        ss = PR_NEWZAP(struct SharedSocket);
        if (ss == NULL) {
            PR_SetError(PR_OUT_OF_MEMORY_ERROR, 0);
            return -1;
        }
        isInterruptsBlocked = PR_IsInterruptsBlocked();
        PR_BlockInterrupt();
        PR_Lock(communicationLock);
        PR_Lock(msgLock);
        PR_Lock(replyLock);
        msg.type = MSG_OBTAIN;
        msg.msg.obtain.private_idx = sock->private_idx;
        PR_NotifyCondVar(msgCondVar);
        PR_Unlock(msgLock);
        PR_WaitCondVar(replyCondVar, PR_INTERVAL_NO_TIMEOUT);
        if (reply.msg.obtain.id != -1) {
            ss->fd = TCP_ObtainSocket(reply.msg.obtain.id, sock->type, sock->domain, sock->protocol);

            if (ss->fd == -1) {
                /* We may be out of sockets */
                increaseSocketTable();
                ss->fd = TCP_ObtainSocket(reply.msg.obtain.id, 
                    sock->type, sock->domain, sock->protocol);
            }

            if (ss->fd == -1) {
                printf("Obtained failed[2] %d\n", TCP_Errno());
                PR_SetError(PR_UNKNOWN_ERROR, TCP_Errno());

                PR_Free(ss);
                ss = NULL;
                fd = -1;
            } else {
                ss->sequenceNumber = reply.msg.obtain.sequenceNumber;
                fd = ss->fd;
            }
        } else {
            printf("Obtained failed %d\n", reply.errno);
            PR_SetError(PR_UNKNOWN_ERROR, reply.errno);
            PR_Free(ss);
            ss = NULL;
            fd = -1;
        }
        PR_SetThreadPrivate(sock->private_idx, (void *)ss);
        printf("_MD_Ensure_Socket(%lx), fd is now %lx(%d), sequenceNumber %d\n", me, ss, (ss!= NULL) ? ss->fd : -1, (ss != NULL) ? ss->sequenceNumber : -1);
    } else {
        printf("_MD_Ensure_Socket(%lx), doing socket check for fd %d, private_idx %d, sequenceNumber %d\n", me, ss->fd, sock->private_idx, ss->sequenceNumber);
        isInterruptsBlocked = PR_IsInterruptsBlocked();
        PR_BlockInterrupt();
        PR_Lock(communicationLock);
        PR_Lock(msgLock);
        PR_Lock(replyLock);
        msg.type = MSG_CHECK;
        msg.msg.check.private_idx = sock->private_idx;
        msg.msg.check.sequenceNumber = ss->sequenceNumber;
        PR_NotifyCondVar(msgCondVar);
        PR_Unlock(msgLock);
        PR_WaitCondVar(replyCondVar, PR_INTERVAL_NO_TIMEOUT);
        if (reply.msg.check.status == PR_SUCCESS)
            fd = ss->fd;
        else
            fd = -1;
    }
    PR_Unlock(replyLock);
    PR_Unlock(communicationLock);
    if (!isInterruptsBlocked)
        PR_UnblockInterrupt();      
    return fd;
}


/*
 * Closes the socket and also tells
 * the socket thread to close its socket
 */
PRInt32 _MD_CLOSE_SOCKET(PRInt32 osfd) {
    _MDSocket *sock = (_MDSocket *)osfd;
    PRThread *me = PR_GetCurrentThread();
    struct SharedSocket *ss = (struct SharedSocket *)PR_GetThreadPrivate(sock->private_idx);
    int sequenceNumber;
    int retval;
    PRBool isInterruptsBlocked;

    printf("Close(%lx) for sock %lx, private_idx %d, sock %lx, fd %d\n", me, osfd, sock->private_idx, ss, (ss != NULL) ? ss->fd : -1 );

    if (ss == NULL) {
        return -1;
    }

    sequenceNumber = ss->sequenceNumber;
    PR_SetThreadPrivate(sock->private_idx, NULL);
    isInterruptsBlocked = PR_IsInterruptsBlocked();
    PR_BlockInterrupt();
    PR_Lock(communicationLock);
    PR_Lock(msgLock);
    PR_Lock(replyLock);
    msg.type = MSG_CLOSE;
    msg.msg.close.private_idx = sock->private_idx;
    msg.msg.close.sequenceNumber = sequenceNumber;
    PR_NotifyCondVar(msgCondVar);
    PR_Unlock(msgLock);
    PR_WaitCondVar(replyCondVar, PR_INTERVAL_NO_TIMEOUT);
    PR_Unlock(replyLock);
    PR_Unlock(communicationLock);
    if (!isInterruptsBlocked)
        PR_UnblockInterrupt();
    PR_SetThreadPrivate(sock->private_idx, NULL);
    PR_Free(sock);
    return 1;
}

/*
 * Connects to a server
 */
PRInt32 _MD_CONNECT(
    PRFileDesc *osfd, const PRNetAddr *addr,
    PRUint32 addrlen, PRIntervalTime timeout) {
    PRThread *me = PR_GetCurrentThread();
    int fd =_MD_Ensure_Socket(osfd->secret->md.osfd);
    PRNetAddr addrCopy;
    struct sockaddr_in *t = (struct sockaddr_in *)&addrCopy;
    int retval;
    PRBool doneWait = PR_FALSE;
    
    printf("connect(%lx), osfd %lx fd %d\n", me, osfd->secret->md.osfd, fd);
    if (fd == -1)
        return -1;

    addrCopy = *addr;
    ((struct sockaddr *) &addrCopy)->sa_len = addrlen;
    ((struct sockaddr *) &addrCopy)->sa_family = addr->raw.family;
    printf("addrlen %d, sin_len %d, sin_family %d, sin_port %d\n", addrlen, t->sin_len, t->sin_family, ntohl(t->sin_port));
    while ((retval = TCP_Connect(fd, (struct sockaddr *)&addrCopy, addrlen)) == -1) {
        int err = TCP_Errno();
        printf("Connect(%lx) returned %d, errno is %d\n", me, retval, err);
        /* All done */
        if (osfd->secret->nonblocking) {
            _PR_MD_MAP_CONNECT_ERROR(TCP_Errno());
            break;
        }

        if (err == EISCONN) {
            retval = 0;
            break;
        } else if (err == ECONNREFUSED && doneWait) {
            _PR_MD_MAP_CONNECT_ERROR(err);
            break;
        } else if (err == EINVAL) {
            _PR_MD_MAP_CONNECT_ERROR(err);
            break;
        }

        doneWait = PR_TRUE;
        retval = local_io_wait(fd, TYPE_WRITE, timeout);
        if (_PR_PENDING_INTERRUPT(me)) {
            printf("Connect(%lx) got interrupted\n", me);
            PR_ClearInterrupt();
            retval = -1;
            break;
        }
        if (retval < 0) {
            _PR_MD_MAP_CONNECT_ERROR(TCP_Errno());
            break;
        } else if (retval == 0) {
            retval = -1;
            break;
        }
    }
    printf("Connect returned %d, errno is %d\n", retval, TCP_Errno());
    return retval;
    
}

/**
 * Accepts a connection
 * Sends the new socket to the socket thread
 */
PRInt32 _MD_ACCEPT(
    PRFileDesc *osfd, PRNetAddr *addr,
    PRUint32 *addrlen, PRIntervalTime timeout) {
    struct sockaddr_in tmp;
    PRThread *me = PR_GetCurrentThread();
    int fd = _MD_Ensure_Socket(osfd->secret->md.osfd);
    _MDSocket *sock2 = (_MDSocket *)-1;
    _MDSocket *sock;
    PRStatus rc;
    int fd2;
    int retval = -1;

    printf("accept(%lx), osfd %lx, fd %d\n", me, osfd->secret->md.osfd, fd);

    if (fd == -1)
        return -1;

    sock2 = PR_NEWZAP(_MDSocket);
    if (sock2 == NULL) {
        goto error;
    }
    printf("Going to accept %d, %lx, %d\n", fd, addr, *addrlen);
    while ((retval = TCP_Accept(fd,(struct sockaddr *)addr, addrlen)) < 0) {
        int err = TCP_Errno();

        printf("Accept(%lx) returned %d, errno is %d\n", me, retval, err);
        /* All done */
        if (osfd->secret->nonblocking) {
            _PR_MD_MAP_ACCEPT_ERROR(err);
            goto error;
        }

        if (err == EAGAIN || err == EWOULDBLOCK || err == ECONNABORTED || err == EDEADLK) {
            int io = local_io_wait(fd, TYPE_READ, timeout);
            if (_PR_PENDING_INTERRUPT(me)) {
                PR_ClearInterrupt();
                printf("accept(%lx) got interrupt\n", me);
                goto error;
            }
            if (io < 0) {
                _PR_MD_MAP_ACCEPT_ERROR(TCP_Errno());
                goto error;
            } else if (io == 0) {
                goto error;
            }
        } else {
            _PR_MD_MAP_ACCEPT_ERROR(TCP_Errno());
            goto error;
        }
    }

    printf("Accept2(%lx) returned %d, errno is %d\n", me, retval, TCP_Errno());
 
    sock = (_MDSocket *)osfd->secret->md.osfd;
    sock2->type = sock->type;
    sock2->domain = sock->domain;
    sock2->protocol = sock->protocol;
    if (sendSocketToThread(retval, sock2) == PR_FAILURE)
        goto error;

    printf("Accept returned %d, len is %d, errno is %d, newsock is %lx, private_idx is %d\n", retval, *addrlen, TCP_Errno(), sock2, sock2->private_idx);
    /* ignore the sa_len field of struct sockaddr */    
    if (addr) {
        addr->raw.family = AF_INET;
    }

    return (PRInt32)sock2;

error:
    if (sock2 != (_MDSocket *)-1 && sock2 != NULL) {
        PR_Free(sock2);
    }

    if (retval >= 0) {
        printf("Accept error: closing socket %d\n", retval);
        TCP_CloseSocket(retval);
    }
    return -1;
}

/*
 * Binds a socket to a port
 */ 
PRInt32 _MD_BIND(PRFileDesc *osfd, const PRNetAddr *addr, PRUint32 addrlen) {
    PRThread *me = PR_GetCurrentThread();
    PRNetAddr addrCopy;
    int fd =_MD_Ensure_Socket(osfd->secret->md.osfd);
    int retval;

    if (fd == -1)
        return -1;

    addrCopy = *addr;
    ((struct sockaddr *) &addrCopy)->sa_len = addrlen;
    ((struct sockaddr *) &addrCopy)->sa_family = addr->raw.family;

    printf("bind(%lx), osfd %lx fd %d, port %d, len %d, size %d\n", me, osfd->secret->md.osfd, fd, ntohl(((struct sockaddr_in *)&addrCopy)->sin_port), addrlen, sizeof(struct sockaddr_in));
    retval = TCP_Bind(fd,(struct sockaddr *)&addrCopy, addrlen);
    if (retval == -1) {
        printf("Bind failed %d\n", TCP_Errno());
        _PR_MD_MAP_BIND_ERROR(TCP_Errno());
    }

    printf("bind(%lx) returns %d, errno is %d\n", me, retval, TCP_Errno());
    return retval;
}

/*
 * Sets the listen queue for accepting
 */
PRInt32 _MD_LISTEN(PRFileDesc *osfd, PRIntn backlog) {
    PRThread *me = PR_GetCurrentThread();
    int fd = _MD_Ensure_Socket(osfd->secret->md.osfd);
    int retval;

    printf("Listen(%lx), osfd %lx, fd %d\n", me, osfd->secret->md.osfd, fd);
   
    if (fd == -1)
        return -1;

    retval = TCP_Listen(fd, backlog);
    if (retval == -1) {
        _PR_MD_MAP_LISTEN_ERROR(TCP_Errno());
    }

    return retval;
}

/*
 * Shut down the read/write end of a socket
 */
PRInt32 _MD_SHUTDOWN(PRFileDesc *osfd, PRIntn how) {
    PRThread *me = PR_GetCurrentThread();
    int fd =_MD_Ensure_Socket(osfd->secret->md.osfd);
    int retval;
    if (fd == -1)
        return -1;

    printf("shutdown(%lx), osfd %lx %d\n", me, osfd->secret->md.osfd, fd);
    retval = TCP_ShutDown(fd, how);
    if (retval == -1) {
        _PR_MD_MAP_SHUTDOWN_ERROR(TCP_Errno());
    }
    return retval;
}

/*
 * Recv data from a socket
 */
PRInt32 _MD_RECV(PRFileDesc *osfd, void *buf, PRInt32 amount, 
                               PRIntn flags, PRIntervalTime timeout) {
    PRThread *me = PR_GetCurrentThread();
    int fd =_MD_Ensure_Socket(osfd->secret->md.osfd);
    int retval;

    if (fd == -1)
        return -1;

    printf("recv(%lx), osfd %lx fd %d, amount %d, timeout %d\n", me, osfd->secret->md.osfd, fd, amount, timeout);
    /* TODO Should be < 0 */
    while ((retval = TCP_Recv(fd, buf, amount, flags)) < 0) {
        printf("recv(%lx) returns %d, errno is %d\n", me, retval, TCP_Errno());        
        /* All done */
        if (osfd->secret->nonblocking) {
            _PR_MD_MAP_RECV_ERROR(TCP_Errno());
            break;
        }

        retval = local_io_wait(fd, TYPE_READ, timeout);
        if (_PR_PENDING_INTERRUPT(me)) {
            printf("recv(%lx) got interrupted\n", me);
            PR_ClearInterrupt();
            retval = -1;
            break;
        }
        if (retval < 0) {            
            _PR_MD_MAP_RECV_ERROR(TCP_Errno());
            break;
        } else if (retval == 0) {
            retval = -1;
            break;
        }
    }
    printf("recv(%lx) returns %d, errno is %d\n", me, retval, TCP_Errno());
    return retval;
}

/*
 * Send data over the socket
 */
PRInt32 _MD_SEND(
    PRFileDesc *osfd, const void *buf, PRInt32 amount, PRIntn flags, 
    PRIntervalTime timeout) {
    PRThread *me = PR_GetCurrentThread();
    int fd =_MD_Ensure_Socket(osfd->secret->md.osfd);
    int retval;
    if (fd == -1)
        return -1;
   

    printf("send(%lx), osfd %lx fd %d buf %lx, amount %d, flags %d\n", me, osfd->secret->md.osfd, fd, buf, amount, flags);
    while ((retval = TCP_Send(fd, buf, amount, flags)) == -1) {
        printf("Send(%lx) returns %d, error is %d\n", me, retval, TCP_Errno());
        /* All done */
        if (osfd->secret->nonblocking) {
            _PR_MD_MAP_SEND_ERROR(TCP_Errno());
            break;
        }

        retval = local_io_wait,(fd, TYPE_WRITE, timeout);
        if (_PR_PENDING_INTERRUPT(me)) {
            printf("send(%lx) got interrupted\n", me);
            PR_ClearInterrupt();
            retval = -1;
            break;
        }
        if (retval < 0) {
            _PR_MD_MAP_SEND_ERROR(TCP_Errno());
            break;
        } else if (retval == 0) {
            retval = -1;
            break;
        }
    }

    printf("send(%lx) returns %d, error is %d\n", me, retval, TCP_Errno());
    return retval;
}

/*
 * Get the port of the socket
 */
PRStatus _MD_GETSOCKNAME(
    PRFileDesc *osfd, PRNetAddr *addr, PRUint32 *addrlen) {
    PRThread *me = PR_GetCurrentThread();
    int fd =_MD_Ensure_Socket(osfd->secret->md.osfd);
    int retval;
    if (fd == -1)
        return -1;

    printf("getsockname(%lx), osfd %lx %d\n", me, osfd->secret->md.osfd, fd);
    retval = TCP_GetSockName(fd, (struct sockaddr *)addr, addrlen);
    if (retval == 0) {
        /* ignore the sa_len field of struct sockaddr */
        if (addr) {
            addr->raw.family = ((struct sockaddr *) addr)->sa_family;
        }
    }

    printf("getsockname(%lx) returns %d, errno is %d\n", me, retval, TCP_Errno());
    if (retval == -1) {
        _PR_MD_MAP_GETSOCKNAME_ERROR(TCP_Errno());
    }
    return retval == 0 ? PR_SUCCESS : PR_FAILURE;
}

/*
 * Get the hostname/port of the socket on the other side of this one
 */
PRStatus _MD_GETPEERNAME(
    PRFileDesc *osfd, PRNetAddr *addr, PRUint32 *addrlen) {
    PRThread *me = PR_GetCurrentThread();
    int fd =_MD_Ensure_Socket(osfd->secret->md.osfd);
    int retval;

    if (fd == -1)
        return -1;

    printf("getpeername(%lx), osfd %lx %d\n", me, osfd->secret->md.osfd, fd);
    retval = TCP_GetPeerName(fd, (struct sockaddr *)addr, addrlen);
    printf("getpeername(%lx), retval is %d, errno is %d\n", me, retval, TCP_Errno());
    if (retval == -1) {
        _PR_MD_MAP_GETPEERNAME_ERROR(TCP_Errno());
    }
    return retval == 0 ? PR_SUCCESS: PR_FAILURE;
}

/*
 * Get information about a socket
 */
PRStatus _MD_GETSOCKOPT(
    PRFileDesc *osfd, PRInt32 level, PRInt32 optname, char* optval, PRInt32* optlen) {
    PRThread *me = PR_GetCurrentThread();
    int fd =_MD_Ensure_Socket(osfd->secret->md.osfd);
    int retval;

    printf("getsockopt(%lx), osfd %lx %d\n", me, osfd->secret->md.osfd, fd);

    if (fd == -1)
        return -1;

    retval = TCP_GetSockOpt(fd, level, optname, optval, optlen);
    if (retval == -1) {
        _PR_MD_MAP_GETSOCKOPT_ERROR(TCP_Errno());
    }
    printf("getsockopt(%lx) returns %d, errno is %d\n", me, retval, TCP_Errno());
    return retval == 0 ? PR_SUCCESS: PR_FAILURE;

}

/*
 * Set information about a socket
 */
PRStatus _MD_SETSOCKOPT(
    PRFileDesc *osfd, PRInt32 level, PRInt32 optname,
    const char* optval, PRInt32 optlen) {
    PRThread *me = PR_GetCurrentThread();
    int fd =_MD_Ensure_Socket(osfd->secret->md.osfd);
    int retval;

    printf("setsockopt(%lx), osfd %lx, fd %d\n", me, osfd->secret->md.osfd, fd);
    printf("setsockopt(%lx), level %d, optname %d, optval %lx, optlen %d\n", me ,level, optname, optval, optlen);

    if (fd == -1)
        return -1;

    retval = TCP_SetSockOpt(fd, level, optname, optval, optlen);
    if (retval == -1) {
        _PR_MD_MAP_SETSOCKOPT_ERROR(TCP_Errno());
    }
    printf("setsockopt(%lx) returns %d, errno is %d\n", me, retval, TCP_Errno());
    return retval == 0 ? PR_SUCCESS: PR_FAILURE;


}

/*
 * Receive data from a particular host
 */
PRInt32 _MD_RECVFROM(
    PRFileDesc *osfd, void *buf, PRInt32 amount, PRIntn flags,
    PRNetAddr *addr, PRUint32 *addrlen, PRIntervalTime timeout) {
    PRThread *me = PR_GetCurrentThread();
    int fd =_MD_Ensure_Socket(osfd->secret->md.osfd);
    int retval;

    if (fd == -1)
        return -1;
    while ((retval = TCP_RecvFrom(fd, buf, amount, flags, addr, addrlen)) == -1) {
        printf("RecvFrom(%lx) returns %d, error is %d\n", me, retval, TCP_Errno());
        /* All done */
        if (osfd->secret->nonblocking) {
            _PR_MD_MAP_RECVFROM_ERROR(TCP_Errno());
            break;
        }

        retval = local_io_wait(fd, TYPE_READ, timeout);
        if (_PR_PENDING_INTERRUPT(me)) {
            printf("recvfrom(%lx) got interrupted\n", me);
            PR_ClearInterrupt();
            retval = -1;
            break;
        }
        if (retval < 0) {
            _PR_MD_MAP_RECVFROM_ERROR(TCP_Errno());
            break;
        } else if (retval == 0) {
            retval = -1;
            break;
        }

    }

    printf("RecvFrom(%lx) returns %d, error is %d\n", me, retval, TCP_Errno());
    if (retval != -1) {
        /* ignore the sa_len field of struct sockaddr */
        if (addr) {
            addr->raw.family = ((struct sockaddr *) addr)->sa_family;
        }
    }
    return retval;
}

/*
 * Send data to a particular host
 */
PRInt32 _MD_SENDTO(
    PRFileDesc *osfd, const void *buf, PRInt32 amount, PRIntn flags,
    const PRNetAddr *addr, PRUint32 addrlen, PRIntervalTime timeout) {
    PRThread *me = PR_GetCurrentThread();
    int fd =_MD_Ensure_Socket(osfd->secret->md.osfd);
    PRNetAddr addrCopy;
    int retval;

    if (fd == -1)
        return -1;
    printf("sendto(%lx), osfd %lx %d\n", me, osfd->secret->md.osfd, fd);

    addrCopy = *addr;
    ((struct sockaddr *) &addrCopy)->sa_len = addrlen;
    ((struct sockaddr *) &addrCopy)->sa_family = addr->raw.family;

    while ((retval = TCP_SendTo(fd, buf, amount, flags, &addrCopy, addrlen)) == -1) {
        /* All done */
        if (osfd->secret->nonblocking) {
            _PR_MD_MAP_SENDTO_ERROR(TCP_Errno());
            break;
        }

        retval = local_io_wait(fd, TYPE_WRITE, timeout);
        if (_PR_PENDING_INTERRUPT(me)) {
            printf("sendto(%lx) got interrupted\n", me);
            PR_ClearInterrupt();
            retval = -1;
            break;
        }
        if (retval < 0) {
            _PR_MD_MAP_SENDTO_ERROR(TCP_Errno());
            break;
        } else if (retval == 0) {
            retval = -1;
            break;
        }
    }
    return retval;
}

/*
 * Create a new socket.
 * Also sends the socket to the socket thread
 */
PRInt32 _MD_SOCKET(int type, int domain, int protocol) {
  int retval;
  int fd;
  PRThread *me = PR_GetCurrentThread();
  _MDSocket *sock;

  if (me->AmiTCP_Base == NULL) {
      PR_SetError(PR_PROTOCOL_NOT_SUPPORTED_ERROR, 0);
      return -1;
  }

  sock = PR_NEWZAP(_MDSocket);
  if (sock == NULL) 
      return -1;
  sock->type = type;
  sock->domain = domain;
  sock->protocol = protocol;

  fd = TCP_Socket(type, domain, protocol);

  printf("Socket(%lx) returns %d, errno is %d\n", me, fd, TCP_Errno());

  if (fd < 0) {
      _PR_MD_MAP_SOCKET_ERROR(TCP_Errno());
      PR_Free(sock);
      return -1;
  } else {
      if (sendSocketToThread(fd, sock) == PR_FAILURE)
          goto error;
  }

  printf("socket(%lx), newsock is %lx, private_idx is %d, fd is %d\n", me, sock, sock->private_idx, fd);
  return (PRInt32)sock;

error:
  if (sock != (_MDSocket *)-1 && sock != NULL) {
      PR_Free(sock);
      sock = (_MDSocket *)-1;
  }

  printf("Socket error, closing socket %d\n", fd);
  if (fd >= 0)
      TCP_CloseSocket(fd);

  return (PRInt32)sock;
}

/*
 * See if there is data available on the socket
 */
PRInt32 _MD_SOCKETAVAILABLE(PRFileDesc *osfd) {
    PRThread *me = PR_GetCurrentThread();
    int fd =_MD_Ensure_Socket(osfd->secret->md.osfd);
    PRInt32 result;

    if (fd < 0)
        return -1;

    printf("socketavailable(%lx), osfd %lx %d\n", me, osfd->secret->md.osfd, fd);

    if (TCP_IoctlSocket(fd, FIONREAD, &result) < 0) {
        printf("socketavailable(%lx), returns =1, errno is %d\n", me, TCP_Errno());        
        _PR_MD_MAP_SOCKETAVAILABLE_ERROR(TCP_Errno());
        return -1;
    }

    printf("socketavailable(%lx), returns %d, errno is %d\n", me, result, TCP_Errno());

    return result;
}

/*
 * Get the appropriate errno for a connect error
 */
PRInt32 _MD_amiga_get_nonblocking_connect_error(int osfd) 
{
    PRThread *me = PR_GetCurrentThread();
    int fd =_MD_Ensure_Socket(osfd);
    PRInt32 result;
    int err;
    size_t optlen = sizeof(err);

    if (fd == -1)
        return EBADF;
    if (TCP_GetSockOpt(fd, SOL_SOCKET, SO_ERROR, (char *) &err, &optlen) == -1) {
        printf("unix_connect error(%d), returns %lx, errno is %d\n", me, -1, TCP_Errno());
        return TCP_Errno();
    } else {
        printf("unix_connect error(%d), returns %lx, errno is %d\n", me, err, TCP_Errno());
        return err;
    }
}

/*
 * Poll a set of file descriptors for reading/writing with a optional timeout
 */
PRInt32 _MD_PR_POLL(PRPollDesc *pds, PRIntn npds, PRIntervalTime timeout) 
{
    int i;
    int fd;
    PRInt32 retval = -1, rc;
    fd_set in;
    fd_set out;
    fd_set err;
    PRThread *me = PR_GetCurrentThread();
    PRInt32 flags;
    PRInt32 ready;
    PRBool done = PR_FALSE;
    PRBool firstTime = PR_TRUE;
    int maxfd = -1 ;
    struct StandardPacket sps[npds];

    if (npds == 0) {
        PR_Sleep(timeout);
        return 0;
    }

    FD_ZERO(&in);
    FD_ZERO(&out);
    FD_ZERO(&err);

    memset(sps, 0, sizeof(sps[0]) * npds);

    printf("Poll(%lx) with #fds %d, timeout %d\n", me, npds, timeout);
    ready = 0;

    /* Send off a timer request waiting for x seconds */
    if (timeout != PR_INTERVAL_NO_TIMEOUT) {
        me->sleepRequest->tr_node.io_Command = TR_ADDREQUEST;


        me->sleepRequest->tr_time.tv_secs = timeout / _PR_MD_INTERVAL_PER_SEC();
        me->sleepRequest->tr_time.tv_micro = timeout % _PR_MD_INTERVAL_PER_SEC()
            * (1000000 / _PR_MD_INTERVAL_PER_SEC());
        me->sleepRequestUsed = PR_TRUE;
    }

    while (!done) {

        for (i = 0; i < npds; i++) {
            struct StandardPacket *sp = &sps[i];
            struct FileHandle *fh;
            struct PRPollDesc *pd = &pds[i];

            PRInt16 in_flags_read = 0, in_flags_write = 0;
            PRInt16 out_flags_read = 0, out_flags_write = 0;

            if ((NULL != pd->fd) && (0 != pd->in_flags)) {
                if (pd->in_flags & PR_POLL_READ) {
                    in_flags_read = (pd->fd->methods->poll)(
                        pd->fd,
                        pd->in_flags & ~PR_POLL_WRITE,
                                                            &out_flags_read);
                }
                if (pd->in_flags & PR_POLL_WRITE) {
                    in_flags_write = (pd->fd->methods->poll)(
                        pd->fd,
                        pd->in_flags & ~PR_POLL_READ,
                        &out_flags_write);
                }
                if ((0 != (in_flags_read & out_flags_read))
                    || (0 != (in_flags_write & out_flags_write))) {
                    /* this one is ready right now */
                    if (0 == ready) {
                        /*
                         * We will return without calling the system
                         * poll function.  So zero the out_flags
                         * fields of all the poll descriptors before
                         * this one.
                         */
                        int j;
                        for (j = 0; j < i; j++) {
                            pd->out_flags = 0;
                        }
                    }
                    ready += 1;
                    pd->out_flags = out_flags_read | out_flags_write;
                } else {
                    PRFileDesc *bottom;
                    pd->out_flags = 0; 

                    /* make sure this is an NSPR supported stack */
                    bottom = PR_GetIdentitiesLayer(pd->fd, PR_NSPR_IO_LAYER);
                    PR_ASSERT(NULL != bottom);  /* what to do about that? */
                    if ((NULL != bottom)
                        && (_PR_FILEDESC_OPEN == bottom->secret->state)) {
                        printf("Poll(%lx) Bottom fd %lx, osfd is %lx, type is %lx\n", me, bottom, bottom->secret->md.osfd, bottom->methods->file_type);
                        switch (bottom->methods->file_type) {
                        case PR_DESC_PIPE:
                        case PR_DESC_FILE:
                            sp = &sps[i];
                            printf("Poll(%lx) fd %d(%lx) is a file,pipe\n", me, i, pd->fd);
                            sp->sp_Msg.mn_Node.ln_Name = (char *)&sp->sp_Pkt;
                            sp->sp_Pkt.dp_Link = &sp->sp_Msg;
                            sp->sp_Pkt.dp_Res1 = NULL;
                            sp->sp_Pkt.dp_Res2 = NULL;
                            sp->sp_Pkt.dp_Port = NULL;
                            sp->sp_Msg.mn_Node.ln_Type = 0;
                            fh = (struct FileHandle *)BTOCPTR(bottom->secret->md.osfd);
                            printf("Poll(%lx) sel port is %lx, BPTR is %lx, fh is %lx, packet is %lx\n", me, me->selectPort, bottom->secret->md.osfd, fh, sp);
                            sp->sp_Pkt.dp_Port = me->selectPort;
                            sp->sp_Pkt.dp_Type = ACTION_WAIT_CHAR;
                            sp->sp_Pkt.dp_Arg1 = 100000;
                            PutMsg(fh->fh_Type, (struct Message *)sp);
                            break;       
                        case PR_DESC_SOCKET_TCP:
                        case PR_DESC_SOCKET_UDP:
                            fd = _MD_Ensure_Socket(bottom->secret->md.osfd);
                            printf("Poll(%lx) fd %d(%lx) is a socket, fd is %d\n", me, i, pd->fd, fd);
                            if (fd < 0) {
                                pd->out_flags = PR_POLL_NVAL;
                                continue;
                            }
                            if (fd > maxfd)
                                maxfd = fd;

                            if (pd->in_flags & PR_POLL_READ) {
                                FD_SET(fd, &in);
                            }
                            if (pd->in_flags & PR_POLL_WRITE) {
                                FD_SET(fd, &out);
                            } 
                            if (pd->in_flags & PR_POLL_EXCEPT) {
                                FD_SET(fd, &err);
                            }
                            break;
                        }
                    }
                }
            }
        }

        /* Do this here just in case the timeout happens before the select */
        if (firstTime && timeout != PR_INTERVAL_NO_TIMEOUT) {
            SendIO((struct IORequest *)me->sleepRequest);
        }

        firstTime = PR_FALSE;

        me->state = _PR_IO_WAIT;
        flags = 1 << me->selectPort->mp_SigBit | 1 << me->port->mp_SigBit;
        printf("Poll(%lx) Going to waitselect, maxfd is %d, signals are %lx\n", me, maxfd, flags);
        retval = TCP_WaitSelect(maxfd + 1, &in, &out, &err, NULL, &flags);
        rc = retval;

        /* See if someone is trying to kill me by setting my state to dead */
        if (me->state == _PR_DEAD_STATE) {
            printf("Thread %x was forceably killed from WaitSelect in poll\n", me);
            longjmp(me->jmpbuf, 1);
        }
        me->state = _PR_RUNNING;

        printf("Poll(%lx) select returns %d, errno is %d\n", me, retval, TCP_Errno());

        if (flags & (1 << me->selectPort->mp_SigBit)) {
            struct StandardPacket *sp;
            printf("File descriptor waiting...\n");

            while ((sp = (struct StandardPacket *)GetMsg(me->selectPort)) != NULL) {
                printf("Got packet %lx\n", sp);
                for (i = 0; i < npds && sp != &sps[i]; i++)
                    ;

                printf("File descriptor packet %d is waiting, res1 is %d, res2 is %d\n", i, sp->sp_Pkt.dp_Res1, sp->sp_Pkt.dp_Res2);
                pds[i].out_flags = 0;


                if (pds[i].in_flags & PR_POLL_READ) {
                    /* there are two possible answers: error (packet not supported) 
                     * and the `real' answer.
                     * An error is treated as to allow input, so select() won't block
                     * indefinitely...
                     * & 1 converts dos-true (-1) into normal true (1) ;-)
                     */

                    if (sp->sp_Pkt.dp_Res2 || sp->sp_Pkt.dp_Res1 & 1) {
                        pds[i].out_flags |= PR_POLL_READ;
                        retval++;
                    }
                }        
                /* Always available for write? How can I detect pipe blocks ?? */
                if (pds[i].in_flags & PR_POLL_WRITE) {
                    pds[i].out_flags |= PR_POLL_WRITE;
                    retval++;
                }

                sp->sp_Pkt.dp_Port = NULL;
            }

            if (retval != rc) {
                done = TRUE;
            }
        }

        if (flags & (1 << me->port->mp_SigBit)) {
            /* timeout or interrupt */
            printf("Poll got timeout/interrupt\n");
            done = TRUE;
        }

        for (i = 0; i < npds; i++) {
            struct StandardPacket *sp = &sps[i];
            struct StandardPacket *tmp;
            struct FileHandle *fh;
            struct PRPollDesc *pd = &pds[i];
            if ((NULL != pd->fd) && (0 != pd->in_flags)) {
                PRFileDesc *bottom = PR_GetIdentitiesLayer(pd->fd, PR_NSPR_IO_LAYER);
                PR_ASSERT(NULL != bottom);

                switch (bottom->methods->file_type) {
                case PR_DESC_PIPE:
                case PR_DESC_FILE:
                    /* Wait for any packets to return */
                    if (sp->sp_Pkt.dp_Port != NULL) {
                        for (;;) {
                            if ((tmp = (struct StandardPacket *)GetMsg(me->selectPort)) != NULL) {
                                tmp->sp_Pkt.dp_Port = NULL;
                                if (tmp == sp)
                                    break;
                            } else {
                                WaitPort(me->selectPort);
                            }
                        }
                    }
                    break;
                case PR_DESC_SOCKET_TCP:
                case PR_DESC_SOCKET_UDP:
                    if (rc < 0)
                        continue;
                    done = TRUE;
                    fd = _MD_Ensure_Socket(bottom->secret->md.osfd);
                    pds[i].out_flags = 0;
                    if (FD_ISSET(fd, &in)) {
                        printf("Fd %d is waiting for read\n", fd);
                        pds[i].out_flags |= PR_POLL_READ;
                    }
                    if (FD_ISSET(fd, &out)) {
                        printf("Fd %d is waiting for write\n", fd);
                        pds[i].out_flags |= PR_POLL_WRITE;
                    }

                    if (FD_ISSET(fd, &err)) {
                        printf("Fd %d is waiting for except\n", fd);
                        pds[i].out_flags |= PR_POLL_EXCEPT;
                    }
                    break;
                default:
                    break;
                }
            }
        }
    }

    while (GetMsg(me->port))
        ;
    if (me->sleepRequestUsed) {
        if (!(CheckIO((struct IORequest *)me->sleepRequest))) {
            AbortIO((struct IORequest *)me->sleepRequest);
            WaitIO((struct IORequest *)me->sleepRequest);
        }
    }
            
    printf("Poll(%lx) returns %d\n", me, retval);
    return retval;
}

/*
 * Returns the native handle for a socket
 */
int _MD_NATIVE_HANDLE(PRFileDesc *fd) {
    PR_ASSERT(FALSE);
    switch (fd->methods->file_type) {
    case PR_DESC_PIPE:
    case PR_DESC_FILE:
        return fd->secret->md.osfd;
    case PR_DESC_SOCKET_TCP:
    case PR_DESC_SOCKET_UDP:
        return _MD_Ensure_Socket(fd->secret->md.osfd);
    }
}

/*
 * Make the socket non-blocking
 */
void _PR_MD_MAKE_NONBLOCK(PRFileDesc *osfd) {
    int fd;
    PRThread *me = PR_GetCurrentThread();
    long arg = 1;
    switch (osfd->methods->file_type) {
    case PR_DESC_SOCKET_TCP:
    case PR_DESC_SOCKET_UDP:
        fd = _MD_Ensure_Socket(osfd->secret->md.osfd);
        printf("%lx making socket %lx (%d) nonblocking\n", me, osfd->secret->md.osfd, fd);
        TCP_IoctlSocket(fd, FIONBIO, (void *)&arg);
        break;

    default:
        break;
    }        
}

/*
 * Get the hostname for the machine
 */
PRStatus _MD_gethostname(char *name, PRUint32 namelen) {
    PRThread *me = PR_GetCurrentThread();
    if (me->AmiTCP_Base == NULL) {
        strncpy(name, "localhost", namelen-1);
        if (namelen > 0)
            name[namelen-1] = '\0';
        return PR_SUCCESS;
    } else {
        LONG error = TCP_GetHostName(name, (LONG)namelen);
        return (error < 0) ? PR_FAILURE : PR_SUCCESS;
    }
}

/**
 * Returns the appropriate FD depending on the type
 * For sockets, I have got to release the socket so
 * I can obtain it in the other process. I let the socket thread do that
 */
int _MD_MAP_FD(PRFileDesc *fd) {
    _MDSocket *sock;
    _MDSocket *s2;
    PRBool isInterruptsBlocked;
    int id;
    switch (fd->methods->file_type) {
    case PR_DESC_SOCKET_TCP:
    case PR_DESC_SOCKET_UDP:
        sock = (_MDSocket *)fd->secret->md.osfd;
        /* I use AllocVec here so the other side can free it */
        s2 = AllocVec(sizeof(_MDSocket), MEMF_PUBLIC);
        if (s2 == NULL)
            return -1;
        s2->type = sock->type;
        s2->domain = sock->domain;
        s2->protocol = sock->protocol;
        isInterruptsBlocked = PR_IsInterruptsBlocked();
        PR_BlockInterrupt();
        PR_Lock(communicationLock);
        PR_Lock(msgLock);
        PR_Lock(replyLock);
        msg.type = MSG_OBTAIN;
        msg.msg.obtain.private_idx = sock->private_idx;
        PR_NotifyCondVar(msgCondVar);
        PR_Unlock(msgLock);
        PR_WaitCondVar(replyCondVar, PR_INTERVAL_NO_TIMEOUT);
        id = reply.msg.obtain.id;
        PR_Unlock(replyLock);
        PR_Unlock(communicationLock);
        if (!isInterruptsBlocked)
            PR_UnblockInterrupt();      

        if (id != -1) {
            s2->private_idx = reply.msg.obtain.id;
            return (int)s2;
        } else {
            FreeVec(s2);
            return -1;
        }
        break;

    default:
        return fd->secret->md.osfd;
    }
}

/**
 * Unmap the socket descriptor done with _MD_MAP_FD
 * Obtain the socket and pass it off to the socket thread 
 */
int _MD_UNMAP_FD(PRDescType type, int osfd) {
    _MDSocket *sock;
    _MDSocket *s2;
    PRThread *me = PR_CurrentThread();

    switch (type) {
    case PR_DESC_SOCKET_TCP:
    case PR_DESC_SOCKET_UDP:
        sock = (_MDSocket *)osfd;
        s2 = (_MDSocket *)PR_NEWZAP(_MDSocket);
        if (s2 != NULL) {
            int s;
            s2->type = sock->type;
            s2->domain = sock->domain;
            s2->protocol = sock->protocol;
            s = TCP_ObtainSocket(sock->private_idx, s2->type, s2->domain, s2->protocol);
            if (s == -1) {
                increaseSocketSize();
                s = TCP_ObtainSocket(sock->private_idx, s2->type, s2->domain, s2->protocol);
            }
            FreeVec(sock);
            if (s != -1) {
                if (sendSocketToThread(s, s2) == PR_FAILURE) {
                    return -1;
                }
                return (int)s2;
            } else {
                return -1;
            }
        } else {
            return -1;
        }
        break;

    default:
        return osfd;
    }
}
