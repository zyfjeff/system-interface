#include <stdio.h>
//text段，数初始化数据段，非初始化数据段结尾处下一个字节的地址
extern char etext,edata,end;

int main()
{
    printf("%p:%p:%p\n",&etext,&edata,&end);
}
