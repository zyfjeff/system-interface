#include <signal.h>
typedef void (*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler);

/*
 *  经典的信号，非实时的信号，占用了前32个位置。后来引入的新信号都是针对实时进程的
 *  信号被阻塞的时候放在待决列表上，同一个信号被阻塞多次，只在待决列表中只放置一次，
 *
 *  SIGKILL信号无法阻塞，init进程是特例，内核会忽略发送给该进程的SIGKILL信号
 *
 *  struct sigaction  posix信号
 *  sigemptyset 清空信号集
 *  sigprocmask() 设置信号掩码
 *
 *  struct task_struct
 *  {
 *      .......
 *      struct signal_struct *signal;
 *      //设置信号处理程序,
 *      struct sighand_struct *sighand;
 *      //包含了进程屏蔽的信号集
 *      sigset_t blocked;
 *      //包含所有已经引发，仍然有待内核处理的信号
 *      struct sigpending pending;
 *      //可以为信号处理程序专门提供一个堆栈来运行信号处理程序，其堆栈的地址和长度就保存在这里
 *      unsigned long sas_ss_sp;
 *      size_t sas_ss_size;
 *      .......
 *  }
 *
 *  struct sighand_struct {
 *      atomic_t    count;          //保存了共享这个结构的进程数目
 *      struct k_sigaction action[_NSIG];   //指定了每个信号对应的sigaction结构，也就是信号的属性
 *  }
 *
 *  struct k_sigaction {
 *      struct sigaction sa;
 *  }
 *
 *  //存放信号,一位对应一个信号
 *  typedef struct {
 *      unsigned long sig[_SIG_WORDS];  //
 *  }sigset_t;
 *
 *  struct sigpending {
 *      struct list_head list; //链接所有的sigqueue
 *      sigset_t signal;       //记录所有的待处理的信号
 *  }
 *  //一个要处理的信号，包含了这个信号的携带的数据和引发这个信号的一些信息
 *  struct sigqueue {
 *      struct list_head list;
 *      siginfo_t info;
 *  }
 *
 *  kill一个信号其实就是判断发送信号的进程是否有cap，是否可以发送信号，如果可以就生成一个sigqueue，然后插入到sigpengd链表上
 *  如果信号发送成功，没有被阻塞，就可以用signal_wake_up唤醒进程，使得调度器可以选择该进程运行。但是到此为止还没有触发信号
 *  处理程序。
 *
 *  信号队列的处理是发生在每次从内核态切换到用户态的时候发生，
 *  核心态: do_signal->handle_signal
 *  用户态: 信号处理程序
 *  核心态: sys_sigreturn
 *  用户态: 程序继续执行
 *
 *
 *  引起内核为进程产生信号的各类事件如下:
 *  1.硬件发生了异常
 *  2.用户键入了能够产生信号的终端特殊字符
 *  3.发生了软件事件
 *
 *  信号分为两类:标准信号，用于内核向进程通知事件，另一组信号由实时信号构成
 *
 *  SIGABRT 中止进程
 *  SIGALRM 实时定时器过期
 *  SIGBUS  内存访问错误
*   SIGCHLD 终止或者停止子进程
*   SIGCLD
*   SIGCONT 若停止则继续
*   SIGEMT  硬件错误
*   SIGFPE  算术错误
*   SIGHUP  挂起
*   SIGILL  非法指令
*   SIGINFO
*   SIGINT  终端中断
*   SIGIO   I/O时可能产生
*   SIGKILL 必杀
*   SIGLOST
*   SIGPIPE 管道断开
*   SIGPOLL
*   SIGPROF 性能分析定时器过期
*   SIGPWR  电量将耗尽
*   SIGQUIT 终端退出
*   SIGSEGV 无效的内存引用
*   SIGSTKFLT   协处理器栈错误
*   SIGSTOP     确保停止
*   SIGSYS      无效的系统调用
*   SIGTERM     终止进程
*   SIGTRAP     跟踪/断点陷阱
*   SIGTSTP     终端停止
*   SIGTTIN     BG从终端读取
*   SIGTTOU     BG向终端写
*   SIGURG      套接字上的紧急数据
*   SIGUSR1
*   SIGUSR2
*   SIGVTALRM   虚拟定时器过期
*   SIGWINCH    终端窗口尺寸发生变化
*   SIGXCPU     突破对CPU时间的限制
*   SIGXFSZ     突破对文件大小的限制
*
*
*   改变信号处置: signal() 无法在不改变信号处理函数的同时，还能获取到当前的信号处理函数
*   信号处理函数，被typedef定义为sighandler_t，需要打开_GNU_SOURCE特性测试宏
*
*   kill检查进程存在:
*   kill系统调用的另一重功用，若将参数sig指定为0(既所谓的空信号),则无信号发送，则kill仅仅会执行错误检查
*   看看是否可以向目标进程发送信号，因此可以通过将sig设置为0来检查特定进程ID的进程是否存在，若信号发送失败
*   并且返回ESRCH，则目标进程不存在，如果返回EPERM，则是目标进程存在，但是无权向目标进程发送信号。
*
*   进程存在并不能保证特定程序仍然在运行，因为内核会循环使用进程的ID，一段时间后可能又是
*   除此之外还可以使用其他技术来检查某一特定的进程是否正在运行：
*   1.wait系统调用,仅能监控调用者的子进程
*   2.信号量和排他文件锁
*   3.管道,FIFO IPC
*   4./proc/PID
*
*   除了kill还有raise和killpg都可以发丝那个信号，
*   raise可以给自身发送信号
*   pthread_kill(pthread_self(),sig) 发送给特定线程
*
*   killpg 等同于 kill(-pgrp,sig); 向某一个进程组的所有成员发送一个信号
*
*   strsignal 等同于strerror 打印信号的描述，和打印错误码的描述
*   所有的信号描述否放在sys_siglist这样的一个全局数组中，需要开启_BSD_SOURCE和_GNU_SOURCE特性测试宏
*   psignal(int sig,const char *msg); 可以附加一段msg后面接冒号，然后是对应与sig的信号描述
*
*   信号集:
*       使用sigset_t数据类型来标志一个信号集，sigemptyset和sigfillset用于初始化信号集
*       sigaddset和sigdelset用于向信号集添加和删除一个信号 sigismember测试一个信号是否在指定信号集中
*   除此之外还有三个非标准函数，需要开启_GNU_SOURCE特性测试宏
*   sigandset 将left和right信号集的交集置于dest
*   sigorset  将let和right信号集的并集置于dest
*   sigisemptyset 若set集内没有包含信号，则sigisemptyset返回true
*
*   sigprocmask(int how,const sigset_t *set,sigset_t *oldset)　设置信号掩码
*   how的取值:
*       SIG_BLOCK   将set指向信号集内的信号添加到信号掩码中
*       SIG_UNBLOCK 将set指向信号集内的信号从信号掩码中移除
*       SIG_SETMASK 将set指向的信号集赋值给信号掩码
*
*   注: SIGKILL和SIGSTOP信号是不可能被阻塞的
*
*   sigpengding查看当前进程正在阻塞的信号
*
*   信号排队:
*       等待信号集只是一个掩码，仅仅表明一个信号是否发生，至于发生了多少次则没有表示
*       实时信号则会排队进行处理.
*
*   sigaction 改变信号默认处理程序
*
*   #include <signal.h>
*   int sigaction(int signum, const struct sigaction *act,
*                 struct sigaction *oldact);
*
*/
/*
           struct sigaction {
               void     (*sa_handler)(int);         //对应于signal的handler
               void     (*sa_sigaction)(int, siginfo_t *, void *);
               sigset_t   sa_mask;                  //设置信号掩码
               int        sa_flags;                 //内部使用
               void     (*sa_restorer)(void);
           };

    sa_flags:
        SA_NOCLDSTOP
        SA_NOCLDWAIT    若sig为SIGCHLD信号，则当子进程终止时不会将其转化为僵尸进程
        SA_NODEFER
        SA_ONSTACK
        SA_RESETHAND    自动重启信号处理器程序中断的系统调用
        SA_RESTART
        SA_SIGINFO      调用信号处理器程序时携带了额外参数

    pause　暂停进程的执行，直到信号处理器函数中断该调用为止
    总是返回-1，并将errno设置为EINTR

*/
int main()
{

}
