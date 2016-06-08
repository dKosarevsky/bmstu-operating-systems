//
// Created by ilyaps on 27.04.16.
//

#ifndef SERVER_HANDLERS_H
#define SERVER_HANDLERS_H

#define MAX_LEN_MSG 10

int setnonblocking(int sock);
void add_client_socket(int server_socket, int epoll) ;
char * recieve_msg(int socket);
void send_msg(int socket, char * msg);


#endif //SERVER_HANDLERS_H
