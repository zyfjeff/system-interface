#include <gnu/libc-version.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>

int main()
{
    //编译时获取glibc版本,A机器上编译，Ｂ机器上运行就会存在问题．需要使用运行时获取glibc版本
    printf("major version:%d \t minor version:%d\n",__GLIBC__,__GLIBC_MINOR__);

    //获取运行时的glibc版本
    printf("glibc runtime version:%s\n",gnu_get_libc_version());

    char buf[65535] ={0};
    //  glibc特有的函数用来获取glibc版本，size_t confstr(int name, char *buf, size_t len);
    assert(confstr(_CS_GNU_LIBC_VERSION,buf,sizeof(buf)) > 0);
    printf("glibc version:%s\n",buf);
}
