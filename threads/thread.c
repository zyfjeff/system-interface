#include <stdio.h>

/*
 *  pthreads数据类型:
 *  pthread_t               线程ID
 *  pthread_mutex_t         互斥对象
 *  pthread_mutexattr_t     互斥属性对象
 *  pthread_cond_t          条件变量
 *  pthread_condattr_t      条件变量的属性对象
 *  pthread_key_t           线程特有数据的键
 *  pthread_once_t          一次性初始化控制上下文
 *  pthread_attr_t          线程属性对象
 *
 *  SUSv3并未规定如何实现这些数据类型，可移植的程序应将其视为"不透明"数据，不能使用C语言的==去比较这些类型的变量
 *  多线程程序中每个线程都有自己的errno，多线程环境下errno是一个宏，是一个指向返回int *的函数
 *
 *  pthreads API都是返回0表示成功，返回一个正值表示失败。
 *
 *  终止线程:
 *      1.线程star函数执行return语句并返回指定值
 *      2.线程调用pthread_exit
 *      3.调用pthread_cancel取消线程
 *      4.任意线程调用exit，或者主线程执行了return语句,都会导致进程中的所有线程立即终止
 *
 *  pthread_exit函数将终止调用线程，且返回值可由另一个线程通过调用pthread_join获取　等同于线程中执行return
 *
 *  主线程指向了pthread_exit，那么其他线程将继续运行
 *
 *  pthread_t 类型的线程ID是POSIX线程库分配的线程ID，一个POSIX线程对应与内核一个内核线程，通过gettid可以得到内核线程的ID
 *  线程未分离就必须使用pthread_join来进行连接，如果未能连接，那么线程终止时就将产生僵尸线程。
 *
 *  线程之间的关系是对等的，任何线程都可以调用pthread_join来等待其他线程。
 *  pthread_deatch 线程可以自行分离，一旦线程处于分离状态，就不能再使用pthread_join来获取其状态,也无法时期重返可连接的状态
 *  其他线程exit或是主线程执行return即便遭到分离的线程也还是会受到影响。此时不管线程处于可连接状态还是已分离状态，进程的所有线程
 *  都会立即终止。
 *
 *  线程VS进程:
 *  1.线程间数据共享简单，进程间的数据共享需要更多的投入(共享内存，管道等)
 *  2.创建线程要快于创建进程，线程间的上下文切换，其消耗时间一般比进程要短
 *
 *  1.多线程编程 需要确保调用线程安全的函数，或者按照线程安全的方式来调用函数
 *  2.某个线程的bug可能危机该进程的所有线程
 *  3.每个线程都在争用宿主进程中有限的虚拟地址空间
 *  4.多线程应用处理信号，需要小心设计，作为通则，一般建议在多线程程序中，避免使用信号
 *  5.多线程应用中，所有线程必须运行同一个车光绪
 *  6.除了数据，线程还可以共享某些其他信息(例如: 文件描述符，信号处置，当前工作目录，用户ID和组ID
 *
 *  互斥锁仅仅是一种建议锁，而非强制。线程可以考虑不使用互斥量，而仅访问相应的共享变量，为了安全地处理共享变量，所有线程
 *  在使用互斥量时必须互相协调，遵守既定的锁定规则。
 *
 *  可以静态分配，也可以动态创建
 *  pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER  静态初始化只能用于经由动态分配且携带默认属性的互斥量
 *  如果需要通过pthread_mutexatrr_t来指定mutex的属性，则需要使用动态创建初始化，静态初始化的互斥量无序pthread_mutex_destroy
 *  经由pthread_mutex_destroy销毁的互斥量，可调用pthread_mutex_init对其重新初始化
 *
 *  互斥量死锁问题:
 *      一个线程需要同时访问两个或者更多不同的共享资源，而每个资源又都由不同对的互斥量管理,这将导致死锁的可能
 *      为了避免此类死锁问题，最简单的方法就是定义互斥量的层级关系。
 *
 *  互斥量的类型:
 *  PTHREAD_MUTEX_NORMAL    不具有死锁检测的功能，试图对已由自己锁定的互斥量加锁，则发生死锁，互斥量处于未锁定状态下，
 *  或者已由其他线程锁定，对其解锁会导致不确定的结果。
 *
 *  PTHREAD_MUTEX_ERRORCHECK    对此类互斥量的所有操作都会执行错误检查
 *
 *  PTHREAD_MUTEX_RECURSIVE 地柜互斥量维护有一个锁计数器，当线程第一次取得互斥量就将锁计数器置1,后续由同一个线程执行
 *  的每次加锁操作都会递增计数器的数值，而解锁操作则递减计数器计数。只有当锁计数器值降到0时，才会释放该互斥量。
 *  PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP
 *
 *  条件变量:
 *      互斥量防止多个线程同时访问同一个共享变量，条件变量允许一个线程就某个共享变量的状态变化通知其他线程，并让其他线程
 *      等待这一通知。条件变量总是结合互斥量使用，条件变量就共享变量的状态改变发出通知，而互斥量则提供对该共享变量访问的互斥
 *  条件变量的分配也有静态和动态之分，静态初始化为PTHREAD_COND_INITALIZER
*
*  pthread_cond_signal和pthread_cond_broadcast之间的差别，而这对阻塞于pthread_cond_wait的多个线程处理方式不同，pthread_cond_signal
*  只保证唤醒至少一条遭到阻塞的线程，而pthread_cond_broadcast则会唤醒所有遭到阻塞的线程
*
*  pthread_cond_signal 用于所有线程执行完全相同的任务，基于这些假设，pthread_cond_signal比pthread_cond_broadcast更有效率
*  pthread_cond_broadcast锁处理的情况是，处于等待状态的所有线程执行的任务不同(判定条件不同)
*　
*  用条件变量实现生产者-消费者模型:
*
*  生产者代码:
*  static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
*  static pthread_cond_t cond = PTHREAD_MUTEX_INITIALIZER;
*  static int avail = 0;
*  s = pthread_mutex_lock(&mtx);
*  if(s != 0)
*       errExitEN(s,"pthread_mutex_lock");
*  avail++;
*  s = pthread_mutex_unlock(&tmx);
*  s = pthread_cond_signal(&cond);      //这里的通知可以放到互斥代码中，也可以放在解锁后
*  if(s != 0)
*       errExitEN(s,"pthread_cond_signal");
*
*   在某些实现中，先解互斥量再通知条件变量可能比反序指向效率更高，如果仅在发出条件变量信号后才解锁，那么可能会导致
*   线程被唤醒但是还未解锁，导致cond_wait唤醒后发现还未解锁便再次休眠，导致多余的上下文切换。
*
* 消费者代码:
*for(;;) {
*   s = pthread_mutex_lock(&mtx)
*   if(s != 0)
*       errExitEN(s,"pthread_mutex_lock");
*
*   while(avail == 0) {             //Wait for something to consume,这里必须是while循环，避免虚假唤醒
*       s = pthread_cond_wait(&cond,&mtx);      //cond_wait时会被解锁，
*       if(s != 0)
*           errExitEN(s,"pthread_cond_wait")
*   }
*
*   while(avail > 0) {
*       avail--;
*   }
*   s = pthread_mutex_unlcok(&mtx)
*   if(s != 0)
*       errExitEN(s,"pthread_mutex_unlock")
*}
*
*   这里使用while而不是if，其原因如下:
*   1.其它线程可能率先醒来
*   2.虚假唤醒
*
*   线程安全:　若函数可同时提供多个线程安全的调用就是线程安全函数，通常通过互斥量来使非线程安全变成线程安全
*   可重入: 可重入函数是线程安全函数，但是不需要借助互斥量，通过避免去使用一些全局和静态的数据
*   malloc是线程安全的，但是不可重入，需要访问堆上的全局链表，因为是加锁访问的，所以是线程安全的
*
*   线程特有数据:
*       每个调用线程分别维护一份变量的副本
*       线程特有数据的实现限制，最多PTHREAD_KEY_MAX个键
*
*   线程局部存储，比线程特有数据更简单，要创建线程局部变量只需要简单的在全局或静态变量的声明中包含__thread说明符即可
*   static __thread buf[MAX_ERROR_LEN] 但凡含有__thread这种说明符的变量，每个线程都拥有一份对变量的拷贝
*
*   线程局部变量的声明和使用，需要注意以下几点:
*   1.如果变量声明中使用关键字static和extern，那么关键字__thread必须紧随其后
*   2.与一般的全局或静态变量声明一样，线程局部变量在声明时，可设置一个初始值
*   3.可以使用C语言取址操作符，来获取线程局部变量的地址
*
*   pthread_attr_setstacksize 设置线程属性，设定线程栈的大小
*   pthread_attr_setstack 可以同时控制线程栈的大小和位置
*   通过减少线程栈大小，以便让应用程序创建更多的线程
*
*   UNIX信号模型，是基于UNIX进程模型而设计的，问世比Pthreads要早几十年,自然而然信号与线程模型之间存在一些明显冲突
*   下面是信号模型在线程模型下的注意事项:
*   * 信号动作应该是属于进程层面 任一线程收到未经特殊处理的信号，其缺省动作就是stop或terminate
*   * 信号的处置是属于进程层面，所有线程共享对信号的处置设置
*   * 信号的发送，可以针对整个进程，也可以针对某个特定线程,下面三种情况是面向线程的:
*       1.信号的产生源于线程上下文中对特定硬件指令的指向,如SIGBUS SIGFPE SIGILL SIGSEGV
*       2.当线程试图对已断开的管道进行写操作时，所产生的SIGPIPE信号
*       3.由函数pthread_kill pthread_sigqueue发出的信号，这个函数允许线程向同一进程下的其他线程发送信号
*       由其他机制产生的信号都是面向进程的
*   * 信号掩码是针对每个线程而言的
*   * 多线程程序收到信号，内核会任选一个线程来接收这个信号
*   * 信号掩码是针对每个线程而言的
*   * 针对为整个进程挂起的信号，以及每条线程所挂起的信号，内核都分别维护有记录
*   * 备选信号栈是每个线程特有的
*
*   pthread_sigmask 操作线程信号掩码
*   pthread_kill 向线程发送信号，也可以使用pthread_sigqueue 来发送实时信号，附带还可以发送额外的信息
*
*   异步信号的处理:
*       可重入问题，系统调用重启问题，线程安全问题，避免竞争条件 异步信号安全问题，没有任何pthread API是属于异步信号安全的
*       函数，解决的办法就是将异步信号，转换为同步信号。
*   1.主线程阻塞进程可能接收到的所有异步信号，后续创建的每个线程都会继承主线程信号掩码的一份拷贝
*   2.再创建一个专用线程，调用函数sigwaitinfo sigtimedwait sigwait来接收收到的信号
*
*   exec fork exit的问世都早于pthread API
*   线程和exec():
*   1.只要任一线程调用exec系列函数，调用程序将被完全替换，除了调用exec的线程之外,其他线程都立即消失
*   2.没有任何线程会对线程特有数据指向解构，也不会调用清理函数
*   3.进程的所有互斥量和条件变量都会消失，调用exec后，调用线程的线程ID是不确定的
*
*   线程和fork()
*   1.进会将发起调用的线程复制到子进程中，子进程中该线程的线程ID保持不变
*   2.也不会调用清理函数和针对线程特有数据的解构函数，这将导致一些问题:
*
*       1.虽然只将发起调用的线程复制到子进程中，但是全局变量的状态以及所有的pthread对象(互斥量和条件变量)都会在子进程中保留
*         会存在互斥量锁住的问题，子进程的全局数据结构处于不一致的状态等问题
*       2.因为并未执行清理函数，多线程程序对的fork会导致子进程的内存泄露等问题
*   推荐做法就是fork后立即执行exec，这将导致子进程的所有pthreads 对象消失
*   除此之外你可以借助pthread_atfork来创建fork处理函数，
*
*   int pthread_atfork(void (*prepare)(void), void (*parent)(void), void (*child)(void));
*   每一次pthread_atfork都会将prepare添加到一个函数列表，在fork调用之前会自动执行该函数列表中的函数，，
*   同理也会将parent和child添加到一个函数列表中，在fork返回前，将分别在父子进程中自动运行
*
*   线程和exit()
*   如果任何线程调用exit，或者主线程执行了return，那么所有线程都将消失,也不会执行线程特有数据的解构函数以及清理函数
*/


int main()
{

}
