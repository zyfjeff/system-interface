#include <stdio.h>

/*
 *  目录权限:
 *      读权限: 可列出目录之下的内容
 *      写权限: 可在目录内创建,删除文件
 *      可执行权限: 可访问目录中的文件,可以cd到这个目录下,访问目录下文件的i节点信息
 *  访问文件的时候，需要拥有对路径名所列出的所有目录的执行权限
 *  拥有读目录的读权限，只能列出目录之下的内容，要访问目录内文件的内容，必须要有执行权限
 *  反之如果拥有目录的可执行权限，没有读权限，只要知道目录内的文件的名称，仍可对其进行访问
 *
 *  文件权限检查算法:
 *  1.对于特权级进程，授予其所有访问权限
 *  2.若进程的有效用户ID与文件的用户ID(属主)相同，内核会根据文件的属主权限授予进程相应的访问权限
 *  3.若进程的有效组ID或任一附加组ID与文件的组ID想匹配，内核会根据文件的数组权限，授予进程对文件的相应访问权限
 *  4.若以上三点都不满足，内核会根据文件的other权限，授予进程相应的权限
 *
 */

/*
       #include <unistd.h>
       int access(const char *pathname, int mode);
       根据mode的不同可以检测的情况也不同:
        mode:
            F_OK    有这个文件吗?
            R_OK    对这个文件有读权限吗?
            W_OK    对这个文件有写权限吗?
            X_OK    对这个恩家有执行权限吗?

       #include <fcntl.h>
       #include <unistd.h>
       int faccessat(int dirfd, const char *pathname, int mode, int flags);
*/

/*  Set-User-ID(04000)
 *  Set-Group-ID(02000)
 *  Sticky(01000)
 *
 *  set-group-ID的用途:
 *      1.设置nogrpid选项状态的目录下所新建的文件，控制其群组的从属关系
 *      2.可用于强制锁定文件
 *
 *  set-group-ID和set-User-ID　的作用很好理解，主要就是更改进程的有效用户ID或者有效组ID为文件的属于主或属组
 *  比较难理解的是Sticky，通常作用于目录时，sticky权限位起限制删除位的作用．为目录设置该位的时候
 *  对于非特权进程来说只要对目录具有写权限，且为文件或目录的属主时，才能对目录下的文件删除，修改和重命名等操作
 *
 *  通过Sticky位可实现多用户共享同一个目录，但是每个用户只能删除自己创建的文件
 */

/*
       #include <sys/types.h>
       #include <sys/stat.h>

       mode_t umask(mode_t mask);
*/

/*
       #include <sys/stat.h>
       如果pathname是符号链接，那么更改的是符号链接所指向的文件的权限
       int chmod(const char *pathname, mode_t mode);
       int fchmod(int fd, mode_t mode);

       更改文件的权限
*/

int main()
{

}
