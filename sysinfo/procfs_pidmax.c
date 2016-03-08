#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc,char *argv[])
{
    int fd;
    char line[MAX_LINE];
    ssize_t n;
    fd = open("/proc/sys/kernel/pid_max",(argc > 1)?O_RDWR:O_RDONLY);
    if(fd == -1) {
        perror("open procfs");
        exit(EXIT_FAILURE);
    }

    if(argc > 1)
        printf("old value:");
    printf("%.*s",(int)n,line);
    if(argc > 1) {
        if(write(fd,argv[1]),strlen(argv[1]) != strlen(argv[1])) {
            perror("write() failed");
            exit(EXIT_FAILURE);
        }

        system("echo /proc/sys/kernel/pid_max now contains " "`cat /proc/sys/kernel/pid_max`");
    }
}
