#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUFF_SIZE 1024
typedef struct sockaddr_in SOCK_IN;
void error_handling(char *message);
int main()
{
	int serv_socket;
	int clnt_socket;
	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;

	int clnt_addr_size;
	char buff_rcv[BUFF_SIZE+5], buff_snd[BUFF_SIZE +5];

	serv_socket = socket(PF_INET , SOCK_STREAM , 0);
	if( serv_socket == -1)
	{
		printf("failed\n");
		exit(1);
	}
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(4000);
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	if( -1 == bind(serv_socket, (struct sockaddr*)&serv_addr, sizeof(serv_addr)))
	{
		printf("error bind\n");	
		exit(1);
	}
	if(-1 == listen(serv_socket , 5))
	{
		printf("listen fail\n");
		exit(1);
	}
	printf("test start\n");
	while(1)
	{
		clnt_addr_size = sizeof(clnt_addr);
		clnt_socket = accept(serv_socket, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
	if(clnt_socket == -1)
	{
		printf("not connect \n");
		exit(1);
	}

		read(clnt_socket , buff_rcv , BUFF_SIZE);
		printf("server receive data : %s \n" , buff_rcv );
		sprintf(buff_snd, "%d : %s", strlen(buff_rcv) , buff_rcv);
		write(clnt_socket , buff_snd , strlen(buff_snd)+1);
		close(clnt_socket);
		
	}
}
