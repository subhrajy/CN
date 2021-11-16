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

int main(int argc, char const *argv[]) {
    int sockfd, portno, num1, num2, op, result;
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

    printf("\nEnter first number - ");
    scanf("%d", &num1);
    write(sockfd, &num1, sizeof(int));

    printf("\nEnter second number - ");
    scanf("%d", &num2);
    write(sockfd, &num2, sizeof(int));

    printf("\nEnter operator - 1) Addition\n2) Subtraction\n3) Multiplication\n4) Division\n\n");
    scanf("%d", &op);
    write(sockfd, &op, sizeof(int));

    read(sockfd, &result, sizeof(float));
    printf("\nThe result is - %d", result);

    return 0;
}
