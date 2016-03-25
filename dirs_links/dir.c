#include <sys/types.h>
#include <dirent.h>

/*
 *  本质上都是去调用getdents系统调用
 *
 */
DIR *opendir(const char *name);
DIR *fdopendir(int fd);
//没调用readdir一次，就会从dirp所指代的目录流中读取下一目录返回，并返回一枚指针指向经静态分配而得到的dirent
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







