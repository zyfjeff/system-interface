#include <stdio.h>
#include <stdlib.h>
/*
 *  提供一个名称模板，最终最后需要以6个XXXXXX字符为结束字符
 *  这6个XXXXXX讲会被替换以保证文件名的唯一性
 *  需要自己调用unlink来删除
 *
 *  tmpfile会在打开文件后从内部立即调用unlink来删除文件名
 */
int mkstemp(char *template);
FILE *tmpfile(void);


int main()
{

}
