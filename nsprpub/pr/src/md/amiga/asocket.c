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
#include "primpl.h"

#define  AMITCP_BASE_NAME me->AmiTCP_Base
#include "amitcp.h"


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
 * CreateNewPrivateIndex functions. If a thread uses a socket created
 * by another thread, it asks the Socket Thread to obtain a copy of it
 * Socket cleanup per-thread is handled automatically by the destructor
 * of the thread-local variable code
 */
#define MSG_RECEIVE   1
#define MSG_OBTAIN   2
#define MSG_CLOSE    3
#define MSG_DONE     4

/* Message sent to the Socket Thread */
struct SocketMsg {
    int type; /* One of MSG_RECEIVE, MSG_OBTAIN, MSG_CLOSE, MSG_DONE */
    struct {
        int type;
        int domain;
        int protocol;
    }  socket; /* Structure used on MSG_RECEIVE */
    int fd; /* if type is MSG_RECEIVE, the id returned from ObtainSocket */
            /* if type is MSG_OBTAIN, the private index for the socket */
};

/* Reply from the socket thread */
struct ReplyMsg {
    int id; /* if type is MSG_OBTAIN, the id from ReleaseSocket */
    int private_idx; /* if type is MSG_RECEIVE, the new private index for the socket */
    int errno;/* Any errors encountered */
};
    

static void SocketThread(void *);

/* Global messages/replies to the socket thread */
static struct SocketMsg msg;
static struct ReplyMsg reply;
/* If you want to talk to the socket thread, lock this lock first */
static PRLock *communicationLock;
static PRLock *msgLock;
static PRLock *replyLock;
static PRCondVar *msgCondVar;
static PRCondVar *replyCondVar;

/* The Socket Thread */
static PRThread *sockThread;

/* Destructor for the ThreadPrivate socket descriptor */
static void closeOpenSocketDTOR(void *prm) {
    PRThread *me = PR_GetCurrentThread();
    int fd = (int)prm;
    if (fd != 0) {
        TCP_CloseSocket(fd - 1);
    }
}

/*
 * Initialize the locks and socket thread
 */
void _MD_INIT_IO(void) {
    communicationLock = PR_NewLock();
    msgCondVar = PR_NewCondVar(msgLock = PR_NewLock());
    replyCondVar = PR_NewCondVar(replyLock = PR_NewLock());
    sockThread = PR_CreateThread(PR_SYSTEM_THREAD, 
                                 SocketThread, NULL, PR_PRIORITY_NORMAL, 
                                 PR_LOCAL_THREAD, 
                                 PR_JOINABLE_THREAD, 0);
}


/*
 * Clean up all the locks and the socket thread 
 */
void _PR_CleanupSocket(void) {
    PR_Lock(communicationLock);
    PR_Lock(msgLock);
    PR_Lock(replyLock);
    msg.type = MSG_DONE;
    PR_NotifyCondVar(msgCondVar);
    PR_Unlock(msgLock);
    PR_WaitCondVar(replyCondVar, PR_INTERVAL_NO_TIMEOUT);
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
    struct timeval tv;
    int sel;

    if (timeout != PR_INTERVAL_NO_TIMEOUT) {
        tv.tv_sec = timeout / _PR_MD_INTERVAL_PER_SEC();
        tv.tv_micro = timeout % _PR_MD_INTERVAL_PER_SEC();
    }

    PR_fprintf(PR_STDERR, "Local_io_wait(%lx) fd %d, type %d, timeout %d\n", me, fd, type, timeout);
    FD_ZERO(&fd_read);
    FD_ZERO(&fd_write);
    FD_ZERO(&fd_except);

    FD_SET(fd, &fd_except);
    if (type == TYPE_READ) {
        FD_SET(fd, &fd_read);
    } else {
        FD_SET(fd, &fd_write);
    }

    sel = TCP_WaitSelect(fd + 1, &fd_read, &fd_write, &fd_except, 
                         (timeout == PR_INTERVAL_NO_TIMEOUT) ? NULL : &tv, 1L << me->port->mp_SigBit);

    PR_fprintf(PR_STDERR, "WaitSelect(%lx) returned %d, error is %d\n", me, sel, TCP_Errno());
    if (sel == -1) {
        _PR_MD_MAP_SELECT_ERROR(TCP_Errno());
    } else if (sel == 0) {
        if (SetSignal(0, 0) & (1 << me->port->mp_SigBit)) {
            PR_fprintf(PR_STDERR, "Interrupted\n");
            PR_SetError(PR_PENDING_INTERRUPT_ERROR, 0);
        } else {
            PR_SetError(PR_IO_TIMEOUT_ERROR, 0);
        }
    }
    return sel;
}

