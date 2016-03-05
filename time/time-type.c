#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

/*
 *  时间类型:
 *
 *      真实时间:
 *          日历时间(起点是某个标准点),clock时间(起点是进程生命周期内的某个固定点)
 *      进程时间:
 *          一个进程所使用的CPU时间总量,适用于对程序,算法性能的检查和优化
 *
 *  日历时间:
 *      来自于以Epoch以来的秒数来度量,Epoch也就是通用协调时间(UTC 以前也成为格林威治标准时间 或GMT)
 *      日历时间存储为time_t的变量,32位系统每time_t是一个有符号整数,能表示到2038年
 *
 *  int gettimeofday(struct timeval *tv, struct timezone *tz); //tz已经被废弃,设置为NULL即可
 *  int settimeofday(const struct timeval *tv, const struct timezone *tz);
 *  time_t time(time_t *t);
 *
 *  同时存在上面两个函数存在历史原因,gettimeofday更为精确.time是利用gettimeofday实现的一个库函数
 */

/*
struct timeval {
        time_t      tv_sec;
        suseconds_t tv_usec;
};

*/

int main()
{

}
