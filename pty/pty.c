/*
 *  1.驱动程序打开伪终端主设备
 *  2.驱动程序调用fork来创建一个子进程
 *      a. 调用setsid启动一个新的会话,使该子进程成为会话的领头进程,该操作使得子进程失去了它的控制终端
 *      b.打开同伪终端主设备相对应的从设备，由于子进程是会话的头领进程，且没有控制终端，那么伪终端从设备就成为子进程的控制终端了
 *      c.调用dup为从设备复制标准输入，标准输出，以及错误输出的文件描述符
 *      d.调用exec启动要连接到伪终端从设备的面向终端程序
 *
 *  伪终端的应用:
 *      expect 程序使用伪终端来允许交互式面向终端程序可以从脚本文件中驱动
 *      screen　程序使用伪终端在单个物理终端同多个进程间实现多路复用
 *      script 程序使用到了伪终端，用来记录shell会话中的所有输入和输出
 *
 *  posix_openpt 打开一个未使用的伪终端主设备，返回对应的描述符
 *  grantpt　修改对应于伪终端主设备的从设备属主和权限
 *  unlockpt　解锁对应于伪终端主设备的从设备，这样就能打开从设备了
 *  ptsname　返回对应于伪终端主设备的从设备名称，
 *
 */


#include <stdlib.h>
#include <fcntl.h>
int posix_openpt(int flags);

/*  flags:
 *      O_RDWR
 *      O_NOCTTY　使这个终端不成为当前进程的控制终端
 *  /proc/sys/kernel/pty/max 4094　设置伪终端的最大数量
 *  /proc/sys/kernel/pty/nr 这个文件记录了当前系统有多少UNIX伪终端
 */

       #define _XOPEN_SOURCE       /* See feature_test_macros(7) */
       #include <stdlib.h>

       int grantpt(int fd);

/*
 *  1.将从设备的属主修改为与调用进程相同的有效用户ID
 *  2.将从设备的组修改为tty
 *  3.修改从设备的权限，使拥有者有读和写权限，组拥有写权限
 *
 *  在Linux上，伪终端从设备自动按照以上方式配置，因此不需要调用grantpt，因为会创建子进程，因此如果调用程序为
 *  SIGCHLD信号安装处理例程的时候，则grantpt的行为是未定义的
 */

       #define _XOPEN_SOURCE       /* See feature_test_macros(7) */
       #include <stdlib.h>

       int unlockpt(int fd);

/*
 *  解锁从设备,在unlockpt之前尝试打开伪终端从设备将导致失败，错误码为EIO
 *  这个锁机制的目的是允许调用进程在其他进程能够打开这个伪终端从设备之前执行必要的初始化工作
 */

       #define _XOPEN_SOURCE       /* See feature_test_macros(7) */
       #include <stdlib.h>

       char *ptsname(int fd);

       #define _GNU_SOURCE         /* See feature_test_macros(7) */
       #include <stdlib.h>

       int ptsname_r(int fd, char *buf, size_t buflen);

/*
 *  返回从设备的名称，在linux上ptsname返回的行为/dev/pts/nn的字符串,nn是伪终端从设备专用的唯一标示号所取代
 *  返回的从设备名称所占用的缓冲区是静态分配的，后续调用会覆盖前次的结果，得到从设备名称后就可以使用open来打开了
 *
 */

