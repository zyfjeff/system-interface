#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
    int numSigs,sig,j;
    pid_t pid;

    pid = getpid();
    numSigs = 10;
    sig = SIGUSR1;
    printf("%s: sending signal %d to process %ld %d times\n",
            argv[0],sig,(long)pid,numSigs);
    for(j = 0;j < numSigs;++j) {
        if(kill(pid,sig) == -1) {
            perror("kill signal");
            exit(EXIT_FAILURE);
        }
    }

    printf("%s: exitting\n",argv[0]);
    exit(EXIT_SUCCESS);
}
