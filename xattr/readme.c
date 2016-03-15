#include <stdio.h>
#include <stdlib.h>

/*
 *  文件的扩展属性(EA) 可用于实现访问列表和文件能力
 *  是以名称－值对形式将任意元数据与文件i节点关联起来的技术
 *
 *  EA的命名空间:
 *      EA的命名格式为namespace.name 其中namespace是用来把EA从
 *      功能上划分截然不用的几大类．而name则用来在既定命名空间内唯一标识某个EA
 *
 *      可供namespace使用的值有4个: user,trusted,system,security
 *      上面四类的EA namespace的用途如下:
 *
 *      * user EA将在文件权限检查的制约下由非特权级进程操控
 *      * trusted EA 也可由用户进程"驱使"
 *      * system EA
 *      * security EA
 *
 *  apt-get install attr 安装EA的用户态工具
 *  setfattr -n user.<name> -v "<value>" <filename> 设置name=value的扩展属性
 *  getfattr -n user.<name> 获取<name>对应的<value>
 *  setfattr -n user.<name> <filename> 改变<name>的value为空字符串
 *  getfattr -d <filename> dump所有的user namespace中内容
 *  setfattr -x user.<name> <filename>
 *  getfattr -m "pattern" <filename> 其中pattern默认是^user\.
 *
 *  getfattr -m - <filename> 列出一个文件的所有EA值
 *
 */

#include <sys/types.h>
#include <attr/xattr.h>
int setxattr (const char *path, const char *name,
              const void *value, size_t size, int flags);
int lsetxattr (const char *path, const char *name,
               const void *value, size_t size, int flags);
int fsetxattr (int filedes, const char *name,
               const void *value, size_t size, int flags);

//setattr lsetattr fsetxattr其实都差不多，setattr对符号链接解引用
//lsetxattr 则针对的是符号链接本身
//fsetxattr提供的是文件描述符
// flags取值如下: 如果为0就是默认情况，name不存在就创建，存在就替换
//  其他取值如下:
//      XATTR_CREATE 若具有给定名称的EA已经存在则失败
//      XATTR_REPLACE 若具有给定名称的EA不存在，则失败



//若EA中不存在名为name的值，则返回错误ENODATA，若size值过小，上述系统调用也会失败，返回错误ERANGE
//若把size设置为0，将会返回value的实际大小

       #include <sys/types.h>
       #include <attr/xattr.h>

       ssize_t getxattr (const char *path, const char *name,
                            void *value, size_t size);
       ssize_t lgetxattr (const char *path, const char *name,
                            void *value, size_t size);
       ssize_t fgetxattr (int filedes, const char *name,
                            void *value, size_t size);


       #include <sys/types.h>
       #include <attr/xattr.h>
//试图删除不存在的EA，将返回错误ENODATA
       int removexattr (const char *path, const char *name);
       int lremovexattr (const char *path, const char *name);
       int fremovexattr (int filedes, const char *name);


       #include <sys/types.h>
       #include <attr/xattr.h>

       ssize_t listxattr (const char *path,
                            char *list, size_t size);
       ssize_t llistxattr (const char *path,
                            char *list, size_t size);
       ssize_t flistxattr (int filedes,
                            char *list, size_t size);


int main()
{

}
