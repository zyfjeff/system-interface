#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

extern char **environ;

//setenv 将name value拷贝到内部维护的缓冲区中,overwrite确定是否覆盖已有的环境变量
int setenv(const char *name, const char *value, int overwrite);
//清除环境变量，并释放对应的内部缓冲区
int unsetenv(const char *name);

//内部指针直接指向string的地址，不分配缓冲区，因此string不能是自动变量
int putenv(char *string);

//不释放内部缓冲器,知识把environ设置为NULL,所以再某些情况下使用setenv和clearenv可能会导致内存泄露
int clearenv(void);


/*
 *  获取命令行参数:
 *  1.通过main函数的argc,argv
 *  2.通过/proc/self/cmdline　获取命令行参数
 *  3.program_invocation_name program_invocation_short_name 程序的完整路径和短路径
 *  需要定义_GNU_SOURCE 包含再errno.h 中
 *
 *
 *
 *
 *
 */
int main(int argc,char *argv[])
{
    int j;
    char **ep;
    clearenv();
    for(j = 1;j < argc;j++)
        //putenv的参数格式是 variable=value
        if(putenv(argv[j]) != 0) {
            perror("putenv:");
            exit(EXIT_FAILURE);
        }

    unsetenv("BYE"); //清除BYE环境变量
    for(ep = environ; *ep != NULL; ep++)
        puts(*ep);
    printf("full-name:%s short-name:%s\n",program_invocation_name,program_invocation_short_name);
    exit(EXIT_FAILURE);
}
