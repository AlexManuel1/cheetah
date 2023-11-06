#ifndef FOO_H_
#define FOO_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>

int launch();
void printIPAddress(const struct sockaddr *addr);

#endif