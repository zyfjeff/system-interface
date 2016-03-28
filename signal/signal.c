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
 *  SIGABRT
 *  SIGALRM
 *  SIGBUS
*   SIGCHLD
*   SIGCLD
*   SIGCONT
*   SIGEMT
*   SIGFPE
*   SIGHUP
*   SIGILL
*   SIGINFO
*   SIGINT
*   SIGIO
*   SIGKILL
*   SIGLOST
*   SIGPIPE
*   SIGPOLL
*   SIGPROF
*   SIGPWR
*   SIGQUIT
*   SIGSEGV
*   SIGSTKFLT
*   SIGSTOP
*   SIGSYS
*   SIGTERM
*
*
*   改变信号处置: signal()
 */

int main()
{

}
