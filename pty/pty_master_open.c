#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

/*
 *
 *  打开一个未使用的伪终端主设备，调用grantpt()并通过unlockpt对其解锁，然后将对应的伪终端从设备名拷贝到slaveName所
 *  指向的缓冲区中,调用者必须通过参数snLen指定的缓冲区的空间大小．
 *
 */

int ptyMasterOpen(char *slaveName,size_t snLen)
{
    int masterFd,slavedErrno;
    char *p;
    masterFd = posix_openpt(O_RDWR|O_NOCTTY);
    if(masterFd == -1)
        return -1;
    if(grantpt(masterFd) == -1) {
        slavedErrno = errno;
        close(masterFd);
        errno = slavedErrno;
        return -1;
    }

    if(unlockpt(masterFd) == -1){
        slavedErrno = errno;
        close(masterFd);
        errno = slavedErrno;
        return -1;
    }

    p = ptsname(masterFd);
    if(p == NULL) {
        slavedErrno = errno;
        close(masterFd);
        errno = slavedErrno;
        return -1;
    }

    if(strlen(p) < snLen) {
        strncpy(slaveName,p,snLen);
    } else {
        close(masterFd);
        errno = EOVERFLOW;
        return -1;
    }

    return masterFd;
}


