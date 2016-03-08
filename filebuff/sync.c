#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * synchronized I/O data integrity completion
 * synchronized file data integrity completion
 *
 * fdatasync和fsync 都是用来完成同步IO的,两者的差别在于,前者只同步数据,后者只同步元数据
 * sync系统调用会使包含更新文件信息的所有内核缓冲区(数据块,指针块,元数据等)
 * 但是其实现在的磁盘驱动器一般都会内置大型的告诉缓存,默认情况下sync只是将数据传递到这该缓存中
 *
 *  hdparm -W0 关闭磁盘的高速缓存特性
 *
 * 若内容发生了变化的内核缓冲区在30s内未经显示方式同步到磁盘上,则一条长期运行的内核线程会确保将其刷新到磁盘上
 * linux2.6版本中,该任务由pdflush内核线程执行.
 *
 *
 * proc/sys/vm/dirty_expire_centisecs 规定了间隔时间,多长时间刷新一次
 *
 * open系统调用提供了O_SYNC O_DSYNC 来控制IO,前者等同于sync,后者等同于fdatasync
 */

       int fsync(int fd);
       int fdatasync(int fd);
       void sync(void);
       int syncfs(int fd);

int main()
{

}
