#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 *  fuser和lsof　用户获取一个进程当前打开了哪些文件
 *  /proc/PID/fd里面的内容，包含了进程打开的文件描述符，并且其符号链接指明了描述符对应的文件路径
 *
 *  硬链接:
 *      不可跨越文件系统
 *      不能给目录创建硬链接，避免链接环路
 *
 *  使用绑定挂载可以获得与目录创建硬链接相似的效果
 *
 *  符号链接:
 *      可能会产生链接环路，linux解析符号链接链路的时候，解引用操作次数限制为5次，
 *      避免解析符号链接时免于引发堆栈溢出,这个次数取决于_POSIX_SYMLOOP_MAX
 *
 *  如果符号链接内容的字符串总长度很小，足以放入i-node中，通常用于存放数据指针的位置，就不需要额外申请一个
 *  磁盘块来存放符号链接的内容。
 *
 *  每个文件系统的根目录的inode号是从2开始的，因为inode=0表示未使用，inode=1用来记录坏块，因此根目录总是从2开始
 *  大部分操作会无视符号链接的所有权和权限，是否允许操作反而是由符号链接所指代文件的所有权和权限来决定。
 *
 *  int link(const char *oldpath, const char *newpath);
 *  int unlink(const char *pathname);
 *  用于创建和移除硬链接,但是不对符号链接解引用
 *
 *  重命名文件
 *  int rename(const char *oldpath, const char *newpath);
 *
 *  建立符号链接
 *  int symlink(const char *target, const char *linkpath);
 *
 *  读取符号链接文件本身的内容
 *  ssize_t readlink(const char *pathname, char *buf, size_t bufsiz);
 *
 *  创建一个唯一命名的目录,返回的是一个经过修改处理的字符串，里面是tempplate中的实际目录名
 *  char *mkdtemp(char *template);
 *
 *  删除一个目录,要求目录需要是空的
 *  int rmdir(const char *pathname);
 *
 *  删除一个文件或者空目录,是一个库函数，不需要去检测目标是文件还是目录
 *  int remove(const char *pathname);
 *
 *
 *
 */
int main()
{


}
