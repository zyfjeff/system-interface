#include <iostream>

/*
 *  //设置间隔定时器
 *  #include <sys/time.h>
 *  int getitimer(int which, struct itimerval *curr_value);
 *  int setitimer(int which, const struct itimerval *new_value,
 *                struct itimerval *old_value);
 *
 * which:
 *  ITIMER_REAL 创建以真实时间倒计时的定时器，到期时会产生SIGALARM信号并发送给进程
 *  ITIMER_VIRTUAL 创建以进程虚拟时间(用户模式下的CPU时间)倒计时的定时器,到期会产生SIGVTALRM
 *  ITIMER_PROF 创建一个profiling定时器 以进程时间倒计时，到期时，则会产生SIGPROF信号
 *
 *
 *  #include <unistd.h>
 *  unsigned int alarm(unsigned int seconds);
 *
 *  alarm(0) 屏蔽现有的定时器,精度是秒，到期后会向调用进程发送SIGALARM信号
 *  alarm和setitimer针对同一个进程共享同一个实时定时器，无论调用两者之中哪个都可以改变定时器的设置
 *
 *  clock_getres 判断是否支持高分辨率定时器
 *
 *  超时read:
 *      1.调用sigaction设置SIGALARM信号处理器函数，排除SA_RESTART标志
 *      2.调用alarm或setitimer创建一个定时器
 *      3.执行阻塞系统调用
 *      4.检查系统调用失败时是否设置errno为RINTR
 *
 *
 * 休眠:
 *  sleep(对nanosleep的调用)
 *  nanosleep 没有用信号实现这个函数，和alarm setitimer混用是可以的，可以被信号中断
 *
 * POSIX时钟:
 *  clock_gettime 返回时钟当前值
 *  clock_getres  返回时钟分辨
 *  clock_settime 更新时钟
 *
 * clockid_t:
 *  CLOCK_REALTIME              可设定的系统级实时时钟,用于度量真实时间。
 *  CLOCK_MONOTONIC             不可设定的恒定态时钟
 *  CLOCK_PROCESS_CPUTIME_ID    每进程CPU时间的时钟
 *  CLOCK_THREAD_CPUTIME_ID     每线程CPU时间的时钟
 *
 *
 *　测量特定进程或线程所消耗的CPU时间:
 *
 * clock_getcpuclockid，返回调用进程的CPU时间时钟ID，然后使用clock_gettime获取时间
 * clock_nanosleep
 *
 *
 */


#include <time.h>
int clock_getres(clockid_t clk_id, struct timespec *res);
int clock_gettime(clockid_t clk_id, struct timespec *tp);
int clock_settime(clockid_t clk_id, const struct timespec *tp);
int clock_getcpuclockid(pid_t pid, clockid_t *clock_id);
#include <pthread.h>
#include <time.h>
int pthread_getcpuclockid(pthread_t thread, clockid_t *clock_id);

Link with -lrt (only for glibc versions before 2.17).


//设置间隔时间的
//1.只能设置ITIMER_REAL ITIMER_VIRTUAL ITIMER_PROF 这三类定时器，每种只能设置一个
//2.只能通过发送信号的方式来通知定时器到期,并且不能改变到期产生的信号
//3.间隔定时器到期多次，相应信号遭到阻塞时，只会调用一次信号处理函数
//4.定时器的分辨率只能呢过达到微妙级
//
/*
 *  POSIX定时器:
 *  1.以系统调用timer_create创建一个新的定时器，并定义其到期时对进程的通知方法
 *  2.以系统调用timer_settime启动或停止一个定时器
 *  3.以系统调用timer_delete删除不再需要的定时器
 *
 *  由fork创建的子进程不会继承POSIX定时器，调用exec期间，亦或进程终止时将停止并删除定时器
 *
 */
           struct itimerval {
               struct timeval it_interval; /* Interval for periodic timer */
               struct timeval it_value;    /* Time until next expiration */
           };

           struct timeval {
               time_t      tv_sec;         /* seconds */
                      suseconds_t tv_usec;        /* microseconds */
           };


/*  利用文件描述符进行通知的定时器 timerfd API
 *  可以从文件描述符中读取所创建定时器的到期通知，因此可以使用select poll还有epoll将这种文件描述符
 *  同其他描述符一同进行监控，所以非常有用。
 *
 *  timerfd_create
 *  timerfd_settimer
 *  timerfd_gettime
 *
 */

int main()
{

}
