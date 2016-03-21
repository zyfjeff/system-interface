#include <sys/stat.h>
#include <fcntl.h>
#include <libgen.h>
#include <termios.h>
#include <sys/select.h>
#include "pty_fork.h"

#define BUF_SIZE 256
#define MAX_NAME 1000



struct termios ttyOrig;

static void ttyReset(void)
{
    //重置窗口模式
    if(tcsetattr(STDIN_FILENO,TCSANOW,&ttyOrig) == -1){
        perror("tcsetattr");
        exit(EXIT_FAILURE);
    }
}

int main(int argc,char *argv[])
{
    char slaveName[MAX_SNAME];
    char *shell;
    int masterFd,scriptFd;
    struct winsize ws;
    fd_set inFds;
    char buf[BUF_SIZE];
    ssize_t numRead;
    pid_t childPid;

    //setp1 获取终端属性
    if(tcgetattr(STDIN_FILENO,&ttyOrig) == -1) {
        perror("tcgetattr");
        exit(EXIT_FAILURE);
    }
    //获取终端窗口大小
    if(ioctl(STDIN_FILENO,TIOCGWINSZ,&ws) < 0) {
        perror("ioctl-TIOCGWINSZ");
        exit(EXIT_FAILURE);
    }

    //setp2 创建伪设备对，
    childPid = ptyFork(&masterFd,slaveName,MAX_SNAME,&ttyOrig,&ws);
    if(childPid == -1) {
        perror("ptyFork");
        exit(EXIT_FAILURE);
    }

    //setp3 获取shell类型,然后子进程运行面向终端程序
    if(childPid == 0) {
        shell = getenv("SHELL");
        if(shell == NULL || *shell == '\0')
            shell = "/bin/sh";

    //setp4 子进程执行shell，一个面向终端的程序
        execlp(shell,shell,(char *)NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    //setp5 打开记录script文件
    scriptFd = open((argc > 1)? argv[1]:"typescript",
                     O_WRONLY|O_CREAT|O_TRUNC,
                     S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|
                     S_IROTH|S_IWOTH);

    if(scriptFd == -1) {
        perror("open typescript");
        exit(EXIT_FAILURE);
    }

    //setp6 通过ttySetRaw设置终端属性为raw模式
    ttySetRaw(STDIN_FILENO,&ttyOrig);

    //setp7 设置退出时的退出函数
    if(atexit(ttyReset) != 0) {
        perror("atexit");
        exit(EXIT_FAILURE);
    }

    //setp8
    for(;;) {
        FD_ZERO(&inFds);
        FD_SET(STDIN_FILENO,&inFds);
        FD_SET(masterFd,&inFds);

    //监听 STDIN_FILENO masterfd
    //setp9
        if(select(masterFd + 1,&inFds,NULL,NULL,NULL) == -1) {
            perror("select");
            exit(EXIT_FAILURE);
        }

    //setp10

        if(FD_ISSET(STDIN_FILENO,&inFds)) {
            numRead = read(STDIN_FILENO,buf,BUF_SIZE);
            if(numRead <= 0) {
                exit(EXIT_SUCCESS);
            }

            if(write(masterFd,buf,numRead) != numRead) {
                perror("partial/failed write (masterFd)");
            }
        }

    //setp11
        if(FD_ISSET(masterFd,&inFds)) {
            numRead = read(masterFd,buf,BUF_SIZE);
            if(numRead <= 0)
                exit(EXIT_SUCCESS);

            if(write(STDIN_FILENO,buf,numRead) != numRead) {
                perror("partial/failed write(STDIN_FILENO)");
                exit(EXIT_FAILURE);
            }

            if(write(scriptFd,buf,numRead) != numRead) {
                perror("partial/failed write (scriptFd)");
            }
        }
    }
}
