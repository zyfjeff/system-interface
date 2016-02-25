#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char* argv[])
{
    int fd = open(argv[1],O_WRONLY);
    //使用fcntl获取文件状态标志的时候，有一个不统一的地方就是获取文件的访问模式和获取文件的状态标志
    //要获取文件的访问模式需要先和O_ACCMODE，然后与指定模式直接作相等比较，
    int flags = fcntl(fd,F_GETFL);
    int accessmode = flags & O_ACCMODE;
    if(accessmode == O_WRONLY)
        printf("file is writable\n");
    //判断其他文件状态标志，则直接相与

    if(flags &O_SYNC)
        printf("writes are synchronized\n");

    /*
     *  两个不同的文件描述符，若指向同一个打开文件句柄，将共享同一个文件偏移量
     *  因此如果通过其中一个文件描述符来修改文件偏移量，那么从另一个文件描述符中也会观察到这个变化
     *  无论这两个描述符是属于不同进程还是属于同一个进程，情况都如此
     *
     *  文件描述符标志(如: close-on-exec)是进程和文件描述符私有的，对这个标志的修改不会影响同一进程或不同进程
     *  中的其他文件描述符
     *
     *  两个不同的文件描述，指向同一个打开文件句柄(通过dup dup2 fcntl等实现，或者fork实现)
     *  dup dup2 fcntl都可以实现复制文件描述符，
     *  dup2可以复制文件描述符为指定的描述符，在复制之前会关闭指定的描述符，保证了close+dup的原子性
     *  dup3额外添加了一个flags参数，可以给文件描述符，指定私有的文件描述符标志，close-on-exec
     *  fcntl也提供了F_DUPFD_CLOEXEC标志
     *
     */
}
