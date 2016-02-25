#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
int main()
{
    perror("execute success");

    int fd = open("not_exists",O_RDONLY);
    if(fd == -1) {
        //当调用失败，就使用perror打印错误．
        //但是如果调用成功，不要想当然的通过perror来打印成功信息，
        //因为有的调用在调用成功这时是不会设置errno为0的，因此此时errno保存的值还是上次调用
        //成功或者失败的值
        perror("open");
 //       exit(EXIT_FAILURE);
    }

    printf("5 status code corresponding %s\n",strerror(5));
    //返回Unknown error 257
    printf("257 status code corresponding %s\n",strerror(257));
    char *p = strerror(257);
    char *c = strerror(5);
    printf("%s\n",c);
    printf("%s\n",p);

    //strerror_r 线程安全的版本，使用用户传入的buf来存放返回的结果
    //线程函数失败成功返回０，失败返回一个整数表示错误号
}
