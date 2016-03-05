#include <sys/time.h>

int gettimeofday(struct timeval *tv, struct timezone *tz);
int settimeofday(const struct timeval *tv, const struct timezone *tz);
int stime(const time_t *t);

/*
 *  settimeofday和stime都可以用来设置系统时钟,前者精度更高.
 *  无论是settimeofday,还是stime这两个调用所造成的那种系统时间突然变化,都会导致那些依赖于系统时钟单调
 *  递增的应用造成有害的影响,出于这个原因,通常推荐使用库函数adjtime()将系统时钟逐步调整到正确的时间
 *
 *  int adjtime(const struct timeval *delta, struct timeval *olddelta);
 *  根据delta的正负,每秒系统时间会额外拨快一点点,或者额外拨慢一点点,知道增加或者减少所需的时间.
 *  olddelta返回未调整的时间.
 *
 *  adjtime是根据linux上更通用和复杂的特定于linux的系统调用adjtimex来完成的
 *
 *  进程时间:
 *      分为用户态cpu时间,内核态cpu时间,
 *   clock_t times(struct tms *buf);
 *
 */

           struct tms {
               clock_t tms_utime;  // user time
               clock_t tms_stime;  // system time
               clock_t tms_cutime; // user time of children
               clock_t tms_cstime; // system time of children
           };
//tms_cutime 和tms_cstime指的是的,父进程执行了系统调用wait()的所有已经终止的子进程所使用的CPU时间

clock_t clock(void);
//clock也可以获取进程时间,无论是times还是clock都可以获取进程时间,返回的是clock_t,这是时钟计时单元,要转换为秒,还需要知道
//每秒是多少个计时单元,对于times来说,这个值是sysconf(_SC_CLK_TCK),对于clock来说这个值是CLOCKS_PER_SEC
//

int main()
{

}
