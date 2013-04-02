#pragma once
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

/*
    Simple WebServer
*/

typedef void* (*client_handler)(void* socket);

typedef struct _wserver {
    struct sockaddr_in serv_addr;
    int listenfd;
    client_handler handler;
    int running;
} wserver;

void wserver_init(wserver* self, int port, client_handler handler);
void wserver_listen(wserver* self);
void wserver_finalize(wserver* self);

