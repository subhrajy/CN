#include "server.h"
#define PORT 8080
#define MAXLINE 1024
#define MSG_CONFIRM 0

int main(int argc, char const *argv[]) {
    int sockfd, n;
    unsigned int len;
    char buffer[MAXLINE];
    char *msg;
    struct sockaddr_in servaddr, cliaddr;

    msg = malloc(256);

    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        perror("\nSocket creation failed.");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    if(bind(sockfd, (const struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
        perror("\nError on binding.");
        exit(EXIT_FAILURE);
    }

    len = sizeof(cliaddr);
    n = recvfrom(sockfd, (char*)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr*) &cliaddr, &len);
    buffer[n] = '\0';

    printf("\nclient: %s", buffer);

    printf("\n\nEnter message - ");
    scanf("%s", msg);
    sendto(sockfd, (const char*)msg, strlen(msg), MSG_CONFIRM, (const struct sockaddr*) &cliaddr, len);

    close(sockfd);

    return 0;
}
