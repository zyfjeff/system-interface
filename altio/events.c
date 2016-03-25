#include<poll.h>

/*
 *  POLLIN  可读取非高优先级的数据
 *  POLLRDNORM  等同于POLLIN
 *  POLLRDBAND  可读优先级数据(linux中不适用)
 *  POLLPRI     可读取高优先级数据
 *  POLLRDHUP   对端套接字关闭
 *
 *  POLLOUT     普通数据可写
 *  POLLWRNOR   等同于POLLOUT
 *  POLLWRBAND  优先级数据可写入
 *
 *  POLLERR     有错误发生
 *  POLLHUP     出现挂断
 *  POLLNVAL    文件描述符未打开
 *
 *  POLLMSG     linux中不使用
 *
 *
 *
 */
