#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h> //wrtie , close
#define BUFF_SIZE 1024

void tokken(char *t);
int calc_infix(char **Data, int n);

void tokken(char *t)
{
	int i = 0;
	char *data[10];
	data[i++] = strtok(t , " \n");
	while( data[i++] = strtok( NULL , " \n"));
	calc_infix(data, i - 1);
	
}
int main(int argc , char **argv)
{
	
	int fd, num, i;
	char temp[BUFF_SIZE];
	if( 0 < ( fd = open(argv[1] , O_RDONLY | O_CREAT)) )
	{
		read(fd , temp , BUFF_SIZE);
		close(fd);
	}
	tokken(temp);
	close(fd);
	return 0;
}
int calc_infix(char **Data, int n)
{
	int result = 0;
	int i;
	for(i = 0 ; i < n ; i++)
	{
		switch(Data[i][0])
		{
			case '+':
				break;
			case '-':
				break;
			case '*':
				break;
			case '/':
				break;
			default :
				break;
		}
	}
	
	return result;
}