static void sendSocketToThread(int fd, _MDSocket *sock) {
    PRThread *me = PR_GetCurrentThread();
    long arg = 1;

    int fd2 = TCP_Dup2Socket(fd, -1);
    PR_Lock(communicationLock);
    PR_Lock(msgLock);
    PR_Lock(replyLock);
    TCP_IoctlSocket(fd, FIONBIO, &arg);
    msg.fd = TCP_ReleaseSocket(fd2, -1);
    msg.socket.type = sock->type;
    msg.socket.domain = sock->domain;
    msg.socket.protocol = sock->protocol;
    msg.type = MSG_RECEIVE;
    PR_NotifyCondVar(msgCondVar);
    PR_Unlock(msgLock);
    PR_WaitCondVar(replyCondVar, PR_INTERVAL_NO_TIMEOUT);
    sock->private_idx = reply.private_idx;

    PR_Unlock(replyLock);
    PR_Unlock(communicationLock);
    PR_SetThreadPrivate(sock->private_idx, (void *)fd + 1);
}

static void SocketThread(void *notused) {
    PRBool done = PR_FALSE;
    PRThread *me = PR_GetCurrentThread();

    PR_Lock(msgLock);

    while(!done) {
        int fd, fd2, retval;

        PR_WaitCondVar(msgCondVar,PR_INTERVAL_NO_TIMEOUT);
        PR_Lock(replyLock);

        PR_fprintf(PR_STDERR, "Socket thread got msg %d\n", msg.type);
        switch (msg.type) {
        case MSG_OBTAIN:
            fd = PR_GetThreadPrivate(msg.fd);
            fd2 = TCP_Dup2Socket(fd - 1, -1);
            if (fd2 == -1) {
                reply.errno = TCP_Errno();
                reply.id = -1;
            } else {
                reply.id = TCP_ReleaseSocket(fd2, -1);
            }
            break;
        case MSG_RECEIVE:
            fd = TCP_ObtainSocket(msg.fd, msg.socket.type, 
                                  msg.socket.domain, msg.socket.protocol);
            if (fd == -1) {
                reply.errno = TCP_Errno();
                reply.private_idx = -1;
            } else {
                PR_NewThreadPrivateIndex(&reply.private_idx, closeOpenSocketDTOR);
                PR_SetThreadPrivate(reply.private_idx, (void *)fd + 1);
            }
            break;

        case MSG_CLOSE:
            fd = (int)PR_GetThreadPrivate(msg.fd);
            retval = TCP_CloseSocket(fd - 1);
            break;
        case MSG_DONE:
            done = PR_TRUE;
            break;
        }
        PR_NotifyCondVar(replyCondVar);
        PR_Unlock(replyLock);
    }
    PR_Unlock(msgLock);
}
                

/* Obtains the socket from the thread-local variable
 * and possibly obtains the socket from the socket thread
 */
static int _MD_Ensure_Socket(PRInt32 osfd) {
    _MDSocket *sock = (_MDSocket *)osfd;
    PRThread *me = PR_GetCurrentThread();
    int fd;
    if (sock->private_idx == -1 || sock->released == 1) {
        return -1;
    }

    fd = (int)PR_GetThreadPrivate(sock->private_idx);
    PR_fprintf(PR_STDERR, "_MD_Ensure_Socket(%lx), fd from osfd %lx, private %d, is %d\n", me, osfd, sock->private_idx, fd - 1);
    if (fd == 0) {
        PR_Lock(communicationLock);
        PR_Lock(msgLock);
        PR_Lock(replyLock);
        msg.type = MSG_OBTAIN;
        msg.fd = sock->private_idx;
        PR_NotifyCondVar(msgCondVar);
        PR_Unlock(msgLock);
        PR_WaitCondVar(replyCondVar, PR_INTERVAL_NO_TIMEOUT);
        fd = TCP_ObtainSocket(reply.id, sock->type, sock->domain, sock->protocol);
        
        PR_Unlock(replyLock);
        PR_Unlock(communicationLock);
        PR_SetThreadPrivate(sock->private_idx, (void *)fd + 1);
        PR_fprintf(PR_STDERR, "_MD_Ensure_Socket(%lx), fd is now %d\n", me, fd);
    } else {
        fd--;
    }

    return fd;
}
            
  
PRInt32 _MD_CLOSE_SOCKET(PRInt32 osfd) {
    _MDSocket *sock = (_MDSocket *)osfd;
    PRThread *me = PR_GetCurrentThread();
    int fd = _MD_Ensure_Socket(osfd);
    int retval;
    PR_fprintf(PR_STDERR, "Close(%lx) for sock %lx, fd %d, private_idx %d\n", me, osfd, fd, sock->private_idx);
    if (fd == -1) {
        return -1;
    }

    retval = TCP_CloseSocket(fd);
    PR_Lock(communicationLock);
    PR_Lock(msgLock);
    PR_Lock(replyLock);
    msg.type = MSG_CLOSE;
    msg.fd = sock->private_idx;
    sock->released = 1;
    PR_NotifyCondVar(msgCondVar);
    PR_Unlock(msgLock);
    PR_WaitCondVar(replyCondVar, PR_INTERVAL_NO_TIMEOUT);
    PR_Unlock(replyLock);
    PR_Unlock(communicationLock);
    PR_fprintf(PR_STDERR, "Close(%lx), got reply from socket thread\n", me);
    return osfd;
}

