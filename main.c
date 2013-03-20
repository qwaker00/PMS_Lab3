#include "server.h"

int main()
{
    wserver s;

    wserver_init(&s, 81);
    wserver_listen(&s);
    wserver_finalize(&s);

    return 0;
}
