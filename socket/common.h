#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define EXIT_ERR(msg) do{           \
    perror(msg);                    \
    exit(EXIT_FAILURE);             \
}while(0)
