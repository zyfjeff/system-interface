#include <signal.h>
#include <stdio.h>

void handler(int sig)
{
    printf("Receive signal: %u\n",sig);
}

int main()
{
    struct sigaction sa;
    int count;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGTERM,&sa,&sa.sa_mask);
    sigprocmask(&sa.sa_mask);
    while(1) {
        sigsuspend(&sa.sa_mask);
        printf("loop \n");
    }
    return 0;
}
