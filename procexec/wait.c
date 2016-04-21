#include <sys/types.h>
#include <sys/wait.h>


/*
 *  while((childPid = wait(NULL)) != -1)
 *      continue;
 *  if(errno != ECHILD) {   // An unexpected error.....
 *      perror("wait");
 *      exit(EXIT_FAILURE);
 *  }
 *  wait的诸多限制:
 *  1.wiat无法等待特定子进程的完成
 *  2.如果没有子进程退出，wait总是保持阻塞
 *  3.wait只能发现那些已经终止的子进程，对于子进程因某些信号而停止，或是已经停止的子进程收到SIGCONT信号后恢复执行的
 *  情况就无能为力了。
 *
 * waitpid:
 *  WUNTRACED   除了返回终止子进程的信息外，还返回因信号而停止的子进程信息
 *  WCONTINUED  返回那些因收到SIGCONT信号而恢复执行的已停止子进程的状态信息
 *  WNOHANG 非阻塞
 *
 *  当通过ptrace追踪一个子进程时，那么除了SIGKILL信号之外，任何信号都会造成子进程停止
 *
 *  wait&waitpid可以回收到的子进程事件:
 *  1.调用_exit和exit终止，并指定的一个整型值作为退出状态
 *  2.子进程收到未处理信号而终止
 *  3.子进程因为信号而停止，并以WUNTRACED标志调用waitpid
 *  4.子进程收到信号SIGCONT而恢复,并以WCONTINUED标志调用waitpid()
 *
 *  等待状态包含了上述所有情况，而终止状态指代前两种情况
 *
 *  正常终止情况:使用8~15表示退出状态 　一共0~255中状态
 *  信号所杀:   7标志是否内存转储，0~6为终止信号
 *  信号停止: 8~15 终止信号,0~7 是0x7F
 *  信号恢复: 0xFFFF
 *
 *  WIFEXITED 若子进程正常结束则返回真，宏WEXITSTATUS返回子进程的退出状态
 *  WIFSIGNALED 若通过信号杀掉子进程则返回true 此时WTERMSIG返回导致子进程终止的信号编号,WCOREDUMP判断是否产生核心转储文件
 *  WIFSTOPPED 若子进程因信号而停止，则返回true
 *  WIFCONTINUED　若子进程收到SIGCONT而恢复指向，则此宏返回真值true
 *
 *
 * wait3 and wait4 执行与waitpid类似的工作，主要的语义差别在于:
 * wait3和wait4在参数rusage所指向的结构中返回终止子进程的资源使用情况
 *
 *  子进程的终止属异步事件，父进程无法预知其子进程何时终止，即使父进程向子进程发送SIGKILL信号，子进程终止的确切时间
 *  还依赖与系统的调度。
 *
 *  处理僵尸进程:
 *  1.父进程阻塞的调用wait和waitpid回收子进程，如果此刻没有已经终止的子进程，那么调用将会阻塞
 *  2.父进程周期性地调用带有WNOHANG标志的waitpid,执行针对已终止子进程的非阻塞式检查(轮询)
 *
 *  上面两个方法都有其局限性，可以为SIGCHLD建立信号处理程序，异步回收僵尸进程
 *
 *  已停止的子进程也会向父进程发送SIGCHLD信号,为了控制这个行为，可以使用sigaction为SIGCHLD设置信号处理程序的
 *  时候设置SA_NOCLDSTOP标志
 *
 *  对SIGCHLD设置为SIG_IGN系统，从而会将其后终止的子进程立即删除，毋庸转换为僵尸进程，虽然默认处置就是将其忽略
 *  但是显式设置对SIG_IGN标志的处置还是会导致这里所描述的行为差异，对于既有的僵尸进程的状态，对他们的处理要正常进行
 *  给SIGCHLD设置SIG_IGN效果等同于sigaction设置SA_NOCLDWAIT标志，但是两者的区别在于后者同样会导致子进程会发送SIGCHLD
 *  信号给父进程，但是无法在SIGCHLD处理程序中调用wait来获得子进程状态。
 *
 */

    //等待任意子进程
       pid_t wait3(int *status, int options,
                   struct rusage *rusage);
    //等待选定的一个或多个子进程
       pid_t wait4(pid_t pid, int *status, int options,
                   struct rusage *rusage);


int main()
{

}
