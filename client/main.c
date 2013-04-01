#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>

#define handle_error(msg)  do { perror(msg); exit(EXIT_FAILURE); } while (0)

int client_connect(const char * hostname, int port)
{
    struct sockaddr_in serv_addr;
    struct hostent *server;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        handle_error("Creation socket failed");
    }
    server = gethostbyname(hostname);
    if (server == NULL) {
        handle_error("Hostname error");
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(port);
    if (connect(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
        handle_error("Connection error");
    }
    return sockfd;
}

void client_getfile(int sock, const char* file, const char* hostname) {
    int n;
    char buf[1024];
    int writen = snprintf(buf, sizeof(buf) - 1, "GET /%s HTTP/1.1\r\nHost: %s\r\n\r\n", file, hostname);
    write(sock, buf, writen);

    while ( (n = read(sock, buf, sizeof(buf) - 1) ) > 0 )
    {
        buf[n] = 0;
        fputs(buf, stdout);
    }
}

void client_disconnect(int sockfd)
{
    close(sockfd); 
}

int main(int argc, char *argv[])
{
    int sockfd;

    if (argc < 4) {
        fputs("Usage: get <hostname> <port> <file>", stderr);
        exit(1);
    }

    sockfd = client_connect(argv[1], atoi(argv[2]));
    client_getfile(sockfd, argv[3], argv[1]);
    client_disconnect(sockfd);

    return 0;
}

