#define _GNU_SOURCE
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

static void handler(int sig)
{
    printf("PID %ld: caught signal %2d (%s)\n",(long)getpid(),
            sig,strsignal(sig));
}

int main(int argc,char *argv[])
{
    pid_t parentPid,childPid;
    int j;
    struct sigaction sa;
    if(argc < 2 || strcmp(argv[1],"--help") == 0) {
        fprintf(stderr,"%s {d|s}.....[ > sig.loh 2>&1 ]\n",argv[0]);
    }
    setbuf(stdout,NULL);
    parentPid = getpid();
    printf("PID of parent process is:   %ld\n",(long)parentPid);
    printf("Foreground process group ID is: %ld\n",
            (long)tcgetpgrp(STDIN_FILENO));

    for(j = 1; j < argc; ++j) {
        childPid = fork();
        if(childPid == -1) {
            perror("fork:");
            exit(EXIT_FAILURE);
        }

        if(childPid == 0) {
            if(argv[j][0] == 'd')
                if(setpgid(0,0) == -1) {    //移动到一个新的进程组中
                    perror("fork:");
                    exit(EXIT_FAILURE);
                }

            sigemptyset(&sa.sa_mask);
            sa.sa_flags = 0;
            sa.sa_handler = handler;

            if(sigaction(SIGHUP,&sa,NULL) == -1) {
                    perror("fork:");
                    exit(EXIT_FAILURE);
            }
            break;      //child exits loop
        }
    }

    alarm(60);
    printf("PID=%ld PGID=%ld\n",(long)getpid(),(long)getpgrp());
    for(;;)
        pause();
}
