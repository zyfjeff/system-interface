#include <stdio.h>



void clearerr(FILE *stream);
int feof(FILE *stream);
int ferror(FILE *stream);

/*  得到库函数IO底层对应的文件描述符fd
 *
 */
int fileno(FILE *stream);

/*
 *  将fd,转换为库函数io
 */
FILE *fdopen(int fd, const char *mode);
FILE *fopen(const char *path, const char *mode);
FILE *freopen(const char *path, const char *mode, FILE *stream);

//库函数io有应用层缓冲,系统调用IO,则没有,两者交换使用的时候需要考虑应用层缓冲,
//通过使用setvbuf setbuf fflush等函数避免应用层缓冲问题.

