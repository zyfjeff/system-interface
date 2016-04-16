#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <time.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>

static volatile sig_atomic_t gotAlarm = 0;

static void displayTimes(const char *msg,bool includeTimer)
{
    struct itimerval itv;
    static struct timeval start;
    struct timeval curr;
    static int callNum = 0;

    if(callNum == 0) {
        if(gettimeofday(&start,NULL) == -1) {
            perror("gettimeofday");
            exit(EXIT_FAILURE);
        }
    }

    if(callNum % 20 == 0)
        printf("    Elapsed Value Interval\n");

    if(gettimeofday(&curr,NULL) == -1) {
        perror("gettimeofday");
        exit(EXIT_FAILURE);
    }

    printf("%-7s %6.2f",msg,curr.tv_sec - start.tv_sec + (curr.tv_usec - start.tv_usec) / 1000000.0);

    if(includeTimer) {
        if(getitimer(ITIMER_REAL,&itv) == -1) {
            perror("getitimer");
            exit(EXIT_FAILURE);
        }
        printf("    %6.2f  %6.2f",
                itv.it_value.tv_sec + itv.it_value.tv_usec / 1000000.0,
                itv.it_interval.tv_sec + itv.it_interval.tv_usec / 1000000.0);

    }

    printf("\n");
    ++callNum;
}

static void signalrmHandler(int sig)
{
    gotAlarm = 1;
}

itn main(int argc,char *argv[])
{
    struct itimerval itv;
    clock_t prevClock;
    int maxSigs;
    int sigCnt;
    struct sigaction sa;


}
