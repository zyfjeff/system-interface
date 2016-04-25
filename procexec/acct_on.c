#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
    if(acct("pacct") == -1) {
        perror("pacct");
    }

    printf("Process accounting %s\n",
            (argv[1] == NULL) ? "disabled" : "enabled");
    exit(EXIT_SUCCESS);
}
