#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>

int main()
{
    int fd = 1;
    int cnt = 0;
    char buf[BUFSIZ] = {0};
    TEMP_FAILURE_RETRY(cnt = read(fd,buf,BUFSIZ));
}
