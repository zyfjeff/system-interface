#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>


int main()
{
    signal(SIGABRT,SIG_IGN);
    printf("start to abort process\n");
    abort();
    while(1);
}
