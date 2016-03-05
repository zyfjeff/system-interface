#define _XOPEN_SOURCE
#include <unistd.h>
#include <limits.h>
#include <pwd.h>
#include <shadow.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>

int main(int argc,char *argv)
{
    char *username,*password,*encrypted,*p;
    struct passwd *pwd;
    struct spwd *spwd;
    bool authOk;
    size_t len;
    long lnmax;
    //获取username最大长度
    lnmax = sysconf(_SC_LOGIN_NAME_MAX);
    if(lnmax == -1)
        lnmax = 256;

    username = malloc(lnmax);
    if(username == NULL) {
        fprintf(stderr,"malloc failure\n");
        exit(EXIT_FAILURE);
    }

    printf("Username: ");
    fflush(stdout);
    //用户输入username
    if(fgets(username,lnmax,stdin) == NULL) {
        exit(EXIT_FAILURE);
    }
    //设置username
    len = strlen(username);
    if(username[len - 1] == '\n')
        username[len - 1] = '\0';

    pwd = getpwnam(username);
    if(pwd == NULL) {
        perror("couldn't get password record");
        exit(EXIT_FAILURE);
    }

    spwd = getspnam(username);

    if(spwd == NULL && errno == EACCES) {
        perror("no permission to read shadow password file");
        exit(EXIT_FAILURE);
    }

    if(spwd != NULL)
        pwd->pw_passwd = spwd->sp_pwdp;
    password = getpass("Password: ");
    encrypted = crypt(password,pwd->pw_passwd);
    //记得立刻清楚密码在内存中的数据
    for(p = password; *p != '\0';)
        *p++ = '\0';

    if(encrypted == NULL) {
        perror("crypt:");
        exit(EXIT_FAILURE);
    }
    authOk = strcmp(encrypted,pwd->pw_passwd) == 0;
    if(!authOk) {
        printf("incorrect password\n");
        exit(EXIT_FAILURE);
    }
    printf("Successfully authenticated: UID=%ld\n",(long)pwd->pw_uid);
    exit(EXIT_SUCCESS);

}
