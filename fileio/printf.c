#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
/*
 *  可移植的打印off_t size_t这些自定义类型
 *  将其转换为long型，然后使用%ld打印
 *
 */
int main()
{
    off_t a = 1000;
    printf("%ld\n",1);
}
