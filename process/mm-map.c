#include <stdio.h>
#include <stdlib.h>
//text段，数初始化数据段，非初始化数据段结尾处下一个字节的地址
extern char etext,edata,end;

char globBuf[65536];
int primes[] = {2,3,5,7};

static int square(int x) {
    int result;
    result = x * x;
    return result;
}

static void doCalc(int val)
{
    printf("The square of %d is %d\n",val,square(val));
    if(val < 1000) {
        int t;
        t = val * val * val;
        printf("the cube of %d is %d\n",val,t);
    }
}

int main()
{
    printf("%p:%p:%p\n",&etext,&edata,&end);
    static int key = 9973;
    static char mbuf[1024000];
    char *p;
    p = malloc(1024);
    doCalc(key);
    exit(EXIT_SUCCESS);
}
