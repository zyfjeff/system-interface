#define _GNU_SOURCE
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static void sigsegvHandler(int sig)
{
    int x;
    printf("Caught signal %d (%s)\n",sig,strsignal(sig));
    printf("Top of handler stack near   %10p\n",(void*)&x);
    fflush(NULL);
    _exit(EXIT_FAILURE);
}

static void overflowStack(int callNum)
{
    char a[100000];
    printf("Call %4d - top of stack near %10p\n",callNum,&a[0]);
    overflowStack(callNum + 1);
}

int main(int argc,char *argv[])
{
    stack_t sigstack;
    struct sigaction sa;
    int j;

    printf("Top of standard stack is near %10p\n",(void *)&j);
    sigstack.ss_sp = malloc(SIGSTKSZ);
    if(sigstack.ss_sp == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    sigstack.ss_size = SIGSTKSZ;
    sigstack.ss_flags = 0;
    if(sigaltstack(&sigstack,NULL) == -1) {
        perror("sigalstack");
        exit(EXIT_FAILURE);
    }
    printf("Alternate stack is at   %10p-%p\n",
            sigstack.ss_sp,(char*)sbrk(0) - 1);
    sa.sa_handler = sigsegvHandler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_ONSTACK;
    if(sigaction(SIGSEGV,&sa,NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
    overflowStack(1);
}
