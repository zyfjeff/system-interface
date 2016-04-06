#include <sys/types.h>
#include <dirent.h>

/*
 *  本质上都是去调用getdents系统调用
 *
 */
DIR *opendir(const char *name);
DIR *fdopendir(int fd);
//每调用readdir一次，就会从dirp所指代的目录流中读取下一目录返回，并返回一枚指针指向经静态分配而得到的dirent
//类型结构体。因此readdir是不可重入的，每次readdir的调用都会覆盖上次的dirent，readdir返回的文件名是未排序的。
struct dirent *readdir(DIR *dirp);
//可重入的，使用用户分配的内存，存储dirent结构体
int readdir_r(DIR *dirp, struct dirent *entry, struct dirent **result);
//重置目录流指针
void rewinddir(DIR *dirp);
//关闭目录流
int closedir(DIR *dirp);
//报告目录流的位置
long telldir(DIR *dirp);
//定位目录流
void seekdir(DIR *dirp, long loc);
//返回目录流对应的fd,可以把返回的fd传递给fchdir来更改进程的当前工作目录
int dirfd(DIR *dirp);



/*
 *  遍历目录树，并为子树中的每个文件执行某些操作(也就是由程序员定义的函数)
 *
 */
#define _XOPEN_SOURCE 500   /* See feature_test_macros(7) */
#include <ftw.h>
int nftw(const char *dirpath,
               int (*fn) (const char *fpath, const struct stat *sb,
                          int typeflag, struct FTW *ftwbuf),
               int nopenfd, int flags);



//获取当前工作目录
#include <unistd.h>
//当buf为NULL,size为0的时候，由内部malloc分配空间，存储结果，需要调用者自己去释放其结果
char *getcwd(char *buf, size_t size);
char *getwd(char *buf);
//不具备可移植性
char *get_current_dir_name(void);

/*
 *  linux系统为传统的接口提供了一个新的接口，接口名称在原来的名字后面添加了at，比如access，更改为faccessat,chmod改为fchmodat
 *  等等，这个新接口的第一个参数就是dirfd,如果后面的pathname参数是相对路径，那么这个相对路径不是依赖与当前目录还是相对于dirfd
 *  所指的目录
 */


#include <unistd.h>
int chroot(const char *path);
/*
 *  chroot目录中有指向chroot外部的硬链接，那么chroot区域的安全将受到威胁
 *  或者是特权进程在chroot内使用mknod创建一个内存设备文件，类似于/dev/mem 并通过该设备来访问RAM的内容
 *  到那时就一切都有可能了,因此不要在chroo区域内放置set-user-ID-root程序
 *
 *  初次之外还需要考虑下面几种可能会越狱的场景:
 *  1.调用chroot了，但是并未改变进程当前工作目录，那么程序可以使用相对路径去访问chroot外的目录
 *  2.进程对chroot区域外的某一个目录持有一打开文件描述符，那么结合fchdir和chroot即可越狱成功
 *  3.即使chroot成功了，也没有出现上面的问题，但是遭受chroot的进程仍然可以利用unix域套接字来接受指向chroot外目录的文件描述符
 *
 */


#include <limits.h>
#include <stdlib.h>
/*
 *  对path中的所有符号链接一一解除引用，并解析其中的.和..的引用。最后生成一个绝对路径名
 */
char *realpath(const char *path, char *resolved_path);

/*
 *  将一个路径名字符串分解成目录和文件名两个部分,这两个函数会原地修改字符串,事先可以使用strdup(该函数用了malloc)，需要free
 *  使用这两个函数，需要考虑下面几个事情:
 *
 *  1.忽略pathname中尾部的斜线字符
 *  2.如果pathname中不包含斜线字符，那么dirname返回字符串.而basename将返回path
 *  3.如果pathname仅由一个斜线字符组成,那么dirname和basename均将返回字符串/
 *  4.如果pathname为空指针或者空字符串，那么dirname和basename均将返回字符串点
 *
 *
 */

#include <libgen.h>
char *dirname(char *path);
char *basename(char *path);









