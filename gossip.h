#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h> 

#define BUFFSIZE 2048
#define PORTA_INICIAL_REMOTA 1500

void cliente(int porta);

void servidor(int porta);
