
/*
 *  实际用户ID和实际组ID 确定了进程所属的用户和组 登陆shell从/etc/passwd中读取第三字段和第四字段，作为实际用户的id
 *  和实际组id
 *
 *  有效用户id和有效组id还有辅助组id一起确定了授予进程的权限，一般情况有效用户和有效组id和实际用户实际组id相同．
 *  但是有两种方法可以使之不同:
 *
 *  1.使用调整用户能力的系统调用
 *  2.使用set-user-ID和set-group-ID
 *
 *  set-user-ID程序会将进程的有效用户ID设置为可执行文件的用户ID，从而获得常规情况下并不具有的权限
 *  例如: passwd mount umount su等命令就是使用了set-user-ID
 *  set-group-ID类似，wall使用了set-group-ID
 *
 *  保存set-user-ID和保存set-group-ID 也称之为保存用户ID和保存组ID
 *  其目的在于结合set-user-ID和set-group-ID来使用
 *  保存用户ID和保存组ID会拷贝有效用户ID和有效组ID，无论是否是设置了set-user或者set-group位
 *
 *  保存用户ID和保存组ID存在的一个目的就是在于让进程可以丢弃权限,然后再通过保存用户id恢复权限
 *
 *  文件系统用户id和组id(不是文件属主和属组)
 *  始终和有效用户id和有效用户组id保持同步，只有在使用linux特有的两个系统调用setfsuid和setfsgid的时候，才会不同．
 *
 *  CAP_SETUID  允许进程任意修改用户ID
 *  CAP_SETGID  允许进程任意修改组ID
 */

#include <unistd.h>
#include <sys/types.h>
uid_t getuid(void);
uid_t geteuid(void);

/*
 *  区分特权进程和非特权进程对这个函数的调用情况:
 *
 *  设置进程的有效id,如果是非特权进程调用,那么uid只能是实际用户id,或者是保存用户id,因为普通程序的实际用户id和保存用户id.还有
 *  有效用户id都是相等的,因此,只有在设置了set-user-ID的情况下,setuid才会有作用.
 *
 *  特权进程以一个非0参数调用setuid时,实际用户id,有效用户id,保存用户id都会被设置为uid参数所指定的值,这个操作是单向的,一旦设置
 *  所有特权都将丢失,且之后也不能再使用setuid调用将有效用户id重置为0了.
 *
 */
int setuid(uid_t uid);

/*
 *  修改进程的有效用户id和有效用户组
 *  非特权进程: 仅能将其有效id修改为相应的实际id或者保存用户id
 *
 *  特权进程: 将有效用户id修改为任意值,此后这个进程不再具有特权.
 *
 */
int seteuid(uid_t euid);
int setegid(gid_t egid);


/*
 *  修改实际ID和有效ID
 *
 *
 */
int setreuid(uid_t ruid, uid_t euid);
int setregid(gid_t rgid, gid_t egid);





