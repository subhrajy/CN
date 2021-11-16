//
//  Server.c
//  Test
//
//  Created by Subhrajyoti Behera on 26/10/21.
//

#include "Server.h"

void do_processing(int sock)
{
    long n;
    char buffer[256];
    
    printf("\nEnter '$' to exit.");

    while(1)
    {
        bzero(buffer, 256);
        n = read(sock, buffer, 256);

        if(n < 0)
        {
            perror("\nError on reading from client !!!");
            exit(1);
        }

        printf("\nclient: %s", buffer);
        
        bzero(buffer, 256);
        
        printf("\nEnter a message - ");
        fgets(buffer, 256, stdin);

        if (buffer[0] == '$')
        {
            exit(0);
        }
        n = write(sock, buffer, strlen(buffer));
        if(n < 0)
        {
            perror("Error writing to socket !!");
            exit(1);
        }
    }
}


int main(int argc, char const *argv[]) {
    int sockfd, newsockfd, portno, clilen;
    //char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    //int n;
    portno = 5002;

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

    listen(sockfd, 2);


    clilen = sizeof(cli_addr);
   
    newsockfd = accept(sockfd, (struct sockaddr*) &cli_addr, (socklen_t*) &clilen);

    if(newsockfd < 0)
    {
        perror("Error on accpet !!");
        exit(1);
    }
    do_processing(newsockfd);
    
    return 0;
}