PRInt32 _MD_CONNECT(
    PRFileDesc *osfd, const PRNetAddr *addr,
    PRUint32 addrlen, PRIntervalTime timeout) {
    PRThread *me = PR_GetCurrentThread();
    int fd =_MD_Ensure_Socket(osfd->secret->md.osfd);
    PRNetAddr addrCopy;
    struct sockaddr_in *t = (struct sockaddr_in *)&addrCopy;
    int retval;
    PRBool doneWait = PR_FALSE;
    
    PR_fprintf(PR_STDERR, "connect(%lx), osfd %lx fd %d\n", me, osfd->secret->md.osfd, fd);
    if (fd == -1)
        return -1;

    addrCopy = *addr;
    ((struct sockaddr *) &addrCopy)->sa_len = addrlen;
    ((struct sockaddr *) &addrCopy)->sa_family = addr->raw.family;
    PR_fprintf(PR_STDERR, "addrlen %d, sin_len %d, sin_family %d, sin_port %d\n", addrlen, t->sin_len, t->sin_family, ntohl(t->sin_port));
    while ((retval = TCP_Connect(fd, (struct sockaddr *)&addrCopy, addrlen)) == -1) {
        int err = TCP_Errno();
        PR_fprintf(PR_STDERR, "Connect(%lx) returned %d, errno is %d\n", me, retval, err);
        /* All done */
        if (err == EISCONN) {
            retval = 0;
            break;
        } else if (err == ECONNREFUSED && doneWait) {
            break;
        }

        doneWait = PR_TRUE;
        retval = local_io_wait(fd, TYPE_WRITE, timeout);
        if (retval == -1) {
            _PR_MD_MAP_CONNECT_ERROR(TCP_Errno());
            break;
        } else if (retval == 0) {
            retval = -1;
            break;
        }
    }
    PR_fprintf(PR_STDERR, "Connect returned %d\n", retval);
    if (retval == -1) {
        PR_fprintf(PR_STDERR, "Errno is %d\n", TCP_Errno());
    }
    return retval;
    
}

