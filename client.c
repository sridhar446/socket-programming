#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>

	int sockfd;
	int len,*arg[1];
	int result;
	struct sockaddr_in address;
	char rxBuffer[10],txBuffer[10];

void  *readThread(void *data)
{
	while(1)
	{
		sockfd = socket(AF_INET, SOCK_STREAM, 0);

		address.sin_family = AF_INET;
		address.sin_addr.s_addr = inet_addr("127.0.0.1");
		/*if(inet_pton(AF_INET, "49.206.106.101", &address.sin_addr)<=0)
   		 {
        	printf("\n inet_pton error occured\n");
        	return ;
  		  }
		*/
		address.sin_port = 5000;
		//	strcpy(address.sin_path, "server_socket");
		len = sizeof(address);
	
		result = connect(sockfd, (struct sockaddr *)&address, len);

		if(result == -1)	
		{
			perror("oops: client1");
			exit(1);
		}

		//printf("client:" );
		//read(0, ch, 10);
		//write(sockfd, ch,10);
		read(sockfd, rxBuffer,10);
		printf("server:%s",rxBuffer );
		//close(sockfd);

	}
			//printf("Yes1\n");
}


int main(int argc, char const *argv[])
{
	pthread_t readID,decID;

	pthread_create(&readID,NULL,readThread,NULL);
	//pthread_create(&decID,NULL,decThread,NULL);
	

	//pthread_join(incID,NULL);
while(1)
{
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
/*	if(inet_pton(AF_INET, argv[1], &address.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return ;
    }
*/	address.sin_port = 9734;
//	strcpy(address.sin_path, "server_socket");
	len = sizeof(address);
	
	result = connect(sockfd, (struct sockaddr *)&address, len);

	if(result == -1)
	{
		perror("oops: client1");
		exit(1);
	}

	printf("client:" );
	scanf("%s",txBuffer);
	write(sockfd, txBuffer,10);
	//read(sockfd, ch,10);
	//printf("server:%s\n",ch );
	close(sockfd);
}
	exit(0);

}












