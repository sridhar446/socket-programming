#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#define SIZE 160
#define PORT 5000

	int sockfd;
	int len;
	int result;
	struct sockaddr_in address;
	char rxBuffer[10],txBuffer[10];



void  *read_message(void * socket)
{
int sockfd, ret;  
char buffer[SIZE];   
sockfd = (int) socket;  
memset(buffer, 0, SIZE);    
for (;;) 
	{  
  	ret = recvfrom(sockfd, buffer, SIZE, 0, NULL, NULL);    
  	if (ret < 0) 
 	 	{    
 	 		 printf("Error receiving data!\n");      
 	 	} 
 	 else if(ret > 0)
	  	{  
	   		printf("ret = %d\n",ret );
	   		printf("server: ");  
	   		fputs(buffer, stdout);  
	   		//printf("\n");  
	  	}
	  else if(ret == 0)
	  	{
	  		pthread_exit(NULL);
	  		return ;	
	  	}
	 } 
}


int main(int argc, char *argv[])
{
	pthread_t readID;

	
	struct sockaddr_in addr, cl_addr;
	int sockfd,ret;
	char buffer[SIZE];
	char * server_addr;


	if(argc < 2)
		{
			printf("usage: client <ip address>\n" );
			exit(1);
		}
	server_addr = argv[1];

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
		{
			printf("Error creating socket!\n");	
			exit(1);
		}
	printf("Socket created....\n");

	
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(server_addr);
	addr.sin_port = PORT;
	
	ret = connect(sockfd, (struct sockaddr *)&addr, sizeof(addr));
	if(ret == -1)
		{
			perror("oops: client1");
			exit(1);
		}
	printf("connected to server!\n");
	
	memset(buffer, 0, SIZE);
	printf("Start your chat:\n" );

	ret = pthread_create(&readID, NULL, read_message, (void *) sockfd);
	if(ret)
		{
			printf("Error in creating thread\n");	
			exit(1);
		}

	while(fgets(buffer, SIZE, stdin) != NULL)
		{
			ret = sendto(sockfd, buffer, SIZE, 0, (struct sockaddr*)&addr, sizeof(addr));
			if(ret < 0)
			{
				printf("Error sending message!\n");
			}
		}
		
	close(sockfd);
	 
	//pthread_join(readID,NULL);
}













