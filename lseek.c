#include <stdio.h>

/*
 *  lseek调用知识调整内核中与文件描述符相关的文件偏移量记录,并没有引起对任何物理设备的访问，
 *  lseek不适用与管道，FIFO,socket，终端等，一旦使用会发生调用失败，设置errno为ESPIPE
 *
 *  使用lseek实现文件空洞
 *
 *
 */
