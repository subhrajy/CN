#include "stdio.h"
#include "stdlib.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "netdb.h"
#include "netinet/in.h"
#include "unistd.h"
#include "string.h"
#include "arpa/inet.h"

int main(int argc, char const *argv[]) {
    int sockfd, newsockfd, portno, clilen;
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
    else
    {
        printf("\nSomething");
    }

    printf("\nServer listening ...");
    listen(sockfd, 2);


    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr*) &cli_addr, (socklen_t*) &clilen);

    if(newsockfd < 0)
    {
        perror("Error on accpet !!");
        exit(1);
    }

    bzero(buffer, 256);
    n = read(newsockfd, buffer, 255);

    if(n < 0)
    {
        perror("Error reading from socket !!");
        exit(1);
    }

    printf("\nHere is the message - %s", buffer);

    n = write(newsockfd, "server got your message.", 40);
    if(n < 0)
    {
        perror("\nError writing to socket !!");
        exit(1);
    }

    return 0;
}
