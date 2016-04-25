#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>


//和fork不同，close转而去调用fn所指的函数,arg是函数的参数，因为可能产生的子进程可能是共享父进程
//的内存，所以它不能使用父进程的栈，相反调用者必须分配一块大小适中的内存空间供子进程的栈使用
//flags双重目的，低字节存放子进程的终止信号，子进程退出时父进程将收到这个信号，如果子进程因为信号
//而终止，那么父进程依然会收到SIGCHLD信号.flags的剩余位存放位掩码，用于控制clone的操作
//
//CLONE_CHILD_CLEARTID  子进程调用exec或_exit时，清楚tid
//CLONE_CHILD_SETTID    子进程的线程ID写入ctid
//CLONE_FILES   父子进程共享打开文件描述符表
//CLONE_FS      父子进程共享文件系统相关的属性
//CLONE_IO      子进程共享父进程的I/O上下文环境
//CLONE_NEWIPC  子进程获得新的System V IPC命名空间
//CLONE_NEWNET  子进程获得新的网络命名空间
//.....
//
       int clone(int (*fn)(void *), void *child_stack,
                 int flags, void *arg, ...
                 /* pid_t *ptid, struct user_desc *tls, pid_t *ctid */ );

       /* Prototype for the raw system call */

       long clone(unsigned long flags, void *child_stack,
                 void *ptid, void *ctid,
                 struct pt_regs *regs);

/*
 *  线程组中的所有线程拥有同一个父进程ID，即与线程组首线程ID相同
 *  如果一个线程组中的任一线程调用exec，那么除了首线程之外的其他线程都会终止，新进程将在首线程中指向
 *  换言之新程序中的gettid调用将返回首线程的线程ID，
 *
 *  如果线程组中的某个线程调用fork或vfork创建了子进程，那么组中的任何线程都可以使用wait或类似函数来监控子进程
 *
 *  CLONE_FILES　父子进程共享打开文件描述符表
 *  CLONE_FS 父子进程共享文件系统相关的信息，比如权限掩码，根目录，当前工作目录等
 *  CLONE_SIGHAND   父子进程共享同一个信号处置表
 *  CLONE_VM 共享父进程的虚拟内存
 *  CLONE_NEWNS 共父子进程拥有各自的挂载命名空间
 *  CLONE_PARENT 父子进程共享调用者的父进程
 *  CLONE_PTRACE和CLONE_UNTRACED 进程跟踪
 *  CLONE_IO CLONE_NEWIPC CLONE_NEWNET CLONE_NEWPID CLONE_NEWUSR CLONE_NEWUTS 提供容器支持的新标志
 *
 */

int main()
{

}
