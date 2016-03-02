#include <unistd.h>
/*  调整堆的大小，malloc和free的内部就是使用brk sbrk实现
 *  malloc(0) 会分配一小块可以用free释放的内存
 *  sbrk(0) 返回当前program break的位置，
 *  brk 设置当前的program break为addr
 *
 *  malloc会利用sbrk申请一段内存，然后通过链表进行管理，此后free并不是通过调整program break来完成
 *  除非在堆顶空闲内存足够大的时候，free函数才会调用sbrk来降低program break的地址
 *
 *  void *calloc(size_t nmemb, size_t size);
 *  void *realloc(void *ptr, size_t size);
 *
 *
 *  #include <malloc.h>
 *  int mallopt(int param, int value);
 *  调整malloc的分配参数和算法
 *
 */
/*
       #include <malloc.h>
       struct mallinfo mallinfo(void);
       返回malloc分配内存的各种统计数据

*/
// mallinfo mallopt这类函数不同的unix有不同的版本，因此不具备可移植性

           struct mallinfo {
               int arena;     /* Non-mmapped space allocated (bytes) */
               int ordblks;   /* Number of free chunks */
               int smblks;    /* Number of free fastbin blocks */
               int hblks;     /* Number of mmapped regions */
               int hblkhd;    /* Space allocated in mmapped regions (bytes) */
               int usmblks;   /* Maximum total allocated space (bytes) */
               int fsmblks;   /* Space in freed fastbin blocks (bytes) */
               int uordblks;  /* Total allocated space (bytes) */
               int fordblks;  /* Total free space (bytes) */
               int keepcost;  /* Top-most, releasable space (bytes) */
           };


int brk(void *addr);
void *sbrk(intptr_t increment);

