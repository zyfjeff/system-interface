#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//提供了offset参数，等同与先lseek，然后再写入数据，最后还原回原来的offset
//不过pread保证了上面这些操作的原子性,无论是pread还是pwrite，在操作完成后都会
//将偏移量指针设还原

ssize_t pread(int fd, void *buf, size_t count, off_t offset);
ssize_t pwrite(int fd, const void *buf, size_t count, off_t offset);
#include <sys/uio.h>
/*
 *  Scatter-Gatter writev IO 可以将写入多个分散的buf，IOV_MAX 是其最多一次可以写入多少个分散的buf
 *  readv则是将数据读取出来，放到多个分散的buf中，无论是readv还是writc都是一次性再文件和用户内存之间
 *  完成数据迁移．并且是线程安全的，即使在操作过程中有进程或者线程与起共享同一个文件偏移量，并企图修改
 *  但这仍不影响readv和writev的行为．
 */
ssize_t readv(int fd, const struct iovec *iov, int iovcnt);
ssize_t writev(int fd, const struct iovec *iov, int iovcnt);
ssize_t preadv(int fd, const struct iovec *iov, int iovcnt,off_t offset);
ssize_t pwritev(int fd, const struct iovec *iov, int iovcnt,off_t offset);


int main(int argc,char *argv[])
{
    int fd = open(argv[1],O_RDWR);
    char buf[100] = {1,2,3,4,5};
    pwrite(fd,buf,5,10);
    printf("cur offset:%d\n",lseek(fd,0,SEEK_CUR));

}
