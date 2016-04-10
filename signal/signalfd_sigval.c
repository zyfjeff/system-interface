#include <sys/signalfd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
    sigset_t mask;
    int sfd,j;
    struct signalfd_siginfo fdsi;
    ssize_t s;

    if(argc < 2 || strcmp(argv[1],"--help") == 0) {
        fprintf(stderr,"%s sig-num.....\n",argv[0]);
        exit(EXIT_FAILURE);
    }

    printf("%s: PID= %ld\n",argv[0],(long)getpid());
}
