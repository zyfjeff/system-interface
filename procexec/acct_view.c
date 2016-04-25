#include <fcntl.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/acct.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define TIME_BUF_SIZE 100

//convert comp_t value into long long
static long long comptToLL(comp_t ct)
{
    const int EXP_SIZE = 3;
    const int MANTSSA_SIZE = 13;
    const int MANTSSA_MASK = (1 << MANTSSA_SIZE) - 1;
    long long mantissa,exp;
    mantissa = ct & MANTSSA_MASK;
    exp = (ct >> MANTSSA_SIZE) & ((1 << EXP_SIZE) -1);
    return mantissa << (exp * 3);
}

int main(int argc,char *argv[])
{
    int acctFile;
    struct acct ac;
    ssize_t numRead;
    char *s;
    char timeBuf[TIME_BUF_SIZE];
    struct tm *loc;
    time_t t;

    if(argc !=2 || strcmp(argv[1],"--help") == 0) {
        perror("argc!!!!!");
        exit(EXIT_FAILURE);
    }

    acctFile = open(argv[1],O_RDONLY);
    if(acctFile == -1) {
        perror("acctFile");
        exit(EXIT_FAILURE);
    }
    printf("command flag    term.   user    "
           " start time      CPU     elapsed\n");

    printf("                 status "
           "                         time    time\n");

    while((numRead = read(acctFile,&ac,sizeof(struct acct))) > 0) {
        if(numRead != sizeof(struct acct)) {
            fprintf(stderr,"partial read\n");
            exit(EXIT_FAILURE);
        }
        printf("%-8.8s  ",ac.ac_comm);
        printf("%c",(ac.ac_flag & AFORK) ? 'F' : '-');
        printf("%c",(ac.ac_flag & ASU) ? 'F' : '-');
        printf("%c",(ac.ac_flag & AXSIG) ? 'X' : '-');
        printf("%c",(ac.ac_flag & ACORE) ? 'C' : '-');
#ifdef __linux__
        printf("    %#6lx  ",(unsigned long)ac.ac_exitcode);
#else
        printf("    %#6lx  ",(unsigned long)ac.ac_stat);
#endif
        //s = userNameFromId(ac.ac_uid);
        printf("%-8.8s ",(s == NULL) ? "???" : "root");
        t = ac.ac_btime;
        loc = localtime(&t);
        if(loc == NULL) {
            printf("??? Unknown time??? ");
        } else {
            strftime(timeBuf,TIME_BUF_SIZE,"%Y-%m-%d %T ",loc);
            printf("%s ",timeBuf);
        }
        printf("\n");
    }

    if(numRead == -1) {
        perror("read\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
