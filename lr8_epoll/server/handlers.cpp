//
// Created by ilyaps on 27.04.16.
//

#include <fcntl.h>
#include <cstdio>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <errno.h>
#include <cstring>
#include "handlers.h"

int setnonblocking(int sock) {
    int opts;

    opts = fcntl(sock,F_GETFL);
    if (opts < 0)
    {
        perror("fcntl(F_GETFL)");
        return -1;
    }
    opts = (opts | O_NONBLOCK);
    if (fcntl(sock,F_SETFL,opts) < 0)
    {
        perror("fcntl(F_SETFL)");
        return -1;
    }

    return 0;
}

void add_client_socket(int server_socket, int epoll) {
    struct sockaddr_in cliaddr;
    socklen_t addr_size = sizeof cliaddr;

    int client_socket = accept(server_socket, (struct sockaddr*) &cliaddr, &addr_size);
    if (client_socket < 0) {
        perror("accept");
        return;
    }

    setnonblocking(client_socket);
    struct epoll_event connev;
    connev.data.fd = client_socket;
    connev.events = EPOLLIN | EPOLLOUT | EPOLLET | EPOLLHUP;
    if (!epoll_ctl(epoll, EPOLL_CTL_ADD, client_socket, &connev) < 0) {
        perror("Epoll fd add");
        close(client_socket);
        return;
    }
}

char *recieve_msg(int socket) {
    char msg[MAX_LEN_MSG];
    recv(socket, msg, MAX_LEN_MSG * sizeof(char), 0);

    printf("read %s\n", msg);
    printf("\tfinish recieve_msg\n");

    return msg;
}

void send_msg(int socket,char * msg) {
    ssize_t n;
    do {
        n = send(socket, strcat(msg, msg), MAX_LEN_MSG * sizeof(char), 0);
//        printf("send %s\n", msg);
    } while (n < 0 && errno == EAGAIN);
    printf("\tfinish recieve_msg\n");
}