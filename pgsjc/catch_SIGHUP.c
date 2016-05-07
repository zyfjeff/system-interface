#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void handler(int sig)
{

}

int main(int argc,char *argv[])
{
    pid_t childPid;
    struct sigaction sa;
    setbuf(stdout,NULL);
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = handler;
    //设置信号掩码
    if(sigaction(SIGHUP,&sa,NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
    //创建子进程
    childPid = fork();

    if(childPid == -1) {
            perror("sigaction");
            exit(EXIT_FAILURE);
    }

    //创建ok，子进程，创建新的进程组
    //printf("%d\n",argc);
    if(childPid == 0 && argc > 1)
        if(setpgid(0,0) == -1) {
            perror("sigaction");
            exit(EXIT_FAILURE);
        }



    printf("PID=%ld; PPID=%ld; PGID=%ld; SID=%ld\n",(long)getpid(),
            (long)getppid(),(long)getpgrp(),(long)getsid(0));
    alarm(60);

    for(;;) {
        pause();
        printf("%ld: caught SIGHUP\n",(long)getpid());
    }
}
