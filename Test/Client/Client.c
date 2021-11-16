#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    int sockfd, portno, num1, num2, result;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char op;

    if (argc < 3) {
      fprintf(stderr,"usage %s hostname port\n", argv[0]);
      exit(0);
   }

    portno = atoi(argv[2]);
    sockfd = socket (AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    /* added this */
    server = gethostbyname(argv[1]);

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons (portno);
    //serv_addr.sin_addr.s_addr = inet_addr(argv[1]);

    /* added this */
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror ("ERROR connecting");
        exit(1);
    }

    printf("Enter first number: ");
    scanf("%d", &num1);
    write(sockfd, &num1,sizeof(int));
    printf("Enter second number: ");
    scanf("%d", &num2);
    write(sockfd, &num2,sizeof(int));
    printf("Enter the operator: \nAdd - '+' Sub - '-' Mul - '*' Div - '/' \n");
    scanf(" %c", &op);
    write(sockfd, &op, sizeof(char));
    read(sockfd, &result, sizeof(int));
    printf("The result is %d. \n", result);

    return 0;
}
