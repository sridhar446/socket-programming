#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
//#include <netint/in.h>

int main(int argc, char const *argv[])
{
	int server_sockfd, client_sockfd;
	int server_len, client_len;
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;

	unlink("server_socket");
	server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_address.sin_port = 5000;
//	strcpy(server_address.sin_path, "server_socket");
	server_len = sizeof(server_address);
	bind(server_sockfd,(struct sockaddr *)&server_address, server_len);

	listen(server_sockfd, 5);

	signal(SIGCHLD, SIG_IGN);
	
	while(1){
		char rxBuffer[10],txBuffer[10];
		//printf("server waiting\n");
	

	client_len = sizeof(client_address);
	client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);

	if(fork() == 0){
/*
		read(client_sockfd, rxBuffer, 10);
		sleep(1);
		printf("client: %s\n", rxBuffer);
*/		//++ch[0];
		read(0,txBuffer,10);
//		printf("server:");
		write(client_sockfd,txBuffer,10);
		close(client_sockfd);
		exit(0);
		}
	
	else{
		close(client_sockfd);
		}	
	}
}












