#include <stdio.h>


/*
 *  stat() lstat() fstat() 获取和文件相关的信息
 *  lstat可以获取符号链接本身的属性信息,而不是其指向的文件的属性信息这是和stat的区别
 *
 *  设备id:
 *      stat()的返回结果中st_ino字段包含了文件的i节点号,st_dev字段标识了文件所驻留的设备.利用以上两者可在所有
 *      文件系统中唯一标识某个文件,dev_t类型记录了设备的主和辅ID
 *      利用宏major和minor可提取dev_t值的主 辅ID
 *
 *  stat的返回结果中的st_mode字段,用来检查文件类型的宏
 *
 *  S_IFREG     S_ISREG()       常规文件
 *  S_IFDIR     S_ISDIR()       目录
 *  S_IFCHR     S_ISCHR()       字符设备
 *  S_IFBLK     S_ISBLK()       块设备
 *  S_IFIFO     S_ISFIFO()      FIFO或管道
 *  S_IFSOCK    S_ISSOCK()      套接字
 *  S_IFLNK     S_ISLNK()       符号链接
 *
 *  测试文件类型:
 *      (st_mode & S_IFMT) == S_IFREG 来判断文件类型,要先和S_IFMT相于
 *
 *  df -k 查看分配给文件的实际空间
 *  st_blocks  字段记录了实际分配给文件的磁盘块数量,如果有文件内含空洞,那么该值小于相应文件字节数字段的值
 *  st_blksize 字段所指并非底层文件系统的块大小,而是针对文件系统上文件进行io操作时的最优块大小
 *
 */


#include <sys/types.h>
#include <utime.h>
/*
 *	修改文件的access time 和moodification time
 *	times如果为NULL,那么就更新文件的时间为当前时间
 *
 *  utimes相比与utime来说提供了微妙级精度来指定时间值结构
 *
 */
           struct utimbuf {
               time_t actime;       /* access time */
               time_t modtime;      /* modification time */
           };

int utime(const char *filename, const struct utimbuf *times);
#include <sys/time.h>
int utimes(const char *filename, const struct timeval times[2]);

/* futimes传入的是fd,而不是filename,lutimes和utimes的区别就在于如果filename是符号链接
 * 那么utimes更新的是符号链接指向的文件的时间戳,而lutimes则是更新的符号链接本身的时间戳
 */
int futimes(int fd, const struct timeval tv[2]);
int lutimes(const char *filename, const struct timeval tv[2]);



/*
 *  也是用来更改文件的时间戳,但是提供了纳秒级的时间戳改变
 *  并且支持独立设自某一个时间戳,而不是先stat获取时间戳,然后设置其中一个,更新另外一个
 *  下面这两个系统调用自身就支持单独设置时间戳
 *
 *  对于utimensat系统调用来说,使用方法如下:
 *  当dirfd为AT_FDCWD的时候,pathname可以是文件路径,也可以是fd
 *  times数组就是两个要更改的时间戳如果想把某一个时间设置为当前时间就把times对应的那个timespec结构体中的
 *  tv_nsec设置为UTIME_NOW,那么这个时间就会被更新为当前时间,如果想忽略某个时间不设置则只需要把对应的结构体
 *  中的tv_nsec设置为UTIME_OMIT即可,最后的那个flags是用来控制对于符号链接的行为,如果为0或者AT_SYMLINK_NOFOLLOOW,
 *  意思就是当pathname为符号链接的时候不会对其解引用.
 *
 */

struct timespec {
   time_t tv_sec;        /* seconds */
   long   tv_nsec;       /* nanoseconds */
};

#include <fcntl.h> /* Definition of AT_* constants */
#include <sys/stat.h>
int utimensat(int dirfd, const char *pathname,
                const struct timespec times[2], int flags);
int futimens(int fd, const struct timespec times[2]);

