#define _GNU_SOURCE
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void handler(int sig)
{
    printf("PID=%ld: caught signal %d (%s)\n",(long)getpid(),
            sig,strsignal(sig));
}

int main(int argc,char *argv[])
{
    int j;
    struct sigaction sa;
    if(argc < 2 || strcmp(argv[1],"--help") == 0) {
        fprintf(stderr,"%s {s|p} ...\n",argv[0]);
        exit(EXIT_FAILURE);
    }

    setbuf(stdout,NULL);
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = handler;

    if(sigaction(SIGHUP,&sa,NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    if(sigaction(SIGCONT,&sa,NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    printf("parent: PID=%ld, PPID=%ld,PGID=%ld,SID=%ld\n",
            (long)getpid(),(long)getppid(),
            (long)getpgrp(),(long)getsid(0));

    for(j = 1; j < argc;++j) {
        switch(fork()) {
            case -1:
                perror("sigaction");
                exit(EXIT_FAILURE);
            case 0:
                printf("child: PID=%ld, PPID=%ld,PGID=%ld,SID=%ld\n",
                        (long)getpid(),(long)getppid(),
                        (long)getpgrp(),(long)getsid(0));
                if(argv[j][0] == 's') {
                    printf("PID=%ld stopping\n",(long)getpid());
                    raise(SIGSTOP);
                } else {
                    alarm(60);
                    printf("PID=%ld pausing\n",(long)getpid());
                    pause();
                }
                _exit(EXIT_SUCCESS);
            default:
                break;
        }
    }

    sleep(3);
    printf("parent exitting\n");
    exit(EXIT_SUCCESS);
}
