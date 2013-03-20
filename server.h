#include <winsock.h>
#include <pthread.h>

/*
    Simple webserver
*/

typedef struct _wserver {
    struct sockaddr_in serv_addr;
    int listenfd;
} wserver;

void wserver_init(wserver* self, int port);
void wserver_listen(wserver* self);
void wserver_finalize(wserver* self);
