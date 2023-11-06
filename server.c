#include "server.h"

void printIPAddress(const struct sockaddr *addr) {
    if (addr->sa_family == AF_INET) {
        const struct sockaddr_in *addr_in = (const struct sockaddr_in *)addr;
        char ipAddress[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(addr_in->sin_addr), ipAddress, INET_ADDRSTRLEN);
        printf("IPv4 Address: %s\n", ipAddress);
    } else if (addr->sa_family == AF_INET6) {
        const struct sockaddr_in6 *addr_in6 = (const struct sockaddr_in6 *)addr;
        char ipAddress[INET6_ADDRSTRLEN];
        inet_ntop(AF_INET6, &(addr_in6->sin6_addr), ipAddress, INET6_ADDRSTRLEN);
        printf("IPv6 Address: %s\n", ipAddress);
    } else {
        printf("Unknown address family\n");
    }
}

int launch() {

    printf("launch started...\n");

    struct addrinfo *res;
    struct addrinfo hints; 
    struct sockaddr client_addr;
    int socketFD;
    socklen_t client_addr_size = sizeof(struct sockaddr);
    const int BACKLOG = 10;
    const char *HOST = "127.0.0.1";
    const char *PORT = "3005";
    char *responseMsg = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
    int responseMsgLen = strlen(responseMsg);

    printf("variables initialized...\n");

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = 0;
    hints.ai_flags = AI_PASSIVE;

    printf("hints are specified\n");
    
    if (getaddrinfo(HOST, PORT, &hints, &res) != 0) {
        printf("getaddrinfo failed\n");
        return 1;
    }

    printf("Successfully implemented getaddrinfo\n");

    for (struct addrinfo *rp = res; rp != NULL; rp=res->ai_next) {
        printf("ai_family: %d\n", rp->ai_family);
        printf("ai_socktype: %d\n", rp->ai_socktype);
        printf("ai_protocol: %d\n", rp->ai_protocol);
        printf("ai_next: %p\n", rp->ai_next);

        socketFD = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);

        if (socketFD == -1) {
            printf("Socket assignment failed\n");
            return 1;
        }

        printf("Socket assigned successfully. Socket: %d\n", socketFD);

        if (bind(socketFD, rp->ai_addr, rp->ai_addrlen) != 0) {
            printf("Port assignment failed\n");
            return 1;
        }

        printf("Port assigned successfully\n");

    }

    while (1) {
        if (listen(socketFD, BACKLOG) != 0) {
            printf("Listening failed\n");
            return 1;
        }
        printf("Listening at socket file descriptor: %d\n", socketFD);
        int acceptFD = accept(socketFD, &client_addr, &client_addr_size);
        if (acceptFD < 0) {
            printf("accept failed\n");
            return 1;
        }
        printf("Successfully accepted newest request at FD: %d\n", acceptFD);
        printIPAddress(&client_addr);

        printf("\nmessage to send: \"%s\"\n\nMsg length: %d\n", responseMsg, responseMsgLen);
        int bytesSent = send(acceptFD, responseMsg, responseMsgLen, 0);
        printf("message sent: %d\n", bytesSent);
    }

    return 0;
}