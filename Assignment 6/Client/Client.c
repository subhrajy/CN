//
//  Client.c
//  Test
//
//  Created by Subhrajyoti Behera on 26/10/21.
//

#include "Client.h"

int main(int argc, char const *argv[]) {
    int sockfd, portno;
    long n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[256];

    if (argc < 3)
    {
        fprintf(stderr, "\nUsage %s hostname port", argv[0]);
        exit(0);
    }

    portno = atoi(argv[2]);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
    {
        perror("Error opening socket !!");
        exit(1);
    }

    server = gethostbyname(argv[1]);

    if(server == NULL)
    {
        fprintf(stderr, "\nNo such hosts.");
        exit(0);
    }

    bzero((char*) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno);
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);

    if(connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Error connecting !!");
        exit(1);
    }

    printf("\nEnter '$' to exit.");

    while(1)
    {
        printf("\nEnter a message - ");
        bzero(buffer, 256);
        fgets(buffer, 256, stdin);
        
        if (buffer[0] == '$')
        {
            exit(0);
        }        n = write(sockfd, buffer, strlen(buffer));
        if(n < 0)
        {
            perror("Error writing to socket !!");
            exit(1);
        }

        bzero(buffer, 256);
        n = read(sockfd, buffer, 256);

        if(n < 0)
        {
            perror("Error reading from socket !!");
            exit(1);
        }

        printf("\nserver: %s", buffer);
    }

    return 0;
}