PRInt32 _MD_ACCEPT(
    PRFileDesc *osfd, PRNetAddr *addr,
    PRUint32 *addrlen, PRIntervalTime timeout) {
    PRThread *me = PR_GetCurrentThread();
    int fd =_MD_Ensure_Socket(osfd->secret->md.osfd);
    _MDSocket *sock2 = (_MDSocket *)-1;
    _MDSocket *sock;
    int fd2;
    int retval;

    PR_fprintf(PR_STDERR, "accept(%lx), osfd %lx, fd %d\n", me, osfd->secret->md.osfd, fd);
    if (fd == -1)
        return -1;

    
    PR_fprintf(PR_STDERR, "Going to accept %d, %lx, %lx\n", fd, addr, addrlen);
    while ((retval = TCP_Accept(fd,(struct sockaddr *)addr, addrlen)) == -1) {
        int err = TCP_Errno();
        PR_fprintf(PR_STDERR, "Accept returned %d, errno is %d\n", retval, err);
        if (err == EAGAIN || err == EWOULDBLOCK || err == ECONNABORTED || err == EDEADLK) {
            if ((retval = local_io_wait(fd, TYPE_READ, timeout)) <= 0) {
                sock2 = (_MDSocket *)-1;
                goto done;
            }
#if 0
        } else if ((err === EINTR) && (!_PR_PENDING_INTERRUPT(me))) {
            continue;
#endif
        } else {
            goto done;
        }
    }

    sock2 = PR_NEWZAP(_MDSocket);
    if (sock2 == NULL) {
        return -1;
    }
 
    sock = (_MDSocket *)osfd->secret->md.osfd;
    sock2->type = sock->type;
    sock2->domain = sock->domain;
    sock2->protocol = sock->protocol;
    sendSocketToThread(retval, sock2);
    PR_fprintf(PR_STDERR, "Accept returned %d, len is %d, errno is %d, newsock is %lx, private_idx is %d\n", retval, *addrlen, TCP_Errno(), sock2, sock2->private_idx);
done:
    /* ignore the sa_len field of struct sockaddr */    
    if (addr) {
        addr->raw.family = AF_INET;
    }

    return (PRInt32)sock2;
}

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

    PR_fprintf(PR_STDERR, "bind(%lx), osfd %lx fd %d, port %d, len %d, size %d\n", me, osfd->secret->md.osfd, fd, ntohl(((struct sockaddr_in *)&addrCopy)->sin_port), addrlen, sizeof(struct sockaddr_in));
    retval = TCP_Bind(fd,(struct sockaddr *)&addrCopy, addrlen);
    if (retval == -1) {
        PR_fprintf(PR_STDERR, "Bind failed %d\n", TCP_Errno());
        _PR_MD_MAP_BIND_ERROR(TCP_Errno());
    }
    return retval;
}

PRInt32 _MD_LISTEN(PRFileDesc *osfd, PRIntn backlog) {
    PRThread *me = PR_GetCurrentThread();
    int fd = _MD_Ensure_Socket(osfd->secret->md.osfd);
    int retval;

    PR_fprintf(PR_STDERR, "Listen(%lx), osfd %lx, fd %d\n", me, osfd->secret->md.osfd, fd);
   
    if (fd == -1)
        return -1;

    retval = TCP_Listen(fd, backlog);
    if (retval == -1) {
        _PR_MD_MAP_LISTEN_ERROR(TCP_Errno());
    }

    return retval;
}

PRInt32 _MD_SHUTDOWN(PRFileDesc *osfd, PRIntn how) {
    PRThread *me = PR_GetCurrentThread();
    int fd =_MD_Ensure_Socket(osfd->secret->md.osfd);
    int retval;
    if (fd == -1)
        return -1;

    PR_fprintf(PR_STDERR, "shutdown(%lx), osfd %lx %d\n", me, osfd->secret->md.osfd, fd);
    retval = TCP_ShutDown(fd, how);
    if (retval == -1) {
        _PR_MD_MAP_SHUTDOWN_ERROR(TCP_Errno());
    }
    return retval;
}

PRInt32 _MD_RECV(PRFileDesc *osfd, void *buf, PRInt32 amount, 
                               PRIntn flags, PRIntervalTime timeout) {
    PRThread *me = PR_GetCurrentThread();
    int fd =_MD_Ensure_Socket(osfd->secret->md.osfd);
    int retval;

    if (fd == -1)
        return -1;

    PR_fprintf(PR_STDERR, "recv(%lx), osfd %lx fd %d, amount %d, timeout %d\n", me, osfd->secret->md.osfd, fd, amount, timeout);
    /* TODO Should be < 0 */
    while ((retval = TCP_Recv(fd, buf, amount, flags)) < 0) {
        PR_fprintf(PR_STDERR, "recv returns %d, errno is %d\n", retval, TCP_Errno());        
        retval = local_io_wait(fd, TYPE_READ, timeout);
        if (retval == -1) {            
            _PR_MD_MAP_RECV_ERROR(TCP_Errno());
            break;
        } else if (retval == 0) {
            retval = -1;
            break;
        }
    }
    PR_fprintf(PR_STDERR, "recv returns %d, errno is %d\n", retval, TCP_Errno());
    return retval;
}

