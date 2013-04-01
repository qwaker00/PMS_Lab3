#include "wserver.h"
#include <stdio.h>
#include <pthread.h>

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
#ifdef _DEBUG
    fprintf(stderr, "Started server at port %d\n", port);
#endif
}

void wserver_finalize(wserver* self)
{
    close(self->listenfd);
}

void wserver_stop(wserver* self)
{
    self->running = FALSE;
}

void wserver_new_task(wserver* self, int connfd) {
    int* param;
    param = malloc(sizeof(int));
    *param = connfd;

#ifdef _MULTIPROCESS
    int pid = fork();
    if (pid < 0) {
        handle_error("Create process failed");
    }
    if (pid == 0) {
        close(self->listenfd);
        self->handler(param);
        exit(0);
    } else {
        close(connfd);
    }
#else    
    pthread_attr_t attr;
    pthread_t tid;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    if (pthread_create(&tid, &attr, self->handler, param)) {
        handle_error("Create thread failed");
    }
#endif    
}

void wserver_listen(wserver* self)
{
    int connfd;
    socklen_t client_len;
    struct sockaddr_in client_addr;

    listen(self->listenfd, 100);
    self->running = TRUE;
    while (self->running)
    {        
        client_len = sizeof(client_addr);
        connfd = accept(self->listenfd, (struct sockaddr *)&client_addr, &client_len);

#ifdef _DEBUG
        fprintf(stderr, "Client %s:%d connected\n", inet_ntoa(client_addr.sin_addr), client_addr.sin_port);
#endif

        wserver_new_task(self, connfd);
        sleep(1);
    }
}

