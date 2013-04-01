#include "server.h"
#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define handle_error(msg)  do { perror(msg); exit(EXIT_FAILURE); } while (0)

void wserver_init(wserver* self, int port, client_handler handler)
{
    self->serv_addr.sin_family = AF_INET;
    self->serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    self->serv_addr.sin_port = htons(port); 
    self->handler = handler;

    self->listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (self->listenfd < 0) {
        handle_error("Creation socket error");
    }
    if (bind(self->listenfd, (struct sockaddr*)&self->serv_addr, sizeof(self->serv_addr))) {
        handle_error("Bind error");
    }
}

void wserver_finalize(wserver* self)
{
    close(self->listenfd);
}

void wserver_stop(wserver* self)
{
    self->running = FALSE;
}

void wserver_listen(wserver* self)
{
    int connfd;
    listen(self->listenfd, 100);
    self->running = TRUE;
    while (self->running)
    {
        connfd = accept(self->listenfd, (struct sockaddr*)NULL, NULL);
        self->handler(connfd);
        sleep(1);
    }
}

