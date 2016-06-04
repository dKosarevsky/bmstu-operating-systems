#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <netinet/in.h>
#include <cstdio>
#include <cstdlib>

#define PORT 8888
#define MAX_LEN_MSG 10

void send_msg(int socket) {
    char msg[MAX_LEN_MSG];

    printf("input msg: ");
    scanf("%s", msg);

    send(socket, msg, MAX_LEN_MSG * sizeof(char), 0);
    printf("I sent %s\n", msg);
}

void recieve_msg(int socket) {
    char msg[MAX_LEN_MSG];
	recv(socket, msg, MAX_LEN_MSG * sizeof(char), 0);
	printf("I recieve %s\n", msg);
}

int main(void) {
    srand((unsigned int) time(NULL));

	printf("client start\n");

    int sock;
    struct sockaddr_in addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0) {
        perror("socket() failure!\n");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (connect(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        perror("connect");
        exit(2);
    }

    send_msg(sock);
	recieve_msg(sock);

    close(sock);
    printf("client finished\n");
        
    return 0;
}