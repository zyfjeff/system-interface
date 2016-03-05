#include <time.h>

/*
 *  ctime 将time_t类型的数据转换为可读字符串,这个字符串是经由静态分配的,下一次ctime的调用会将其覆盖
 *  SUSv3规定: ctime gmtime localtime asctime中的任何一个函数,都可能会覆盖由其他函数返回,且静态分配的数据结构
 *  这些函数可以共享返回的字符数组和tm结构体.某些版本的glibc也正是这样实现的.如果想对这些函数多次调用,那么必须
 *  将其保存在本地副本.
 *
 *
 * time_t转换为可读字符串
 *  char *ctime(const time_t *timep);
 *  char *ctime_r(const time_t *timep, char *buf);
 *
 * time_t转换为可分解的时间结构体
 *
 *  struct tm *gmtime(const time_t *timep);
 *  struct tm *gmtime_r(const time_t *timep, struct tm *result);
 *
 *  //会考虑失去和夏令时设置
 *  struct tm *localtime(const time_t *timep);
 *  struct tm *localtime_r(const time_t *timep, struct tm *result);
 *
 * 可分解的时间结构体,转换为time_t
 *   time_t mktime(struct tm *tm);
 *  mktime会可能会修改tm所指向的结构体,还会调整tm结构中字段的值范围,如果不在范围内,mktime会将其调整到范围内的
 *
 * 可分解的时间结构体,转换为可打印格式字符串
 *  char *asctime(const struct tm *tm);
 *  char *asctime_r(const struct tm *tm, char *buf);
 * 和ctime一样,asctime也无法控制可打印格式字符串的格式
 *
 *
 * 可分解的时间结构体,转换为可格式化打印格式的字符串
 *  size_t strftime(char *s, size_t max, const char *format,
 *                                const struct tm *tm);
 *  strftime不会再字符串的结尾包括换行符,除非(format中定义了换行符)
 *
 */

/*
           struct tm {
               int tm_sec;    // Seconds (0-60)
               int tm_min;    // Minutes (0-59)
               int tm_hour;   // Hours (0-23)
               int tm_mday;   // Day of the month (1-31)
               int tm_mon;    // Month (0-11)
               int tm_year;   // Year - 1900
               int tm_wday;   // Day of the week (0-6, Sunday = 0)
               int tm_yday;   // Day in the year (0-365, 1 Jan = 0)
               int tm_isdst;  // Daylight saving time
           };
*/

