#include "server.h"
#include <stdio.h>

void wserver_init(wserver* self, int port) {
    self->serv_addr.sin_family = AF_INET;
    self->serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    self->serv_addr.sin_port = htons(port); 

    self->listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (bind(self->listenfd, (struct sockaddr*)&self->serv_addr, sizeof(self->serv_addr))) {
        printf("Error: %d\n", WSAGetLastError());
    }
}

void wserver_finalize(wserver* self) {
    closesocket(self->listenfd);
}

void wserver_listen(wserver* self) {
    int connfd, ticks;
    char sendBuff[1025];

    listen(self->listenfd, 100);

    while (1) {
        connfd = accept(self->listenfd, (struct sockaddr*)NULL, NULL); 

        ticks = time(NULL);
        snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));
        write(connfd, sendBuff, strlen(sendBuff)); 

        close(connfd);
        sleep(1);
   }
}
