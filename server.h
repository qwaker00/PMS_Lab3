
/*
    Simple webserver
*/

struct wserver {
    socketaddr_in serv_addr;
};

void wserver_init(wserver* self, int port);

void wserver_