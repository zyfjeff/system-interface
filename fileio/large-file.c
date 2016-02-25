#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

/*
 *   大文件io   LFS规范 可以通过下面两种方式获得LFS的功能
 *   * 使用支持大文件操作的备选API
 *   * 在编译应用程序的时候，将宏_FILE_OFFSET_BITS的值定义为64
 *
 *   1.过渡型的LFS API
 *   fopen64    open64  lseek64 truncate64 ......
 *
 *   2.直接定义#define _FILE_OFFSET_BITS 64
 *   当通过定义_FILE_OFFSET_BITS为64的时候，off_t变成了64bits的类型,大小是long long类型.
 *   通过%lld然后将off_t强制转换为long long类型才能打印
 *
 *   使用32位的函数访问大文件，调用可能会返回EOVERFLOW错误
 */
int main()
{

}
