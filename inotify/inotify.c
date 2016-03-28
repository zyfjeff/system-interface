
/*
 *  1.先使用inotify_init创建一个inotify实列
 *  2.应用程序使用inotify_add_watch向inotify实例的监控列表添加条目,借此告知内核哪些文件是自己的兴趣所在
 *  3.获得事件通知后，应用程序需要针对inotify文件描述符指向read操作
 *  4.监控结束后关闭inotify描述符
 *
 *  inotify监控机制为非递归的，可以监控文件和目录
 */
#include <sys/inotify.h>
int inotify_init(void);
//支持close-on-exec标志,支IN_NOBLOCK标志
int inotify_init1(int flags);

#include <sys/inotify.h>
//需要对文件有读权限，，后续即使权限发生更改不再具有读权限，任然可以接收到事件通知
//mask是想要监控的事件
int inotify_add_watch(int fd, const char *pathname, uint32_t mask);
//删除监控项，会生成IN_IGNORED事件
int inotify_rm_watch(int fd, int wd);


/*
 *  IN_ACCESS   文件被访问
 *  IN_ATTRIB   文件元数据改变
 *  IN_CLOSE_WRITE  关闭为了写入而打开的文件
 *  IN_CLOSE_NOWRITE    关闭只读方式打开的文件
 *  IN_CREATE   在受监控目录内创建了文件/目录
 *  IN_DELETE   在受监控的目录内删除了文件/目录
 *  IN_DELETE_SELF   删除受监控目录/文件本身
 *  IN_MODIFY   文件被修改
 *  IN_MOVE_SELF    移动受监控目录/文件本身
 *  IN_MOVED_FROM   文件移出到受监控目录之外
 *  IN_MOVED_TO 将文件移入到受监控的目录
 *  IN_OPEN     文件被打开
 *  IN_ALL_EVENTS   以上所有输出
 *  IN_MOVE IN_MOVED_FROM|IN_MOVED_TO 事件的统称
 *  IN_CLOSE IN_CLOSE_WRITE|IN_CLOSE_NOWRITE事件的统称
 *  IN_DONT_FOLLOW  不对符号链接解引用
 *  IN_MASK_ADD 将事件追加到pathname的当前监控掩码
 *  IN_ONESHOT  只监控pathname的一个事件
 *  IN_ONLYDIR  pathname不为目录时会失败
 *  IN_IGNORED  监控项为内核或应用程序所移除
 *  IN_ISDIR    name中所返回的文件名为路径
 *  IN_Q_OVERFLOW    事件队列溢出
 *  IN_UNMOUNT  包含对象的文件系统遭卸载
 *
 */


           struct inotify_event {
               int      wd;       /* Watch descriptor */
               uint32_t mask;     /* Mask describing event */
               uint32_t cookie;   /* Unique cookie associating related
                                     events (for rename(2)) */
               uint32_t len;      /* Size of name field */
               char     name[];   /* Optional null-terminated name */
           };


/*
 *  对inotify事件做队列处理，需要消耗内存，正因为如此，内核对inotify机制的操作施以各种限制
 *  超级用户可配置/proc/sys/fs/inotify路径中的三个文件来调整这些限制
 *
 *  max_queued_events 为inotify实例设置事件数量上限,一旦超出上限生成IN_Q_OVERFLOW事件，并丢弃多余的事件，溢出事件的wd为-1
 *  max_user_instance 每个真实用户ID创建的inotify实例数的限制值
 *  max_user_watches 　对由每个真实用户ID创建的监控项数量的限制值
 *
 */
