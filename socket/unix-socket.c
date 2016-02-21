#include "common.h"
#include <string.h>
#include <sys/un.h>
int main()
{
    const char *SOCKNAME= "/tmp/mysock";
    int sfd;
    struct sockaddr_un addr;
    sfd = socket(AF_UNIX,SOCK_STREAM,0);
    if(sfd == -1)
        EXIT_ERR("create socket");

    memset(&addr,0,sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    //strncpy(addr.sun_path,SOCKNAME,sizeof(addr.sun_path) - 1);
    strncpy(&addr.sun_path[1],"abstract_name",sizeof(addr.sun_path) - 1);
    if(bind(sfd,(struct sockaddr *)&addr,sizeof(struct sockaddr_un)) == -1)
        EXIT_ERR("bind socket");
//无法将socket绑定到一个存在的路径名中，这样bind会失败并返回EADDRINUSE错误
//一个socket只能绑定到一个路径名上，相应的，一个路径名只能被一个socket绑定
//无法使用open打开一个socket
//当不再需要一个socket时，可以使用unlink或者remove删除其unix socket文件即可
//对于数据报来说，其可以发送的最大数据可以通过setsockopt中的SO_SNDBUF选项来控制
//也可以通过/proc/sys/net/core/wmem_default　和 /proc/sys/net/core/wmem_max来控制
//要连接一个UNIX domain流socket需要在该socket文件上拥有写权限
//要通过一个UNIX domain数据报socket发送一个数据报需要在该socket文件上拥有写权限
//此外还需要在存放socket路径名的所有目录上都拥有执行(搜索)权限

//1.无序担心与文件系统中既有的名字发生冲突
//2.没有必要在使用完socket之后删除socket路径名,当socket被关闭之后会自动删除抽象名
//3.无序为socket创建一个文件系统路径名了

//如何创建一个抽象绑定:第一个字节为null,余下的字节为抽象名字
}
