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

}


int main(int argc, char const *argv[]) {
    int sockfd, newsockfd, portno, clilen, pid, num1, num2, op, result;
    struct sockaddr_in serv_addr, cli_addr;
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

    printf("\nServer listening ...");
    listen(sockfd, 2);


    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr*) &cli_addr, (socklen_t*) &clilen);

    read(newsockfd, &num1, sizeof(int));
    printf("\nFirst number received - %d", num1);

    read(newsockfd, &num2, sizeof(int));
    printf("\nFirst number received - %d", num2);

    read(newsockfd, &op, sizeof(int));

    if(op == 1)
    {
        printf("\nOperator received - Add");
        result = num1 + num2;
    }

    if(op == 2)
    {
        printf("\nOperator received - Subtract");
        result = num1 - num2;
    }

    if(op == 3)
    {
        printf("\nOperator received - Multiply");
        result = num1 * num2;
    }

    if(op == 4)
    {
        printf("\nOperator received - Divide");
        result = num1 / num2;
    }

    write(newsockfd, &result, sizeof(int));

    return 0;
}
