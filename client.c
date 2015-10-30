#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	int sockfd;
	int len;
	int result;
	struct sockaddr_in address;
	char ch[10];

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = 9734;
//	strcpy(address.sin_path, "server_socket");
	len = sizeof(address);
	
	result = connect(sockfd, (struct sockaddr *)&address, len);

	if(result == -1)
	{
		perror("oops: client1");
		exit(1);
	}


	read(0, ch, 1);
	write(sockfd, ch,1);
	read(sockfd, ch,1);
	printf("from server = %s\n",ch );
	close(sockfd);
	exit(0);
}












