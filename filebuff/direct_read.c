#define _GNU_SOURCE
#include <fcntl.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>


int main(int argc,char *argv[])
{
    int fd;
    ssize_t length,alignment;
    off_t offset;
    void *buf;
    if(argc < 1 || strcmp(argv[1],"--help") == 0) {
        fprintf(stderr,"%s file length [offset [alignment]]\n",argv[0]);
        exit(EXIT_FAILURE);
    }

    length = 256;
    offset = 0;
    alignment = 4096;

    fd = open(argv[1],O_RDONLY|O_DIRECT);
    if(fd == -1) {
        perror("open fd");
        exit(EXIT_FAILURE);
    }

    //分配一个地址是alignment*2的整数倍,大小是length+alignment的内存块,
    //其中alignment *2 需要是的2的幂
    buf = (char*)memalign(alignment * 2,length + alignment) + alignment;
    if(buf == NULL) {
        perror("memalign");
        exit(EXIT_FAILURE);
    }

    if(lseek(fd,offset,SEEK_SET) == -1) {
        perror("lseek");
        exit(EXIT_FAILURE);
    }
    int numRead = read(fd,buf,length);
    if(numRead == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }
    printf("read %ld bytes\n",(long)numRead);
    exit(EXIT_SUCCESS);
}
