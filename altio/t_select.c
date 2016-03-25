#include <sys/time.h>
#include <sys/select.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

static void usageError(const char *progName)
{
    fprintf(stderr,"Usage: %s {timeout|-} fd-num[rw]...\n",progName);
    fprintf(stderr,"    - means infinite timeout; \n");
    fprintf(stderr,"    r = monitor for read\n");
    fprintf(stderr,"    w = monitor for write\n\n");
    fprintf(stderr,"    e.g.: %s - Orw 1w\n",progName);
    exit(EXIT_FAILURE);
}

int main(int argc,char *argv[])
{
    fd_set readfds,writefds;
    int ready,nfds,fd,numRead,j;
    struct timeval timeout;
    struct timeval *pto;
    char buf[10];

    if(argc < 2 || strcmp(argv[1],"--help") == 0)
        usageError(argv[0]);

    //设置超时时间
    if(strcmp(argv[1],"-") == 0) {
        pto = NULL;
    } else {
        pto = &timeout;
        timeout.tv_sec = 3;
        timeout.tv_usec = 0;
    }

    //保存最大fd+1
    nfds = 0;
    FD_ZERO(&readfds);
    FD_ZERO(&writefds);

    for(j = 2;j < argc;++j) {
        numRead = sscanf(argv[j],"%d%s[rw]",&fd,buf);
        if(numRead != 2)
            usageError(argv[0]);

        if(fd >= FD_SETSIZE) {
            fprintf(stderr,"file descriptor exceed limit (%d)\n",FD_SETSIZE);
            exit(EXIT_FAILURE);
        }

        if(fd >= nfds)
            nfds = fd + 1;

        if(strchr(buf,'r') != NULL)
            FD_SET(fd,&readfds);

        if(strchr(buf,'w') != NULL)
            FD_SET(fd,&writefds);
    }

    ready = select(nfds,&readfds,&writefds,NULL,pto);
    if(ready == -1) {
        perror("select");
        exit(EXIT_FAILURE);
    }
    //遍历每个fd,打印出是读还是写
    printf("ready = %d\n",ready);
    for(fd = 0;fd < nfds;++fd) {
        printf("%d: %s%s\n",fd,FD_ISSET(fd,&readfds)?"r":"",
                FD_ISSET(fd,&writefds)?"w":"");
    }
    //剩余时间
    if(pto != NULL)
        printf("timeout after select():%ld.%03ld\n",
                (long)timeout.tv_sec,(long)timeout.tv_usec / 10000);
    exit(EXIT_SUCCESS);
}


