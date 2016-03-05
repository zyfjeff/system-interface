#include <sys/times.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void displayProcessTimes(const char *msg)
{
    struct tms t;
    clock_t clockTime;
    static long clockTicks = 0;
    if(msg != NULL)
        printf("%s",msg);

    if(clockTicks == 0) {
        clockTicks = sysconf(_SC_CLK_TCK);
        if(clockTicks == -1) {
            perror("sysconf");
            exit(EXIT_FAILURE);
        }
    }
    clockTime = clock();
    if(clockTime == -1) {
        perror("clock");
        exit(EXIT_FAILURE);
    }

    printf("    clock() returns: %ld clocks-per-sec (%.2f secs)\n",
            (long)clockTime,(double)clockTime/CLOCKS_PER_SEC);

    if(time(&t) == -1) {
        perror("times");
        exit(EXIT_FAILURE);
    }
    printf("    times() yields: user CPU=%.2f; system CPU: %.2f\n",
            (double)t.tms_utime /clockTicks,
            (double)t.tms_stime /clockTicks);
}

int main(int argc,char *argv[])
{
    int numCalls,j;
    printf("CLOCKS_PER_SEC=%ld sysconf(_SC_CLK_TCK)=%ld\n\n",(long)CLOCKS_PER_SEC,sysconf(_SC_CLK_TCK));
    displayProcessTimes("At program start:\n");
    numCalls = (argc > 1)?
}


