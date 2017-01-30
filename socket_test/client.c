#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUFF_SIZE 1024


int main(int argc , char **argv)
{
	int clnt_socket, fd;
	char temp[BUFF_SIZE];
	struct sockaddr_in serv_addr;
	char buff[BUFF_SIZE + 5];

	clnt_socket = socket(PF_INET , SOCK_STREAM , 0);
	if( clnt_socket == -1)
	{
		printf("failed\n");
		exit(1);
	}
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(4000);
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	if( -1 == connect(clnt_socket, (struct sockaddr*)&serv_addr, sizeof(serv_addr)))
	{
		printf("error\n");
		exit(1);
	}
	/*if( 0 < ( fd = open(argv[1] , O_RDONLY | O_CREAT)) )
	{
		read(fd , temp , BUFF_SIZE);
		close(fd);
	}*/
	//printf("strlent temp = %d \n" , strlen(temp));
	write(clnt_socket , argv[1] , strlen(argv[1]) + 1);
	read(clnt_socket , buff, BUFF_SIZE);
	printf("receive data = %s\n" , buff);
	close(clnt_socket);
	return 0;
}
