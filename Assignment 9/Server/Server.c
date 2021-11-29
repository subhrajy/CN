#include "server.h"
#define PORT 8080
#define MAXLINE 10
#define MSG_CONFIRM 0


int main(int argc, char const *argv[]) {
    int sockfd, newsockfd, portno, clilen, count = 0, i = 0;
    char num1[256], num2[256];
    struct sockaddr_in serv_addr, cli_addr;
    portno = 5001;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0){
        perror("Error opening socket !!");
        exit(1);
    }

    bzero((char*) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(portno);

    if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
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

    read(newsockfd, num1, 256);
    read(newsockfd, num2, 256);

    for (i = 0; i < strlen(num1); i++){
        if (num1[i] != num2[i])
            count++;
    }

    write(newsockfd, &count, sizeof(int));

    return 0;
}
