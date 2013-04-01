#include "server.h"

#include <string.h>
#include <stdio.h>

const char data_path[] = "data";

void write_bad_request(int sock) {
    static const char bad_response_msg[] =
        "HTTP/1.1 400 Bad Request\r\nContent-Type: text/html; charset=UTF-8\r\nConnection: close\r\n\r\n<h2>Bad Request</h2>\r\n";
    write(sock, bad_response_msg, strlen(bad_response_msg));
}

void http_handler(int connfd)
{
    int n, sent;
    char buf[1024];
    char path[1024];

    read(connfd, buf, sizeof(buf) - 1);
    if (strncmp(buf, "GET ", 4) == 0) {
        *strchr(buf + 4, ' ') = 0;

        strcpy(path, data_path);
        strcat(path, buf + 4);

        FILE* data = fopen(path, "rb");
        if (data == NULL) {
            write_bad_request(connfd);
        } else {
            sent = 0;
            while ( (n = fread(buf, 1, sizeof(buf), data)) > 0 ) 
            {
                write(connfd, buf, n);
                sent += n;
            }
            fclose(data);

            if (sent == 0)
                write_bad_request(connfd);
        }
    } else {
        write_bad_request(connfd);
    }

    close(connfd);
}


int main()
{
    wserver s;

    wserver_init(&s, 81, &http_handler);
    wserver_listen(&s);
    wserver_finalize(&s);

    return 0;
}

