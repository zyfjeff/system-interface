#define _GNU_SOURCE
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
extern const char *const sys_siglist[];

int main()
{
    printf("%s\n",strsignal(SIGKILL));
    psignal(SIGKILL,"test");
}



