#define __GUNC__
#include <stdlib.h>
#include <alloca.h>

/*
 *
 *  #include <alloca.h>
 *  void *alloca(size_t size);
 *  不能再一个函数的参数列表中调用alloca
 *  func(x,alloca(size),z); 这会是的alloca分配的空间在函数参数的堆栈空间
 *
 */
