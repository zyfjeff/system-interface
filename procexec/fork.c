#include <stdio.h>

/*
 *  fork 写时复制机制，不保证父子进程谁先谁后，sleep也无法保证
 *  fork后父子进程共享文件描述符包括偏移量，文件打开标志位，属性位等，但是不共享close-on-exec
 *
 *  task_struct {
 *      .....
 *      struct files_struct-----> struct files_struct {
 *      .....                           .........
 *                                     struct fdtable fdtab; ------> struct fdtable {
 *                                                                      ........
 *                                      .........                       struct file **fd  //一个打开的文件在内存中就是一个file对象
 *                                                                                        //维护了文件打开偏移量和文件的状态信息等
 *                                                                      unsigned long *close_on_exec
 *                                                                      ........
 *
 *                                                                   }
 *                                  }
 *
 *  }
 *
 *  vfork的增强语义:
 *  1.父子进程共享内存，直到成功执行了exec或是调用了_exit退出
 *  2.在子进程调用exec或_exit之前，将暂停指向父进程
 *
 *  fork无法保证父子进程谁先谁后，
 *  /proc/sys/kernel/sched_child_runs_first 用于设置fork之后是否率先调度子进程
 *  利用信号阻塞和等待来进行父子进程同步，
 *  1.父进程对指定信号屏蔽，子进程运行结束后发送指定信号
 *  2.父进程等待指定信号达到。
 *
 */

int main()
{

}
