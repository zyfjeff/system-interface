#include "common.h"
#include <string.h>

/*
 *  INADDR_ANT  INADDR_LOOPBACK 两个常量，用于表示0.0.0.0和127.0.0.1两个地址
 *  INET_ADDRSTRLEN
 *
 */
int main()
{
    char *src_ip = "192.168.23.1";
    struct in_addr toip;
    int ret = inet_pton(AF_INET, src_ip, &toip);
    if(ret == 1) {
        printf("addr is:%p\n",toip.s_addr);
    }
    char ipbuf[4096];
    memset(ipbuf,0,sizeof(ipbuf));
    printf("ip:%s\n",inet_ntop(AF_INET, &toip,ipbuf,INET_ADDRSTRLEN));
}
