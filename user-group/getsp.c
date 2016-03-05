#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <shadow.h>

/*
 *  操作/etc/shadow文件,返回struct spwd结构
 *
 *
 */
//根据用户名得到spwd
struct spwd *getspnam(const char *name);

//遍历/etc/shadow文件
struct spwd *getspent(void);
void setspent(void);
void endspent(void);

struct spwd *fgetspent(FILE *fp);
struct spwd *sgetspent(const char *s);
int putspent(const struct spwd *p, FILE *fp);
int lckpwdf(void);
int ulckpwdf(void);

/*
 *  密码加密和用户认证
 *
 */

char *crypt(const char *key, const char *salt);

//       #define _GNU_SOURCE         /* See feature_test_macros(7) */
//       #include <crypt.h>

char *crypt_r(const char *key, const char *salt,
              struct crypt_data *data);

//Link with -lcrypt.

//提供一个prompt给用户输入密码
char *getpass( const char *prompt);

