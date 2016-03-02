#include <mcheck.h>
#include <stdlib.h>
#include <stdio.h>

/*
 *  mtrace muntrace 分别再程序中打开和关闭对内存分配调用进行跟踪的功能
 *  需要配置环境遍历MALLOC_TRACE，将追踪的信息写入到MALLOC_TRACE指定的文件中
 *  然后通过mtrace解析输出的内容，注意需要在编译的时候加上-g
 *
 *
 */
int
main(int argc, char *argv[])
{
    int j;

    mtrace();

    for (j = 0; j < 2; j++)
        malloc(100);            /* Never freed--a memory leak */

    calloc(16, 16);             /* Never freed--a memory leak */
    exit(EXIT_SUCCESS);
}