PRInt32 _MD_SEND(
    PRFileDesc *osfd, const void *buf, PRInt32 amount, PRIntn flags, 
    PRIntervalTime timeout) {
    PRThread *me = PR_GetCurrentThread();
    int fd =_MD_Ensure_Socket(osfd->secret->md.osfd);
    int retval;
    if (fd == -1)
        return -1;
   

    PR_fprintf(PR_STDERR, "send(%lx), osfd %lx fd %d buf %lx, amount %d, flags %d\n", me, osfd->secret->md.osfd, fd, buf, amount, flags);
    while ((retval = TCP_Send(fd, buf, amount, flags)) == -1) {
        PR_fprintf(PR_STDERR, "Send returns %d, error is %d\n", retval, TCP_Errno());
        retval = local_io_wait,(fd, TYPE_WRITE, timeout);
        if (retval == -1) {
            _PR_MD_MAP_SEND_ERROR(TCP_Errno());
            break;
        } else if (retval == 0) {
            retval = -1;
            break;
        }
    }

    PR_fprintf(PR_STDERR, "Send returns %d, error is %d\n", retval, TCP_Errno());
    return retval;
}

PRStatus _MD_GETSOCKNAME(
    PRFileDesc *osfd, PRNetAddr *addr, PRUint32 *addrlen) {
    PRThread *me = PR_GetCurrentThread();
    int fd =_MD_Ensure_Socket(osfd->secret->md.osfd);
    int retval;
    if (fd == -1)
        return -1;

    PR_fprintf(PR_STDERR, "getsockname(%lx), osfd %lx %d\n", me, osfd->secret->md.osfd, fd);
    retval = TCP_GetSockName(fd, (struct sockaddr *)addr, addrlen);
    if (retval == 0) {
        /* ignore the sa_len field of struct sockaddr */
        if (addr) {
            addr->raw.family = ((struct sockaddr *) addr)->sa_family;
        }
    }

    PR_fprintf(PR_STDERR, "getsockname(%lx) returns %d, errno is %d\n", retval, TCP_Errno());
    if (retval == -1) {
        _PR_MD_MAP_GETSOCKNAME_ERROR(TCP_Errno());
    }
    return retval == 0 ? PR_SUCCESS : PR_FAILURE;
}

PRStatus _MD_GETPEERNAME(
    PRFileDesc *osfd, PRNetAddr *addr, PRUint32 *addrlen) {
    PRThread *me = PR_GetCurrentThread();
    int fd =_MD_Ensure_Socket(osfd->secret->md.osfd);
    int retval;

    if (fd == -1)
        return -1;

    PR_fprintf(PR_STDERR, "getpeername(%lx), osfd %lx %d\n", me, osfd->secret->md.osfd, fd);
    retval = TCP_GetPeerName(fd, (struct sockaddr *)addr, addrlen);
    PR_fprintf(PR_STDERR, "getpeeername(%lx), retval is %d, errno is %d\n", me, retval, TCP_Errno());
    if (retval == -1) {
        _PR_MD_MAP_GETPEERNAME_ERROR(TCP_Errno());
    }
    return retval == 0 ? PR_SUCCESS: PR_FAILURE;
}

PRStatus _MD_GETSOCKOPT(
    PRFileDesc *osfd, PRInt32 level, PRInt32 optname, char* optval, PRInt32* optlen) {
    PRThread *me = PR_GetCurrentThread();
    int fd =_MD_Ensure_Socket(osfd->secret->md.osfd);
    int retval;

    if (fd == -1)
        return -1;

    PR_fprintf(PR_STDERR, "getsockopt(%lx), osfd %lx %d\n", me, osfd->secret->md.osfd, fd);
    retval = TCP_GetSockOpt(fd, level, optname, optval, optlen);
    if (retval == -1) {
        _PR_MD_MAP_GETSOCKOPT_ERROR(TCP_Errno());
    }
    PR_fprintf(PR_STDERR, "getsockopt(%lx) returns %d, errno is %d\n", me, retval, TCP_Errno());
    return retval == 0 ? PR_SUCCESS: PR_FAILURE;

}

PRStatus _MD_SETSOCKOPT(
    PRFileDesc *osfd, PRInt32 level, PRInt32 optname,
    const char* optval, PRInt32 optlen) {
    PRThread *me = PR_GetCurrentThread();
    int fd =_MD_Ensure_Socket(osfd->secret->md.osfd);
    int retval;

    if (fd == -1)
        return -1;

    PR_fprintf(PR_STDERR, "setsockopt(%lx), osfd %lx, fd %d\n", me, osfd->secret->md.osfd, fd);
    PR_fprintf(PR_STDERR, "setsockopt(%lx), level %d, optname %d, optval %lx, optlen %d\n", me ,level, optname, optval, optlen);
    retval = TCP_SetSockOpt(fd, level, optname, optval, optlen);
    if (retval == -1) {
        _PR_MD_MAP_SETSOCKOPT_ERROR(TCP_Errno());
    }
    PR_fprintf(PR_STDERR, "setsockopt(%lx) returns %d, errno is %d\n", me, retval, TCP_Errno());
    return retval == 0 ? PR_SUCCESS: PR_FAILURE;


}

