#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <stdlib.h>

char* user_name_formid(uid_t uid)
{
    struct passwd *pwd;
    pwd = getpwuid(uid);
    return(pwd == NULL)? NULL : pwd->pw_name;
}
/*
 *If endptr is not NULL, strtol() stores the address of the first invalid character in *endptr.  If there  were  no  digits  at
 *all, strtol() stores the original value of nptr in *endptr (and returns 0).  In particular, if *nptr is not '\0' but **endptr
 *is '\0' on return, the entire string is valid.
 * strtol中如果endptr不为NULL，那么strtol将会把要转换的字符串中第一个不是有效字符的位置保存在endptr中，那么只要*endptr不为\0
 * 那么就说明要转换的字符串不是有效的字符串，如果要转换的字符串不为\0.并且*endptr是\0，那么就说明要转换的字符串是有效的
 * strtol的返回值就是要转换后的结果
 */
uid_t use_id_fromname(const char *name)
{
    struct passwd *pwd;
    uid_t u;
    char *endptr;
    if(name == NULL || *name == '\0')
        return -1;
    u = strtol(name,&endptr,10);

    if(*endptr == '\0')
        return u;

    pwd = getpwnam(name);
    if(pwd == NULL)
        return -1;

    return pwd->pw_uid;
}

char * group_name_fromid(gid_t gid)
{
    struct group *grp;
    grp = getgrgid(gid);
    return (grp == NULL)? NULL : grp->gr_name;
}

gid_t group_id_fromname(const char *name)
{
    struct group *grp;
    gid_t g;
    char *endptr;

    if(name == NULL || *name == '\0')
        return -1;

    g = strtol(name,&endptr,10);
    if(*endptr == '\0')
        return g;

    grp = getgrnam(name);
    if(grp == NULL)
        return -1;

    return grp->gr_gid;
}
