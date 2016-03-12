#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>



/*
 * 就IO模式向内核提出建议
 * int posix_fadvise(int fd, off_t offset, off_t len, int advice);
 *
 * advice:
 *  POSIX_FADV_NORMAL   进程对访问模式并无特别建议,默认行为,预读窗口大小为128KB
 *  POSIX_FADV_RANDOM   进程预计以随机顺序访问数据
 *  POSIX_FADV_WILLNEED 进程预计会在不久的将来访问指定的文件区域,内核将预先加载offset和len指定的区域,填充到缓冲区高速缓存中
 *  POSIX_FADV_DONTNEED 进程预计在不久的将来不会访问指定的文件区域,内核会释放相关的高速缓存内容
 *  POSIX_FADV_NOREUSE  进程预计会一次性地访问指定文件区域,不再复用,
 *                          这等于提示内核对指定区域访问一次即可释放页面(linux中目前不起作用)
 *
 *      #define _GNU_SOURCE
 *      #include <fcntl.h>
 *      ssize_t readahead(int fd, off64_t offset, size_t count);
 *      内核会将fd对应的文件,偏移量offset处,count大小的区域先填充到缓冲区高速缓存中,后续对该文件的read调用
 *      将不会阻塞磁盘I/O
 *
 * 绕过缓冲区高速缓存: 直接I/O 在open的时候指定O_DIRECT标志来打开文件
 * 直接I/O的对齐限制:
 * 1.用于传递数据的缓冲区,其内存边界必须对齐为块大小的整数倍
 * 2.数据传输的开始点,也就是文件和设备的偏移量,必须是块大小的整数倍
 * 3.待传递数据的长度必须是块大小的整数倍
 *
 * 不遵守上面的限制会导致EINVAL错误
 */
int main()
{

}
