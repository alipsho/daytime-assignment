//SERVER
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#define MY_PORT_NUMBER 4444

int main(int argc, char **argv) {
	//Make A Socket
	int listenfd;
	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) { // using IPv4 internet protocol (TCP)
		perror("socket");
		exit(1);
	}
	printf("Server socket created\n");

	//Bind The Socket To A Port

	struct sockaddr_in servAddr;

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(MY_PORT_NUMBER); 
	servAddr.sin_addr.s_addr =inet_addr("192.168.56.102");
	
	if (bind(listenfd, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0) { //Bind socket to a port
		perror("bind");
		exit(1);
	}
	printf("Socket bound to port\n");

	//Listen And Accept Connections
	if ((listen(listenfd, 3)) < 0) { //Sets up a connection queue 
		perror("listen");
		exit(1);
	}
	printf("Listening for connections...\n\n");

	//Accept Connections

	int connectfd, status;
	int length = sizeof(struct sockaddr_in);
	struct sockaddr_in clientAddr;

	while (1) {
		//Blocks until a new connection 
		if ((connectfd = accept(listenfd, (struct sockaddr *)&clientAddr, &length)) < 0) {
			perror("accept");
			exit(1);
		}
		printf("Client connection was found!\n");

			char buffer[100]; //Read the date/time into buffer
			time_t ltime;
			time(&ltime);
			strcpy(buffer, ctime(&ltime));
			int len = strlen(buffer);
			buffer[len] = '\0';

			if ((write(connectfd, buffer, 100)) <= 0) { //Write buffer to client
				perror("write");
				exit(1);
			}
			printf("Wrote time and date to client\n");
			printf(" existing...\n\n"); 
			close(connectfd); //Close client file descriptor
			exit(0);		  //Exit child process
		
	}
}
