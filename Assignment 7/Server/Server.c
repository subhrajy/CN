//
//  Server.c
//
//  Created by Subhrajyoti Behera on 2/11/21.
//

#include "Server.h"

void do_processing(int sock){
    char buffer[1024];
    FILE *f;

    f = fopen("message.txt", "w");
    bzero(buffer, 1024);

    read(sock, buffer, 1023);
    fprintf(f, "%s", buffer);

    printf("\nFile copied as \"message.txt\"");
}


int main(int argc, char const *argv[]){
    int sockfd, newsockfd, portno, clilen;
    struct sockaddr_in serv_addr, cli_addr;
    portno = 5002;

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

    if(newsockfd < 0){
        perror("Error on accpet !!");
        exit(1);
    }
    do_processing(newsockfd);

    return 0;
}
