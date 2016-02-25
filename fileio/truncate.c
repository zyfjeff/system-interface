#include <stdio.h>
#include <unistd.h>
#include <unistd.h>
#include <sys/types.h>

//不修改文件偏移量，文件当前长度大于length的时候，丢弃超出部分，小于length的时候在文件尾部添加一系列
//空字节或是一个文件空洞
int truncate(const char *path, off_t length);
int ftruncate(int fd, off_t length);

int main()
{

}
