#include <sys/timerfd.h>
#include <time.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
    struct itimerspec ts;
    struct timespec start,now;
    int maxExp = 100,fd,secs,nanosecs;
    uint64_t numExp,totalExp;
    ssize_t s;
    ts.it_value.tv_sec = 1;
    ts.it_value.tv_nsec = 0;
    ts.it_interval.tv_sec = 1;
    ts.it_interval.tv_nsec = 0;

    //创建fd
    fd = timerfd_create(CLOCK_REALTIME,0);
    if(fd == -1) {
        perror("timerfd_create");
        exit(-1);
    }
    //设置间隔时间
    if(timerfd_settime(fd,0,&ts,NULL) == -1) {
        perror("timerfd_settime");
        exit(-1);
    }

    //获取时间
    if(clock_gettime(CLOCK_MONOTONIC,&start) == -1) {
        perror("clock gettime");
        exit(-1);
    }

    for(totalExp = 0; totalExp < maxExp;) {
        s = read(fd,&numExp,sizeof(uint64_t));
        if(s != sizeof(uint64_t)) {
            perror("read uint64_t");
            exit(-1);
        }
        //numExp 到期的次数
        totalExp += numExp;
        if(clock_gettime(CLOCK_MONOTONIC,&now) == -1) {
            perror("clock_gettime");
            exit(-1);
        }

        secs = now.tv_sec - start.tv_sec;
        nanosecs = now.tv_nsec - start.tv_nsec;
        if(nanosecs < 0) {
            secs--;
            nanosecs += 1000000000;
        }

        printf("%d.%03d: expirations read: %llu; total=%llu\n",
                secs,(nanosecs + 500000) / 1000000,
                (unsigned long long)numExp,(unsigned long long)totalExp);
    }
    exit(EXIT_SUCCESS);
}
