#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/socket.h>

//void toUpperCaseChild(int socket) {
//    char buf; /* for data exchange between processes */
//
//    read(socket, &buf, 1);
//    printf("child: read '%c'\n", buf);
//
//    while (buf != '0') {
//        buf = (char) toupper(buf);  /* make it uppercase */
//        write(socket, &buf, 1);
//        printf("child: sent '%c'\n", buf);
//        read(socket, &buf, 1);
//        printf("child: read '%c'\n", buf);
//    }
//}
//
//void toUpperCaseParent(int socket) {
//    char buf; /* for data exchange between processes */
//
//    for (char sym = 'a'; sym <= 'z'; ++sym) {
//        write(socket, &sym, 1);
//        printf("\t\t\t\tparent: sent %c\n", sym);
//        read(socket, &buf, 1);
//        printf("\t\t\t\tparent: read '%c'\n", buf);
//    }
//    write(socket, "0", 1);
//    printf("\t\t\t\tparent: sent \"0\"\n");
//
//    wait(); /* wait for child to die */
//}

#define MAX_LEN_NUMBER 3

void culcChild(int socket) {
    char number_str[MAX_LEN_NUMBER];

    read(socket, number_str, MAX_LEN_NUMBER * sizeof(char));
    printf("child: read %s\n", number_str);
    int a = atoi( number_str );

    read(socket, number_str, MAX_LEN_NUMBER * sizeof(char));
    printf("child: read %s\n", number_str);
    int b = atoi(number_str);

    char result[MAX_LEN_NUMBER + 1];
    sprintf(result, "%d", a + b);

    write(socket, result, (MAX_LEN_NUMBER + 1) * sizeof(char));
    printf("child: sent %s\n", result);
}

void culcParent(int socket) {
    srand((unsigned int) time(NULL));

    char number_str[MAX_LEN_NUMBER];
    int number_int;

    number_int = rand() % 100;
    sprintf(number_str, "%d", number_int);
    write(socket, number_str, MAX_LEN_NUMBER * sizeof(char));
    printf("\t\t\t\tparent: sent %s\n", number_str);

    number_int = rand() % 100;
    sprintf(number_str, "%d", number_int);
    write(socket, number_str, MAX_LEN_NUMBER * sizeof(char));
    printf("\t\t\t\tparent: sent %s\n", number_str);

    char result[MAX_LEN_NUMBER + 1];
    read(socket, result, (MAX_LEN_NUMBER + 1) * sizeof(char));
    printf("\t\t\t\tparent: read %s\n", result);

    wait();
}


int main(void) {
    int sv[2];

    if (socketpair(AF_UNIX, SOCK_DGRAM, 0, sv) == -1) {
        perror("socketpair");
        exit(1);
    }

    if (!fork()) {  /* child */
        culcChild(sv[0]);
    } else { /* parent */
        culcParent(sv[1]);
    }
}