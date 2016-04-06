#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc,char *argv[])
{
    int s,sig;
    //if(argc != 1 || strcmp(argv[1],"--help") == 0)
    //    fprintf(stderr,"%s sig-num pid \n",argv[0]);
    sig = SIGKILL;
    s = kill(getpid(),sig);
    if(sig != 0) {
        if(s == -1) {
            perror("kill");
            exit(EXIT_FAILURE);
        }else {
            if(s == 0) {
                printf("Process exists and we can send it a signal\n");
            }
        }
    } else {
        if(errno == EPERM)
            printf("process exists,but we don't have permission to send it a signal\n");
        else if(errno == ESRCH)
            printf("Process does not exists\n");
        else {
            perror("kill");
            exit(EXIT_FAILURE);
        }
    }
    exit(EXIT_SUCCESS);
}
