// Subhra

#include "stdio.h"
#include "stdlib.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "netdb.h"
#include "netinet/in.h"
#include "unistd.h"
#include "string.h"
#include "arpa/inet.h"
#include "ctype.h"


void do_processing(int sock)
{
    int n, i;
    char buffer[256];
    bzero(buffer, 256);

    n = read(sock, buffer, 256);

    if(n < 0)
    {
        perror("\nError on reading from client !!!");
        exit(1);
    }

    for(i = 0; i < n; i++)
    {
        buffer[i] = toupper(buffer[i]);
    }

    printf("\nHere is the message from client - %s", buffer);
    n = write(sock, "Server got your message.", 30);

    if(n < 0)
    {
        perror("\nError on writing to client !!!");
        exit(1);
    }
}


int main(int argc, char const *argv[]) {
    int sockfd, newsockfd, portno, clilen, pid;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    portno = 5001;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Error opening socket !!");
        exit(1);
    }

    bzero((char*) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(portno);

    if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Error on binding !!");
        exit(1);
    }

    printf("\nServer listening ...");
    listen(sockfd, 2);


    clilen = sizeof(cli_addr);
    while(1)
    {
        newsockfd = accept(sockfd, (struct sockaddr*) &cli_addr, (socklen_t*) &clilen);

        if(newsockfd < 0)
        {
            perror("Error on accpet !!");
            exit(1);
        }

        pid = fork();

        if(pid < 0)
        {
            perror("\nError on fork !!!");
            exit(1);
        }

        if(pid == 0)
        {
            close(sockfd);
            do_processing(newsockfd);
            exit(0);
        }
        else
        {
            close(newsockfd);
        }
    }

    return 0;
}
