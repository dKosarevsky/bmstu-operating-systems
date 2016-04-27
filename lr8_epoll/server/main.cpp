#include <iostream>
#include <netinet/in.h>
#include <unistd.h>

#include <sys/epoll.h>
#include "handlers.h"

#define PORT 8888

#define EPOLL_QUEUE_LEN 10
#define BACK_LOG 10
#define MAX_EPOLL_EVENTS 10


int main() {
    struct sockaddr_in addr;
    int server_socket;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        perror("bind");
        exit(1);
    }

    if (listen(server_socket, BACK_LOG) < 0) {
        perror("Socket listen");
        exit(1);
    }

    setnonblocking(server_socket);

    int epoll = epoll_create(EPOLL_QUEUE_LEN);

    // Добавляем дескриптор в массив ожидания
    struct epoll_event server_event;
    server_event.events = EPOLLIN| EPOLLET;
    server_event.data.fd = server_socket;

    if (epoll_ctl(epoll, EPOLL_CTL_ADD, server_socket, &server_event) < 0) {
        perror("Epoll fd add");
        exit(1);
    }

    struct epoll_event events[MAX_EPOLL_EVENTS];

    bool run = true;
    while (run) {
        printf("\tstart wait\n");
        int nfds = epoll_wait(epoll, events, MAX_EPOLL_EVENTS, -1);

        for (int i = 0; i < nfds; ++i) {
            if (events[i].data.fd == server_socket) {
                printf("\tadd_client_socket\n");
                add_client_socket(server_socket,  epoll);
            } else if (events[i].events & EPOLLIN) {
                printf("\trecieve_msg\n");
                char *msg = recieve_msg(events[i].data.fd);
                send_msg(events[i].data.fd, msg);
                close(events[i].data.fd);
            } else if (events[i].events & EPOLLOUT) {
                printf("\tsend_msg\n");
            }
        }
    }

    close(epoll);
    return 0;
}