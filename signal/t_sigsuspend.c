#define _GNU_SOURCE
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include "signal_functions.h"

static volatile sig_atomic_t gotSigquit = 0;
static void handler(int sig)
{
    printf("Caught siganl %d (%s)\n",sig,strsignal(sig));
    if(sig == SIGQUIT)
        gotSigquit = 1;
}


int main(int argc,char *argv[])
{
    int loopNum;
    time_t startTime;
    sigset_t origMask,blockMask;
    struct sigaction sa;
    printSigMask(stdout,"Initial signal mask is:\n");

    sigemptyset(&blockMask);
    sigaddset(&blockMask,SIGINT);
    sigaddset(&blockMask,SIGQUIT);
    if(sigprocmask(SIG_BLOCK,&blockMask,&origMask) == -1) {
        perror("sigprocmask - SIG_BLOCK");
        exit(EXIT_FAILURE);
    }

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = handler;

    if(sigaction(SIGINT,&sa,NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    if(sigaction(SIGQUIT,&sa,NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    for(loopNum = 1; !gotSigquit;++loopNum) {
        printf("=== LOOP %d\n",loopNum);
        printSigMask(stdout,"Starting critical section,signal mask is:\n");
        for(startTime = time(NULL);time(NULL) < startTime + 4;)
            continue;

        printPendingSigs(stdout,
                         "Before sigsuspend() - pending signals:\n");
        if(sigsuspend(&origMask) == -1 && errno != EINTR) {
            perror("sigsuspend");
            exit(EXIT_FAILURE);
        }
    }

    if(sigprocmask(SIG_SETMASK,&origMask,NULL) == -1) {
        perror("sigprocmask - SIG_SETMASK");
        exit(EXIT_FAILURE);
    }

    printSigMask(stdout,"=== Exited loop\nRestored signal mask to:\n");
    exit(EXIT_SUCCESS);
}


