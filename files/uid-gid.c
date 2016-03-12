#include <stdio.h>
#include <stdlib.h>


/*
 *  新建文件的时候,文件的属主,取的是当前的用效用户id,而文件的属组则分两种不同的情况:
 *  1.当使用mount -o grpid的时候新建的文件总是继承父目录的组ID
 *  2.当使用mount -o nogrpid的时候新建的文件的组id是进程的有效组id
 *
 *  如果目录设置了set-group-id,那么文件的组id又将从其父目录处继承
 *
 *
 */


/*
 *  修改文件的属主和属组 chown fchown还有 lchown我想这三者的区别应该很明显了
 *  fchownat则是类似于utimensat包含了chown fchown还有lchown的功能
 *
 */
#include <unistd.h>
int chown(const char *pathname, uid_t owner, gid_t group);
int fchown(int fd, uid_t owner, gid_t group);
int lchown(const char *pathname, uid_t owner, gid_t group);

#include <fcntl.h>           /* Definition of AT_* constants */
#include <unistd.h>
int fchownat(int dirfd, const char *pathname,
             uid_t owner, gid_t group, int flags);

//如果文件的属主和属组发生了改变,那么set-user-ID和set-group-ID权限位也会随之关闭
//这是为了防止一种行为:如果普通用户对一个可执行文件有set-user-id或者set-group-id特殊位的时候
//普通用户将这个可执行文件修改为某些系统用户,那么此时执行这个可执行文件就会拥有这个系统用户的身份
//因此为了避免这个问题,在更改了文件属主或属组的时候,特殊位会随之关闭,但是存在特例:
//
//特例:
//改变文件的属主和属组的时候,如果已经屏蔽了属组的可执行权限位,或者要改变的是目录的所有权,那么将不会屏蔽set-group-ID权限位
//set-group-id的其他用途:
//  1.屏蔽了属组的可执行权限位,则可利用set-group-ID权限位来启用强制文件锁定
//  2.当作用于目录时,可利用set-group-id位来控制在该目录下创建文件的所有权

int main()
{

}
