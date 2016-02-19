#include <stdio.h>
#include <features.h>

/*
 *  _POSIX_SOURCE 被 _POSIX_C_SOURCE 取代
 *  _POSIX_C_SOURCE 可选很多值，不同的值对应不用的POSIX标准，会开启很多对标准支持的扩展
 *  _XOPEN_SOURCE
 *  _BSD_SOURCE     BSD定义
 *  _SVID_SOURCE    System V接口规范的定义
 *  _GNU_SOURCE     GNU扩展定义
 *  更详细的信息参见 <features.h> 头文件和 feature_test_macros(7)手册页
 *  1.系统定义的数据结构，不同系统其定义顺序是不同的，因此在使用的时候需要注意这个问题．
 */
