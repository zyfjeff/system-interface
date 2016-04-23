#include <stdio.h>

/*  exec系列函数:
 *  execle
 *  execlp
 *  execvp
 *  execv
 *  execl
 *
 *  execlp execvp　只要求程序的文件名，会自动根据PATH去查找全路径名
 *  execle execlp execl 要求开发者在调用中以字符串列表形式来指定参数，而不是argv列表
 *  execve execle 允许开发者通过envp来为新城徐显式指定环境变量
 *
 *  上面这些系列函数都是构建与execve调用之上。
 *
 *
 *  exec系列函数会查看文件是否是#!开头，如果是就运行对应的解释程序来运行该脚本
 *  如果没哟#!行,那么就会执行失败，但是execlp和execvp则会判断这个文件是否是二进制格式的，如果不是则会使用shell来
 *  解释这个文件。
 *
 *  exec会保持文件文件描述符的打开状态不变，因此在调用exec函数之前应该关闭已经打开的文件描述符。
 *  也可以通过设置close-on-exec标志(FD_CLOEXEC)
 *
 *
 *  信号与exec()
 *  exec在执行时会将现有进程的文本段丢弃，该文本段可能包含由调用进程创建的信号处理器程序，既然处理器程序已经不知
 *  所踪，内核就会将对所有已设信号的处置重置为SIG_DFL,但是有一个例外就是SIGCHLD信号的默认处理，如果此前是忽略那么exec后
 *  是忽略还是重置规范没有定义，Linux操作取前者，为了保证可移植性在exec之前应该设置SIGCHLD SIG_DFL。
 *
 *  在具有set-user-ID和set-group-ID的程序中避免使用system，鉴于shell对操作的控制有赖于各种环境变量，故而使用system会不可
 *  避免地给系统带来安全隐患。
 *
 *  system的实现分析:
 *
 *  1.只能使用waitpid来收集指定子进程的状态，而不能是wait，因为wait等待的是任一子进程。
 *  2.主程序有可能直接创建其他子进程，并执行wait等待SIGCHLD，这将会导致主程序处理了systemd产生的子进程
 *  3.主程序应该忽略SIGINT和SIGQUIT信号
 */


/*
 *
 *
 *
 */

int main()
{

}
