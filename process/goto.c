#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

static jmp_buf env; //存放进程上下文

static void f2(void)
{
    longjmp(env,2); //跳转到env对应的进程上下文中,并让setjmp返回2
}

static void f1(int argc)
{
    if(argc == 1)
        longjmp(env,1); //跳转到env对应的进程上下文中,并让setjmp返回2
    f2();
}

static void doJump(int nvar,int rvar,int vvar)
{
    printf("Inside doJump(): nvar=%d rvar=%d vvar=%d\n",nvar,rvar,vvar);
    longjmp(env,1);
}


/*
 *  setjmp调用只能再无需临时存储的表达式中使用，例如:
 *  s = setjmp(env); //这个语句是不符合标准的,setjmp只能再下面一些语境中使用:
 *  1.if switch while等控制表达式
 *  2.一元操作符!
 *  3.比较操作符
 *  4.独立的函数调用
 *
 *  注意:
 *      longjmp调用不能跳转到一个已经返回的函数中 SUSv3规定: 如果从嵌套的信号处理器中调用longjmp函数，则该程序是行为
 *      未定义的
 *
 *  编译器优化导致longjmp操作过程中经过优化的变量被赋以错误值，解决办法就是设置这些变量为voliate．告诉编译器不对其进行
 *  优化
 */
int main(int argc,char *argv[])
{

    int nvar;
    register int rvar;
    volatile int vvar;
    nvar = 111;
    rvar = 222;
    vvar = 333;
    if(setjmp(env) == 0) {
        nvar = 777;
        rvar = 888;
        vvar = 999;
        doJump(nvar,rvar,vvar);
    } else {
        printf("after longjmp(): nvar=%d rvar=%d vvar=%d\n",nvar,rvar,vvar);
    }
    exit(EXIT_SUCCESS);

    //int ret = setjmp(env); //WARN
    /*
    switch(setjmp(env)) {
        case 0:
            printf("Calling f1() after initial setjmp()\n");
            f1(argc);
            break;

        case 1:
            printf("We jumped back from f1()\n");
            break;

        case 2:
            printf("We jumped back from f2()\n");
            break;
    }
    */
}
