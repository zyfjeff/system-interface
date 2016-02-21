#include "common.h"
#include <netdb.h>
//二进制和人类可读的形式之间转换IPv4 IPv6地址
//inet_ntop 将二进制转换人类可读的字符串
//inet_pton 将字符串转换为二进制网络地址
//支持ipv4和ipv6
//getaddrinfo 给定一个主机名返回对应的二进制ip地址结构和端口号结构
//getnameinfo 将一个ip地址和端口号，转换为对应的主机名和服务名
//
//废弃的API
//inet_aton inet_ntoa(只支持ipv4)
//
//主机和服务名与二进制形式之间的转换
//早期代码中被广泛使用，但是现在已经过时了，改用getaddrinfo和getnameinfo来转换
//gethostbyname getserverbyname
//
//
//需要开启_GNU_SOURCE
//NI_MAXHOST 主机名字符串中的最大字节数 取值为1025
//NI_MAXSERV 服务名字符串的最大字节数 取值为32

int main()
{


}