PRInt32 _MD_RECVFROM(
    PRFileDesc *osfd, void *buf, PRInt32 amount, PRIntn flags,
    PRNetAddr *addr, PRUint32 *addrlen, PRIntervalTime timeout) {
    PRThread *me = PR_GetCurrentThread();
    int fd =_MD_Ensure_Socket(osfd->secret->md.osfd);
    int retval;

    if (fd == -1)
        return -1;
    while ((retval = TCP_RecvFrom(fd, buf, amount, flags, addr, addrlen)) == -1) {
        PR_fprintf(PR_STDERR, "RecvFrom returns %d, error is %d\n", retval, TCP_Errno());
        retval = local_io_wait(fd, TYPE_READ, timeout);
        if (retval == -1) {
            _PR_MD_MAP_RECVFROM_ERROR(TCP_Errno());
            break;
        } else if (retval == 0) {
            retval = -1;
            break;
        }

    }

    if (retval != -1) {
        /* ignore the sa_len field of struct sockaddr */
        if (addr) {
            addr->raw.family = ((struct sockaddr *) addr)->sa_family;
        }
    }
    return retval;
}

PRInt32 _MD_SENDTO(
    PRFileDesc *osfd, const void *buf, PRInt32 amount, PRIntn flags,
    const PRNetAddr *addr, PRUint32 addrlen, PRIntervalTime timeout) {
    PRThread *me = PR_GetCurrentThread();
    int fd =_MD_Ensure_Socket(osfd->secret->md.osfd);
    PRNetAddr addrCopy;
    int retval;

    if (fd == -1)
        return -1;
    PR_fprintf(PR_STDERR, "sendto(%lx), osfd %lx %d\n", me, osfd->secret->md.osfd, fd);

    addrCopy = *addr;
    ((struct sockaddr *) &addrCopy)->sa_len = addrlen;
    ((struct sockaddr *) &addrCopy)->sa_family = addr->raw.family;

    while ((retval = TCP_SendTo(fd, buf, amount, flags, &addrCopy, addrlen)) == -1) {
        retval = local_io_wait(fd, TYPE_WRITE, timeout);
        if (retval == -1) {
            _PR_MD_MAP_SENDTO_ERROR(TCP_Errno());
            break;
        } else if (retval == 0) {
            retval = -1;
            break;
        }
    }
    return retval;
}

PRInt32 _MD_SOCKET(int type, int domain, int protocol) {
  int retval;
  int fd;
  PRThread *me = PR_GetCurrentThread();
  _MDSocket *sock;

  if (me->AmiTCP_Base == NULL) {
      /* TODO NOT IMPLEMENTED */
  }
  sock = PR_NEWZAP(_MDSocket);
  if (sock == NULL) 
      return -1;
  sock->type = type;
  sock->domain = domain;
  sock->protocol = protocol;

  fd = TCP_Socket(type, domain, protocol);

  if (fd == -1) {
      _PR_MD_MAP_SOCKET_ERROR(TCP_Errno());
      PR_Free(sock);
      return -1;
  } else {
      sendSocketToThread(fd, sock);
  }

  PR_fprintf(PR_STDERR, "socket(%lx), newsock is %lx, private_idx is %d, fd is %d\n", me, sock, sock->private_idx, fd);
  return (PRInt32)sock;
}

PRInt32 _MD_SOCKETAVAILABLE(PRFileDesc *osfd) {
    PRThread *me = PR_GetCurrentThread();
    int fd =_MD_Ensure_Socket(osfd->secret->md.osfd);
    PRInt32 result;

    if (fd == -1)
        return -1;

    if (TCP_IoctlSocket(fd, FIONREAD, &result) < 0) {
        _PR_MD_MAP_SOCKETAVAILABLE_ERROR(TCP_Errno());
        return -1;
    }
    return result;
}


PRInt32 _MD_PR_POLL(PRPollDesc *pds, PRIntn npds, PRIntervalTime timeout) {
#warning _MD_PR_POLL not implemented
    assert(0);
}
