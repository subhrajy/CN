// Subhra

#include "client.h"


int main(int argc, char const *argv[]) {
    int sockfd, portno, hammin_dist;
    char num1[256], num2[256];
    struct sockaddr_in serv_addr;
    struct hostent *server;

    if (argc < 3){
        fprintf(stderr, "\nUsage %s hostname port", argv[0]);
        exit(0);
    }

    portno = atoi(argv[2]);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        perror("Error opening socket !!");
        exit(1);
    }

    server = gethostbyname(argv[1]);

    if(server == NULL){
        fprintf(stderr, "\nNo such hosts.");
        exit(0);
    }

    bzero((char*) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno);
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);

    if(connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0){
        perror("Error connecting !!");
        exit(1);
    }

    bzero(num1, 256);
    bzero(num2, 256);

    printf("\nEnter num1 - \n");
    fgets(num1, 256, stdin);

    printf("\nEnter num2 - \n");
    fgets(num2, 256, stdin);

    write(sockfd, num1, strlen(num1));
    write(sockfd, num2, strlen(num2));

    printf("\nreciving ...");
    printf("\nHello");
    printf("\ngo to hell C");

    read(sockfd, &hammin_dist, sizeof(int));
    printf("%d", hammin_dist);

    return 0;
}
