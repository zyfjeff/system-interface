#include <stdio.h>

/*
 *  空间局部性
 *  时间局部性
 *  访问局部性
 *
 *  sysconf(_SG_PAGESIZE) 获取系统虚拟内存的页面大小
 *  进程试图访问的地址并无页表条目与之对应，那么进程将收到一个SIGSEGV信号
 */
int main()
{

}
