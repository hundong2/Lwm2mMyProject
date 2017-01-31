#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#include "calc.h"

#define BUFF_SIZE 1024
#define MAX_SOCK 10


int pid = 0;
void *NewFunc(void *fd)
{
	char buff_rcv[BUFF_SIZE+5], buff_snd[BUFF_SIZE + 5];
	int result;
	read(*(int *)fd , buff_rcv , BUFF_SIZE);
	printf("server receive data : %s \n" , buff_rcv );
	//sprintf(buff_snd, "%d : %s", strlen(buff_rcv) , buff_rcv);
	sprintf(buff_snd, "%0.3f", _calculator(buff_rcv));
	write(*(int *)fd , buff_snd , strlen(buff_snd) + 1);
	close(*(int *)fd);
}
int main(int argc, char **argv)
{
	int serv_socket;
	int clnt_socket;
	int status;
	pthread_t thread_t[MAX_SOCK];

	struct sockaddr_in6 serv_addr;
	struct sockaddr_in6 clnt_addr;

	int clnt_addr_size;


	serv_socket = socket(PF_INET6 , SOCK_STREAM , 0);
	if( serv_socket == -1)
	{
		printf("failed\n");
		exit(1);
	}
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin6_family = AF_INET6;
	serv_addr.sin6_flowinfo = 0;
	serv_addr.sin6_port = htons(atoi(argv[1]));
	serv_addr.sin6_addr = in6addr_any;
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
		else
		{
			pthread_create(&thread_t[pid], NULL, NewFunc, (void *)&clnt_socket);
			pthread_join(thread_t[pid] , NULL);		
			pid++;
		}
		printf("clnt_socket%d \n" , clnt_socket);


	}
}
