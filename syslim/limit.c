#include <stdio.h>
#include <stdlib.h>

/*
 * 系统限制 命名风格是冠以字符串_POSIX_,而且通常还包含字符串_MAX_
 * 在特定系统上获取限制,通常更为可取的方法是使用<limits.h>文件,sysconf或pathconfa
 * 限制归为三类:
 *      运行时恒定值(值可能不确定 因为该值可能依赖于可用的内存空间) _SC_ 系列常量之一
 *      路径名变量值    _PC_系列常量之一
 *      运行时可增加值
 *
 *  _PC_NAME_MAX    文件命名的最大长度
 *  _PC_PATH_MAX    相对路径名的最大长度
 *  _PC_PIPE_BUF
 *
 */
int main()
{

}
