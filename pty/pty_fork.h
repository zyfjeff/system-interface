#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define MAX_SNAME 1000
int ptyMasterOpen(char *slaveName,size_t snLen);

pid_t ptyFork(int *masterFd,char *slaveName,size_t snLen,
              const struct termios *slaveTermios,const struct winsize *slaveWS)

{
    int mfd,slaveFd,saveErrno;
    pid_t childPid;
    char slname[MAX_SNAME];

    //setp1 打开伪终端主设备
    mfd = ptyMasterOpen(slname,MAX_SNAME);
    if(mfd == -1)
        return -1;

    //setp2 拷贝伪终端设备名到缓冲区
    if(slname != NULL) {
        if(strlen(slname) < snLen) {
            strncpy(slaveName,slname,snLen);
        } else {
            close(mfd);
            errno = EOVERFLOW;
            return -1;
        }
    }

    //setp3 fork一个子进程
    childPid = fork();
    if(childPid == -1) {
        saveErrno = errno;
        close(mfd);
        errno = saveErrno;
        return -1;
    }

    //setp4 父进程设置伪设备的fd,并返回子进程的pid
    if(childPid != 0) {
        *masterFd = mfd;
        return childPid;
    }

    //setp5 使这个子进程创建一个会话，成为这个会话的首领进程
    if(setsid() == -1) {
        perror("ptyFork:setsid");
        exit(EXIT_FAILURE);
    }

    //setp6
    close(mfd);

    //setp7 打开伪设备的从设备
    slaveFd = open(slname,O_RDWR);
    if(slaveFd == -1) {
        perror("ptyFork:open-salve");
        exit(EXIT_FAILURE);
    }

    //setp8 设置从设备的TTY属性
#ifdef  TIOCSCITY
    if(ioctl(salveFd,TIOCSCITY,0) == -1) {
        perror("ptyFork:ioctl-TIOCSCITY");
        exit(EXIT_FAILURE);
    }
#endif

    //setp9 设置
    if(slaveTermios != NULL)
        if(tcsetattr(slaveFd,TCSANOW,slaveTermios) == -1) {
            perror("ptyFork:tcsetattr");
        }

    //setp10
    if(slaveWS != NULL)
        if(ioctl(slaveFd,TIOCSWINSZ,slaveWS) == -1) {
            perror("ptyFork:ioctl-TIOCSWINSZ");
            exit(EXIT_FAILURE);
        }

    //setp11 将从设备的标准输出　输入　错误输入关联
    if(dup2(slaveFd,STDIN_FILENO) != STDIN_FILENO) {
        perror("ptyFork:dup2-STDIN_FILENO");
        exit(EXIT_FAILURE);
    }

    if(dup2(slaveFd,STDOUT_FILENO) != STDOUT_FILENO) {
        perror("ptyFork:dup2-STDOUT_FILENO");
        exit(EXIT_FAILURE);

    }

    if(dup2(slaveFd,STDERR_FILENO) != STDERR_FILENO) {
        perror("ptyFork:dup2-STDERR_FILENO");
        exit(EXIT_FAILURE);
    }

    if(slaveFd > STDERR_FILENO)
        close(slaveFd);

    return 0;
}


