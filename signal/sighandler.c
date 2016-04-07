#include <signal.h>

/*
 *  signal handler函数
 *  一般而言将信号处理函数设计的越简单越好，其中的一个重要原因在于，降低引发竞争条件的风险
 *  下面是针对信号处理函数的两种常见设计:
 *
 *  1.信号处理函数设置全局性标志变量并退出,主程序对此标志进行周期性检查。
 *  2.信号处理器函数指向某种类型的清理操作，接着终止进程或者使用非本地跳转将栈解开，然后返回到主程序的预定位置
 *
 *  可重入函数和异步信号安全函数:
 *
 *  volatile 避免编译器优化，直接从内存读取其值
 *  sig_atomic_t 保证读写操作的原子性
 *  SIG_ATOMIC_MIN SIG_ATOMIC_MAX 用于规定可赋给sig_atomic_t类型的值范围
 *  对sig_atomic_t类型的变量进行++和--是不保证原子性的。通常设置全局的sig_atomic_t变量，作为标志
 *  信号处理器函数去修改这个标志，主程序检测这个标志。
 *
 *  信号处理函数进行终止:
 *  1.不要调用exit，这是非安全的，会刷新stdio缓冲区,而是去调用_exit
 *  2.使用kill发送信号杀掉进程
 *  3.指向非本地跳转
 *  4.使用abort函数终止进程，并产生核心转储
 *
 *  在信号处理函数中调用setjmp和longjmp的时候，如果有屏蔽的信号，那么执行完setjmp和longjmp后，屏蔽的信号会继续屏蔽会保留
 *  屏蔽的信号信息。
 *
 *  sigsetjmp siglongjmp　可以定制非本地跳转后信号屏蔽情况，可以保存，也可以不保存
 *
 *  异常终止进程 abort()
 *  abort通过产生SIGABRT信号来终止调用进程，SIGABRT默认动作是产生核心转储文件并终止进程
 *  无论阻塞还是忽略SIGABRT信号，abort调用都不受影响，同时规定除非进程捕获SIGABRT信号后信号处理器函数尚未返回，否则
 *  abort必须终止进程。在信号处理函数中使用setjmp和longjmp进行非本地跳转可以抵消abort的效果。
 *
 *
 *
 *  备选栈中处理信号:
 *      可以让信号处理函数运行在自定义的备选栈中
 *      1.分配一块被称为备选信号栈的内存区域，作为信号处理器函数的栈幁
 *      2.调用sigaltsatck告之内置该备选信号栈的存在
 *      3.创建信号处理器函数时指定SA_ONSTACK标志，也就是通知内核在备选栈上为处理器函数创建栈幁
 *
 *
 *  #include <signal.h>
 *  int sigaltstack(const stack_t *ss, stack_t *oss);
 *
 */

           typedef struct {
               void  *ss_sp;     /* Base address of stack */
               int    ss_flags;  /* Flags */
               size_t ss_size;   /* Number of bytes in stack */
           } stack_t;
/*
 *  ss_sp指定了备选栈的地址起始地址
 *  ss_size　指定了备选栈的大小
 *  ss_flags SS_ONSTACK SS_DISABLE  指定一些标志
 *
 *  备选栈可以是堆上内存，也可以是静态分配 SIGSTKSZ 为备选栈大小的典型值
 *  ss_flags:
 *      SS_ONSTACK  表明进程正在备选信号栈上运行，如果再试图创建一个新的备选信号栈，会产生一个EPERM错误
 *      SS_DISABLE  表示当前不存在已创建的备选信号栈
 *
 * sigaction指定SA_SIGINFO标志的时候，可以在接收信号的时候获取到该信号的一些附加信息
 * 指定SA_SIGINFO标志后，新的信号处理函数其原型如下:
 * void handler(int sig,siginfo_t *siginfo,void *ucontext);
 */

           siginfo_t {
               int      si_signo;    /* Signal number */
               int      si_errno;    /* An errno value */
               int      si_code;     /* Signal code */
               int      si_trapno;   /* Trap number that caused
                                        hardware-generated signal
                                        (unused on most architectures) */
               pid_t    si_pid;      /* Sending process ID */
               uid_t    si_uid;      /* Real user ID of sending process */
               int      si_status;   /* Exit value or signal */
               clock_t  si_utime;    /* User time consumed */
               clock_t  si_stime;    /* System time consumed */
               sigval_t si_value;    /* Signal value */
               int      si_int;      /* POSIX.1b signal */
               void    *si_ptr;      /* POSIX.1b signal */
               int      si_overrun;  /* Timer overrun count; POSIX.1b timers */
               int      si_timerid;  /* Timer ID; POSIX.1b timers */
               void    *si_addr;     /* Memory location which caused fault */
               long     si_band;     /* Band event (was int in
                                        glibc 2.3.2 and earlier) */
               int      si_fd;       /* File descriptor */
               short    si_addr_lsb; /* Least significant bit of address
                                        (since Linux 2.6.32) */
           }


/*
 *  GNU C提供了一个非标准的宏 TEMP_FAILURE_RETRY 需要定义特性测试宏 _GNU_SOURCE
 *  可用于重启系统调用
 *  等同于 #define NO_EINTR(stmt) while(((stmt) == -1 && errno == EINTR);
 *
 *  还可以使用sigaction中的SA_RESTART重启标志，但是并不是每一个阻塞的系统调用都支持这个标志
 */

