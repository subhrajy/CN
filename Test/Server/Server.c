#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <ctype.h>

void doprocessing(int);

int main( int argc, char *argv[] ) {
    int sockfd, newsockfd, portno, clilen, pid;
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    portno = 5003;

    sockfd = socket (AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr= inet_addr("127.0.0.1");
    serv_addr.sin_port = htons (portno);

    if (bind (sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror ("ERROR on binding");
        exit(1);
    }

    listen (sockfd,5);
    printf("Server Listening\n");
    clilen = sizeof (cli_addr);

    while(1){
	    newsockfd = accept (sockfd, (struct sockaddr *) &cli_addr, (socklen_t*) &clilen);

	    if(newsockfd<0){
	        perror("ERROR on accept");
	        exit(1);
	    }
        pid = fork();
	    if(pid <0){
	    	perror("ERROR on fork");
	    	exit(1);
		}

		if(pid == 0){
			close(sockfd);
			doprocessing(newsockfd);
			exit(0);
		}

		else{
			close(newsockfd);
		}
	}

    return 0;
}

void doprocessing (int sock){
	int num1, num2, result;
	char op;

	read(sock, &num1, sizeof(int));
    printf("First number recieved: %d\n", num1);
    read(sock, &num2, sizeof(int));
    printf("Second number recieved: %d\n", num2);
    read(sock, &op, sizeof(char));
    printf("Op = %c \n", op);
    if(op=='+'){
        printf("Operator recieved = Add");
        result = num1 + num2;
    }
    if(op=='-'){
        printf("Operator recieved = Sub");
        result = num1 - num2;
    }if(op=='*'){
        printf("Operator recieved = Mul");
        result = num1 * num2;
    }if(op=='/'){
        printf("Operator recieved = Div");
        result = num1/num2;
    }
    printf("\nResult = %d \n", result);
    write(sock, &result, sizeof(int));
}
