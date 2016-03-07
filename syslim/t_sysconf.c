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
static void sysconfPrint(const char *msg,int name)
{
    long lim;
    errno = 0;
    lim = sysconf(name);
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
    sysconfPrint("_SC_ARG_MAX:  ",_SC_ARG_MAX);
    sysconfPrint("_SC_LOGIN_NAME_MAX:  ",_SC_LOGIN_NAME_MAX);
    sysconfPrint("_SC_OPEN_MAX:  ",_SC_OPEN_MAX);
    sysconfPrint("_SC_NGROUPS_MAX:  ",_SC_NGROUPS_MAX);
    sysconfPrint("_SC_PAGESIZE:  ",_SC_PAGESIZE);
    sysconfPrint("_SC_RTSIG_MAX:  ",_SC_RTSIG_MAX);
    exit(EXIT_SUCCESS);

}
