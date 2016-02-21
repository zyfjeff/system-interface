#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>

#define EXIT_ERR(msg) do{           \
    perror(msg);                    \
    exit(EXIT_FAILURE);             \
}while(0)                           \

int main()
{
    //protocol值通常为0，但是如果socket类型变成SOCK_RAW，那么protocol的值就是IPPROTO_RAW了
    //可直接通过与上SOCK_CLOEXEC和SOCK_NONBLOCK 来实现所谓的close-on-exec功能和非阻塞socket
    int fd = socket(AF_INET,SOCK_STREAM|SOCK_CLOEXEC|SOCK_NONBLOCK,0);
    //int fd = socket(AF_INET,SOCK_RAW,IPPROTO_RAW);
    //int fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd == -1) EXIT_ERR("create socker failure");
    //int bind(int sockfd, const struct sockaddr *addr,socklen_t addrlen);
    //不同的socket要绑定的地址类型都不一样，AF_UNIX，绑定的地址是一个unix socket路径
    //而AF_INET，则是端口和ip，因此为了屏蔽这些结构的不同搞了一个统一的结构体sockaddr
    //  struct sockaddr {
    //      sa_family_t sa_family;
    //      char        sa_data[14];
    //  }
    //
    //listen 总的backlog表示未决链接的数量，可以在运行时通过/proc/sys/net/core/somaxconn来调整
    //getsockname 获取已经bind的socket的struct sockaddr_t
    //getpeername 用于获取对端的socket的struct sockaddr_t
    //accept4　可以接一个额外的参数flags，用于在返回的socket上启用SOCK_CLOEXEC和SOCK_NONBLOCK等功能
    //需要开启_GNU_SOURCES

    //如果connect连接失败，并且希望重新连接，可移植的方法是关闭socket，创建一个新socket，在这个新的socket上重新链接

    //两端建立连接，其中一端发送数据然后断开链接，另外一端第一次将接收完数据，当再次接收的时候会返回0
    //另外一端写数据的时候，第一次写可以写成功，但是会导致对端响应一个RST报文将链接重置，当再次写数据的时候
    //会产生SIGPIPE信号．
    //
    //close关闭sock描述符，但是因为sock描述符是引用计数机制控制的，因此只有当最后一个sock描述符被close的时候才会
    //真正导致socet描述符被关闭，内核发送FIN报文到对端进入FIN-WAIN1，称为主动关闭方方，对端响应ACK报文，然后主动关闭方进入
    //FIN-WAIN2.
    //
    //shutdown系统调用可以更精细的控制关闭

    //connect系统调用导致内核给套接字设置对端地址信息，通过再次发起connect调用可以修改已连接的数据报socket的对等socket信息
    //
    //
    ////proc/sys/net/ipv4/ip_local_port_range　设定动态端口范围
}
