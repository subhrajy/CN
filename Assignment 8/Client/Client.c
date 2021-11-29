#include "client.h"
#define PORT 8080
#define MAXLINE 1024
#define MSG_CONFIRM 0


int main(int argc, char const *argv[]) {
    int sockfd, len, n;
    char buffer[MAXLINE];
    char *msg;
    struct sockaddr_in servaddr;

    msg = malloc(256);

    printf("\nEnter message - ");
    scanf("%s", msg);

    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        perror("\nSocket creation failed.");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    len = sizeof(servaddr);
    sendto(sockfd, (const char*)msg, strlen(msg), MSG_CONFIRM, (const struct sockaddr*)&servaddr, len);

    n = recvfrom(sockfd, (char*)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr*)&servaddr, (socklen_t*)&len);
    buffer[n] = '\0';

    printf("\nserver: %s", buffer);
    close(sockfd);

    return 0;
}
