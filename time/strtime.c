#define _XOPEN_SOURCE
#include <time.h>
#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define  SBUF_SIZE  1000

int main(int argc,char *argv[])
{
    struct tm tm;
    char sbuf[SBUF_SIZE];
    char *ofmt;

    if(argc < 3 || strcmp(argv[1],"--help") == 0) {
        printf("usage:%s input-date-time in-format [out-format]\n",argv[0]);
        exit(EXIT_FAILURE);
    }

    if(setlocale(LC_ALL,"") == NULL) {
        perror("setlocale");
        exit(EXIT_FAILURE);
    }

    memset(&tm,0,sizeof(struct tm));

    if(strptime(argv[1],argv[2],&tm) == NULL) {
        perror("strptime");
        exit(EXIT_FAILURE);
    }
    tm.tm_isdst = -1;
    printf("calendar time(seconds since Epoch): %ld\n",(long)mktime(&tm));
    ofmt = (argc > 3)? argv[3]: "%H:%M:%S %A, %d %B %Y %Z";
    if(strftime(sbuf,SBUF_SIZE,ofmt,&tm) == 0) {
        perror("strftime");
        exit(EXIT_FAILURE);
    }
    printf("strftime() yields: %s\n",sbuf);
    exit(EXIT_SUCCESS);
}

