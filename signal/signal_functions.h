#ifndef _SIGNAL_FUNCTION_H_
#define _SIGNAL_FUNCTION_H_

#define _GNU_SOURCE
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void printSigset(FILE *of,const char *prefix,const sigset_t *sigset);
int printSigMask(FILE *of,const char *msg);
int printPendingSigs(FILE *of,const char *msg);

#endif /* _SIGNAL_FUNCTION_H_ */
