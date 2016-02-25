#define _GNU_SOURCE

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    //和O_CREAT一起使用，使得检查文件存在与否和创建文件这两步属于同一个原子操作
    //使用pathname是符号链接，则open函数调用失败，错误号EEXIST
    printf("%d\n",O_EXCL);
    //避免使用fcntl F_GETFD F_SETFD来设置，使用fcntl来设置CLOEXEC存在竞态
    printf("%d\n",O_CLOEXEC);
    //不指定权限的情况下，会将这个文件的权限设置为栈中某个随机值
    printf("%d\n",O_CREAT);
    //无系统缓冲IO，需要开启 #define _GNU_SOURCE
    printf("%d\n",O_DIRECT);
    //同步O的数据完整性
    printf("%d\n",O_DSYNC);
    //读文件的时候不更新最近访问时间
    //设置这个标志位需要调用进程的有效用户ID必须和文件的拥有者匹配，或者进程需要拥有CAP_FOWNER特权
    //否则会调用失败，返回EPERM错误，该标志位用于索引和备份程序
    printf("%d\n",O_NOATIME);
    printf("%d\n",O_NOCTTY);
    //防止进程对pathname的符号链接进行解引用，如果pathname是符号链接则open打开失败，返回错误ELOOP
    printf("%d\n",O_NOFOLLOW);
    //清空文件内容，(必须对文件拥有写权限)
    printf("%d\n",O_TRUNC);


}
