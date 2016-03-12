#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/fs.h>
#include <sys/ioctl.h>

//扩展属性,又称为i节点标志，ext2是首个支持i节点标志的Linux文件系统，
//随后其他的文件系统，诸如:Btrfs ext3 ext4 reiserfs
//xfs,JFS等,各个文件系统对i节点标志的支持范围略有不同．
//reiserfs上要使用i节点标志的化需要在挂载的时候指定-o attrs选项

/*
 *  通过lsattr查看扩展属性，通过chattr来设置扩展属性
 *  可以通过ioctl来获取或修改i节点标志，这些i节点标志名称定义与
 *  <linux/fs.h>
 *
 * 下面是ioctl中用的常量和chattr选项以及用途
 *  FS_APPEND_FL        a   仅能在尾部追加
 *  FS_COMPR_FL         c   启用文件压缩
 *  FS_DIRSYNC_FL       D   目录更新同步
 *  FS_IMMUTABE_FL      i   不可变更
 *  FS_JOURNAL_DATA_FL  j   针对数据启用日志
 *  FS_NOATIME_FL       A   不更新文件的上次访问时间
 *  FS_NODUMP_FL        d   不转储
 *  FS_NOTAIL_FL        t   禁用尾部打包
 *  FS_SECRM_FL         s   安全删除(未实现)
 *  FS_SYNC_FL          S   文件(和目录)同步更新
 *  FS_TOPDIR_FL        T   以Orlov策略来处理顶层目录
 *  FS_UNRM_FL          u   可恢复已删除的文件(未实现)
 *
 * 每一个文件系统都会定义一套值和上面一样，但是名字是自己文件系统
 * 专有的常量名，因此同一值在ext2文件系统被定义为<linux/ext2_fs.h>
 * EXT2_APPEND_FL，而register文件系统被定义为<linux/reiser_fs.h>的
 * REISERFS_APPEND_FL，所以包含<linux/fs.h>或者包含任何一个文件中的头文件
 * 都可以使用．
 */

/*
 *  FS_APPEND_FL    仅当指定O_APPEND标志时，方能打开文件并写入
 *  FS_COMPR_FL     文件内容经压缩后存储于磁盘上
 *  FS_DIRSYNC_FL   使得目录的更新同步发生
 *  FS_IMMUTABLE_FL 将文件设置为不可更改，既不能更新文件数据，也不能更新文件元数据
 *  FS_JOURNAL_DATA_FL  对数据启用日志功能
 *  FS_NOATIME_FL 访问文件时不更新文件的上次访问时间，省去了每次访问时对I节点更新
 *  FS_NODUMP_FL    使用dump(8)备份系统时跳过具有此标志的文件
 *  FS_NOTAIL_FL    禁用尾部打包，只有reiserfs文件系统才支持该标志，此标志屏蔽了reiserfs
 *                  的尾部打包特性，即尝试将小文件(或较大文件的最后一段)与其元数据置于同一磁盘块中
 *  FS_SECRM_FL     安全的删除文件(该特性尚未实现)
 *  FS_SYNC_FL      文件更新保持同步，相当于打开文件使用O_SYNC标志一样
 *  FS_TOPDIR_FL
 *  FS_UNRM_FL      允许该文件在遭删除后能得以恢复，因此该特性尚未实现
 *
 */

int main()
{
    int attr;
    //获取扩展属性
    if(ioctl(fd,FS_IOC_GETFALAGS,&attr) == -1) {
        perror("ioctl getflags");
        exit(EXIT_FAILURE);
    }
    attr |= FS_NOATIME_FL;
    //设置扩展属性
    if(ioctl(fd,FS_IOC_SETFLAGS,&attr) == -1) {
        perror("ioctl setflags");
        exit(EXIT_FAILURE);
    }
}
