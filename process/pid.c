#include <stdio.h>

/*  linux2.4 PID上限32767　通过内核常量PID_MAX来控制
 *  linux2.6 上限还是32767，但是可以通过/proc/sys/kernel/pid_max来调整
 *  一旦进程号达到最大，会将进程号计数器重置为300，然后继续分配未使用的进程号，因为1~300的进程和守护进程长期占用
 *  所以在1~300范围中搜索未使用的PID是浪费时间
 *
 *
 *
 */
int main()
{

}
