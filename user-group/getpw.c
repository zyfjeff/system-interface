#include <sys/types.h>
#include <pwd.h>

//都是指向内部的一个静态分配的内存，是不可重入的
struct passwd *getpwnam(const char *name);
struct passwd *getpwuid(uid_t uid);
/*  如果没有找到就返回NULL,但是不设置errno,　对于这点不用的unix实现不一样，有的unix在没有
 *  找到的情况下会返回NULL，并且设置errno，因此对于判断是否是未找到，还是出错　这是不能保证代码的可移植性的
 *
 *
 */
int getpwnam_r(const char *name, struct passwd *pwd,
                char *buf, size_t buflen, struct passwd **result);

int getpwuid_r(uid_t uid, struct passwd *pwd,
                char *buf, size_t buflen, struct passwd **result);


/*
 *  根据name或者uid返回/etc/passwd文件结构体 struct passwd,其中pw_passwd只有在未启用shadow密码的情况下，pw_passwd字段才
 *  会包含有效信息，要确定是否启用了shadow密码，最简单的编程方法就是成功调用getpwnam之后，紧接着调用getspnam,确定是否
 *  能为同一个用户名返回一条shadow密码记录
 *
 *
 */

/*	密码扫描
 *
 */
struct passwd *getpwent(void);

void setpwent(void);
void endpwent(void);

int main()
{
    struct passwd *pwd;
    while((pwd = getpwent()) != NULL)
        printf("%-8s %5ld\n",pwd->pw_name,(long)pwd->pw_uid);
    endpwent();
}



