#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <pthread.h>

#define BUFFSIZE 2048
#define PORTA_PADRAO 10101

extern pthread_t tlkSrv_thread, lstSrv_thread;
extern pthread_t tlkClt_thread, lstClt_thread;

extern int porta;

extern char hello_clt[10];
extern char hello_srv[10];
extern char bye_srv[10];
extern char bye_clt[10];

void cliente();
void servidor();
