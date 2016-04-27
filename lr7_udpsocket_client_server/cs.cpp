#include <time.h>
#include <signal.h>
#include <unistd.h>
#include "cs.h"

static bool run_server = true;

static void stop_server(int signo) {
    if (signo == SIGALRM) {
        run_server = false;
    }
}

void server() {
    printf("server start\n");

    int sock;
    struct sockaddr_in addr;
    int bytes_read;

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    if (sock < 0) {
        perror("socket failure!");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        perror("bind");
        exit(1);
    }

    signal(SIGALRM, stop_server);
    alarm(TIME_OUT_SERVER);

    while (run_server) {
        recv_numbers(sock, addr);
    }
    
    alarm(0);

    printf("server finished\n");
}

void client() {
    printf("client start\n");

    int sock;
    struct sockaddr_in addr;

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    if (sock < 0) {
        perror("socket() failure!\n");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    send_numbers(sock, addr);

    close(sock);
    printf("client finished\n");
}


void recv_numbers(int socket, struct sockaddr_in addr) {
    char number_str[MAX_LEN_NUMBER];

    recvfrom(socket, number_str, MAX_LEN_NUMBER * sizeof(char), 0, NULL, NULL);
    printf("read %s\n", number_str);
    int a = atoi( number_str );

    recvfrom(socket, number_str, MAX_LEN_NUMBER * sizeof(char), 0, NULL, NULL);
    printf("read %s\n", number_str);
    int b = atoi(number_str);

    char result[MAX_LEN_NUMBER + 1];
    sprintf(result, "%d", a + b);
    printf("result = %s\n\n", result);
}

void send_numbers(int socket, struct sockaddr_in addr) {
    srand((unsigned int) time(NULL));

    char number_str[MAX_LEN_NUMBER];
    int number_int;

    number_int = rand() % 100;
    sprintf(number_str, "%d", number_int);
    sendto(socket, number_str, MAX_LEN_NUMBER * sizeof(char), 0, (struct sockaddr *) &addr, sizeof(addr));
    printf("sent %s\n", number_str);

    number_int = rand() % 100;
    sprintf(number_str, "%d", number_int);
    sendto(socket, number_str, MAX_LEN_NUMBER * sizeof(char), 0, (struct sockaddr *) &addr, sizeof(addr));
    printf("sent %s\n", number_str);
}
