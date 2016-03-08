#include <stdio.h>
#include <stdlib.h>


/*
 *  setvbuf用来设置缓冲类型,是行缓冲,还是全缓冲,还是无缓冲
 *  mode:
 *      _IONBUF 无缓冲
 *      _IOLBUF 行缓冲
 *      _IOFBUF 全缓冲
 *  setbuf 等同于setvbuf(stream,buf,(buf != NULL)?_IOFBUF:_IONBF,BUFSIZ); //使用默认的BUFSIZ
 *
 *  setbuffer SUSv3并未对这个函数加以定义,但大多数UNIX实现均支持它,需要定义#define_BSD_SOURCE
 *  setvbuf(fp,buf,(buf!=NULL)?_IOFBUF:_IONBF,size);
 *
 *  fflush 刷新stdio缓冲区,如果stream为空,那么就刷新所有缓冲区,关闭一个流的时候,也会自动刷新其stdio缓冲区
 *
 *
 *  如果打开一个流同时用于输入和输出 ,则C99标准提出了两项要求:
 *  1.一个输出操作不能紧跟一个输入操作,必须在两者之间调用fflush函数,或是一个文件定位函数
 *  2.一个输入操作不能紧跟一个输出操作,必须再两者之间调用一次文件定位函数,除非输入操作遭遇到文件结尾
 *
 */
       void setbuf(FILE *stream, char *buf);
       void setbuffer(FILE *stream, char *buf, size_t size);
       void setlinebuf(FILE *stream);
       int setvbuf(FILE *stream, char *buf, int mode, size_t size);
       int fflush(FILE *stream);


int main()
{

}
