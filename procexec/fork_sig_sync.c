#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#define SYNC_SIG SIGUSR1

static void handler(int sig) {

}

int main(int argc,char *argv[]) {
    pid_t childPid;
    sigset_t blockMask,origMask,emptyMask;
    struct sigaction sa;
    setbuf(stdout,NULL);    //disable buffering of stdout

    sigemptyset(&blockMask);
    sigaddset(&blockMask,SYNC_SIG); //Block signal
    if(sigprocmask(SIG_BLOCK,&blockMask,&origMask) == -1) {
        perror("sigprocmask");
        exit(EXIT_FAILURE);
    }
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = handler;
    if(sigaction(SYNC_SIG,&sa,NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    switch(childPid = fork()) {
    case -1:
        perror("sigaction");
        exit(EXIT_FAILURE);
    case 0:
        printf("[%ld] Child started - doing some work\n",(long)getpid());
        sleep(2);
        printf("[%ld] Child doned - doing some work\n",(long)getpid());
        if(kill(getppid(),SYNC_SIG) == -1) {
            perror("sigaction");
            exit(EXIT_FAILURE);
        }
        _exit(EXIT_SUCCESS);
    default:    /* parent */
        printf("[%ld] Parent about to wait for signal\n",(long)getpid());
        sigemptyset(&emptyMask);
        if(sigsuspend(&emptyMask) == -1 && errno != EINTR) {
            perror("sigaction");
            exit(EXIT_FAILURE);
        }
        printf("[%ld] Parent got signal\n",(long)getpid());
        if(sigprocmask(SIG_SETMASK,&origMask,NULL) == -1) {
            perror("sigaction");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }
}
