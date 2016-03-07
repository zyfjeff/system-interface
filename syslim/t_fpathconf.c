#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
/*
 *  serrlimit修改进程的各种资源限制
 *  _SC_OPEN_MAX 限制进程能打开的文件数量
 *  _SC_CHILD_MAX 限制每个用户所创建的子进程的限额
 *  _SC_ARG_MAX 限制进程的命令行参数和环境变量所占用的存储空间
 *
 *
 */
static void fpathconfPrint(const char *msg,int fd,int name)
{
    long lim;
    errno = 0;
    lim = fpathconf(fd,name);
    if(lim != -1) {
        printf("%s %ld\n",msg,lim);
    } else {
        if(errno == 0) {
            printf("%s (indeterminate)\n",msg);
        } else {
            perror("sysconf");
            exit(EXIT_FAILURE);
        }
    }
}

int main(int argc,char *argv[])
{
    fpathconfPrint("_PC_NAME_MAX: ",STDIN_FILENO,_PC_NAME_MAX);
    fpathconfPrint("_PC_PATH_MAXL: ",STDIN_FILENO,_PC_PATH_MAX);
    fpathconfPrint("_PC_PIPE_BUF: ",STDIN_FILENO,_PC_PIPE_BUF);
    exit(EXIT_SUCCESS);

}
