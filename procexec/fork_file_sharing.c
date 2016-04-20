#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
    int fd,flags;
    char template[] = "/tmp/testXXXXXX";
    setbuf(stdout,NULL);
    fd = mkstemp(template);

    if(fd == -1) {
        perror("mkstemp");
        exit(EXIT_FAILURE);
    }

    printf("File offset before fork():% lld\n",
            (long long)lseek(fd,0,SEEK_CUR));

    flags = fcntl(fd,F_GETFL);
    if(flags == -1) {
        perror("fcntl");
        exit(EXIT_FAILURE);
    }
    printf("O_APPEND flag before fork() is: %s\n",
            (flags & O_APPEND)? "ON" : "off");
    switch(fork()) {
    case -1:
        perror("fork");
        exit(EXIT_FAILURE);
    case 0:
        //子进程修改偏移量和文件打开状态表示位
        if(lseek(fd,1000,SEEK_SET) == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        flags = fcntl(fd,F_GETFL);
        if(flags == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        flags |= O_APPEND;
        if(fcntl(fd,F_SETFL,flags) == -1) {
            perror("fcntl - F_SETFL");
            exit(EXIT_FAILURE);
        }
        _exit(EXIT_SUCCESS);

    default:
        if(wait(NULL) == -1) {
            perror("fcntl - F_SETFL");
            exit(EXIT_FAILURE);
        }
        printf("Child has exited\n");
        printf("File offset in parent: %lld\n",
                (long long)lseek(fd,0,SEEK_CUR));
        flags = fcntl(fd,F_GETFL);
        if(flags == -1) {
            perror("fcntl - F_SETFL");
            exit(EXIT_FAILURE);
        }
        printf("O_APPEND flag in parent is: %s\n",
                (flags & O_APPEND)? "on" : "off");
        exit(EXIT_SUCCESS);
    }
}
