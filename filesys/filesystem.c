#include <stdio.h>

/*
 *  虚拟内存文件系统tmpfs,该文件系统不但使用RAM,而且在RAM耗尽的情况下,还会利用交换空间.
 *  tmpfs可以用于挂载一些目录,让这些目录上的数据存放在内存中,使的使用这个目录的程序运行速度得以提升
 *  除此之外tmpfs还有另外两个用途:
 *      1.实现system v共享内存和共享匿名内存映射
 *      2.挂载于/dev/shm的tmpfs文件系统,为glibc用以实现POSIX共享内存和POSIX信号量
 *      tmpfs可以用于挂载一些目录,让这些目录上的数据存放在内存中,使的使用这个目录的程序运行速度得以提升
 *
 * #include <sys/statvfs.h>
 *
 * int statvfs(const char *path, struct statvfs *buf);
 * int fstatvfs(int fd, struct statvfs *buf);
 *
 */



int main()
{

}
