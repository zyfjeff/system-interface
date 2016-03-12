#include <stdio.h>
#include <stdlib.h>
#include <sys/mount.h>

/*
 * source和target是
 * filesystemtype 是文件系统类型
 * mountflags如下:
 *  MS_BIND 建立绑定挂载
 *  MS_DIRSYNC  同步更新路径
 *  MS_MANDLOCK 允许强制锁定文件
 *  MS_MOVE 以原子操作将挂载点移到新位置
 *  MS_NOATIME  不更新文件的最后访问时间
 *  MS_NODEV    不允许访问设备
 *  MS_NODIRATIME   不更新目录的最后访问时间
 *  MS_NOEXEC   不允许程序执行或脚本执行
 *  MS_NOSUID   禁用set-user-ID和set-group-ID程序
 *  MS_RDONLY   以只读方式挂载,不能修改或者创建文件
 *  MS_REC  递归挂载
 *  MS_RELATIME
 *  MS_REMOUNT
 *  MS_STRICTATIME  总是更新最后访问时间
 *  MS_SYNCHRONOUS  使得所有文件和目录同步更新
 *
 *  data参数:
 *      取决于特定的文件系统
 *
 *
 *  内核2.6.15开始支持共享子树的概念
 *  MS_PRIVATE  MS_SHARED   MS_SLAVE    MS_UNBINDABLE
 */
int mount(const char *source, const char *target,const char *filesystemtype,
          unsigned long mountflags,const void *data);


/*
 *  unmoun2是对umount的扩展
 *  flags:
 *      MNT_DEATCH  执行lazy对挂载点加以标记,一方面允许使已使用了挂载点的进程得以继续使用,同时禁止任何其他进程对挂载
 *          点发起新的访问,当所有进程不再使用访问点时,系统会卸载相应的文件系统
 *
 *      MNT_EXPIRE 将挂载点标记为到期,提供了一种可以卸载某段时间内未使用的文件系统,第一次调用的时候,如果挂载点
 *              处于空闲状态就设置为到期,并返回EAGAIN错误,如果挂载点正在使用就返回错误EBUSY,但是不设置到期,
 *              第二次再次调用umount2的时候并且指定MNT_EXPIRE标志就会卸载到期的挂载点
 *
 *      MNT_FORCE   即便文件系统处于在用状态,依然将其强行卸载,采用这个选项会可能会导致数据丢失
 *
 *      UMOUNT_NOFOLLOW 若target是符号链接,则不对其进行解引用,这个标志专为某些set-user-ID-root程序而设计
 *
 */

int umount(const char *target);
int umount2(const char *target, int flags);


int main()
{

}
