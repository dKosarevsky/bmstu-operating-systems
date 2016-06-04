#ifndef LR7_UDPSOCKET_CS_H
#define LR7_UDPSOCKET_CS_H

#include <netinet/in.h>
#include <cstdio>
#include <cstdlib>

#define PORT 8888
#define TIME_OUT_SERVER 10
#define MAX_LEN_NUMBER 3


static void stop_server(int);

void server();
void client();

void send_numbers(int socket, struct sockaddr_in addr);
void recv_numbers(int socket, struct sockaddr_in addr);

#endif //LR7_UDPSOCKET_CS_H
