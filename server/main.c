#include "wserver.h"
#include "http.h"

#include <signal.h>

int main(int argc, char* argv[])
{
    wserver s;
    int port = (argc > 1) ? atoi(argv[1]) : 80;

    signal(SIGCHLD, SIG_IGN);

    wserver_init(&s, port, &http_handler);
    wserver_listen(&s);
    wserver_finalize(&s);

    return 0;
}

