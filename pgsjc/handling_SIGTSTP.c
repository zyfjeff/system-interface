#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

static void tstpHandler(int sig)
{
    sigset_t tstpMask,prevMask;
    int savedErrno;
    struct sigaction sa;
    savedErrno = errno;

    //捕捉到信号
    printf("Caught SIGTSTP\n");
    if(signal(SIGTSTP,SIG_DFL) == SIG_ERR) {
        perror("signal");
        exit(EXIT_FAILURE);
    }

    raise(SIGTSTP);
    sigemptyset(&tstpMask);
    sigaddset(&tstpMask,SIGTSTP);

    if(sigprocmask(SIG_UNBLOCK,&tstpMask,&prevMask) == -1) {
        perror("sigprocmask");
        exit(EXIT_FAILURE);
    }

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = tstpHandler;
    if(sigaction(SIGTSTP,&sa,NULL) == -1) {
        perror("sigprocmask");
        exit(EXIT_FAILURE);
    }
    printf("Exiting SIGTSTP handler\n");
    errno = savedErrno;
}

int main(int argc,char *argv[])
{
    struct sigaction sa;
    if(sigaction(SIGTSTP,NULL,&sa) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    if(sa.sa_handler != SIG_IGN) {
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = SA_RESTART;
        sa.sa_handler = tstpHandler;
        if(sigaction(SIGTSTP,&sa,NULL) == -1) {
            perror("sigaction");
            exit(EXIT_FAILURE);
        }
    }

    for(;;) {
        pause();
        printf("Main\n");
    }
}
