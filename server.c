#include "server.h"

int launch() {

    printf("launch started...\n");

    struct addrinfo **res;
    struct addrinfo *hints;
    const char *HOST = "127.0.0.1";
    const char *PORT = "3005";

    printf("variables initialized...\n");

    hints->ai_family = AF_UNSPEC;
    hints->ai_socktype = SOCK_STREAM;
    hints->ai_protocol = 0;
    hints->ai_flags = AI_PASSIVE;

    printf("hints are specified\n");
    
    if (getaddrinfo(HOST, PORT, hints, res) != 0) {
        printf("getaddrinfo failed\n");
        return 1;
    }

    printf("Hello World\n");
    return 0;
}