#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
    if(fork() != 0)
        _exit(EXIT_SUCCESS);

    if(setsid() == -1) {
        perror("setsid error");
        exit(EXIT_FAILURE);
    }

    printf("PPID=%ld PID=%ld,PGID=%ld,SID=%ld\n",(long)getppid(),(long)getpid(),
            (long)getpgrp(),(long)getsid(0));

    if(open("/dev/tty",O_RDWR) == -1) {
        perror("open /dev/tty");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
