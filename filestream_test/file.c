#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h> //wrtie , close
#define BUFF_SIZE 1024
void tokken(char *t);
int calc(char *Operation_stack, double *Number_stack, int Op_size, int Num_size);
int Order(char oper);
int Op_Arrangement(char *Op, int size);
int Num_Arrangement(double *Num, int size);


void tokken(char *t)
{
	int i = 0, number = 0, Op_size = 0, Num_size = 0;
	char *Op_stack;
	double *Num_stack;
	char *data[10];
	data[number++] = strtok(t , " \n");
	while( data[number++] = strtok( NULL , " \n"));
	Op_stack = (char*)malloc(sizeof(char)* i);
	Num_stack = (double*)malloc(sizeof(double) *i);
	for( i = 0 ; i < number - 1; i++)
	{
		switch(data[i][0])
		{
			case '*':
			case '-':
			case '+':
			case '/':
			case '(':
			case ')':
				Op_stack[Op_size++] = data[i][0];
				break;
			default :
				Num_stack[Num_size++] = atof(data[i]);
				break;
		}
	}
	
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
int calc(char *Operation_stack, double *Number_stack, int Op_size, int Num_size)
{
	int backet_point = 0;
	int Op_point = 0, Num_point = 0;
	while(1)
	{
		if( 42 <= Operation_stack[Op_point] && Operation_stack[Op_point] <= 47 )
		{	
			if( Operation_stack[Op_point + 1] != ')' && Operation_stack[Op_point + 1] != '(' )
			{
				if( Order(Operation_stack[Op_point]) >= Order(Operation_stack[Op_point + 1]) )
				{
					//value of number stack operate
					switch( Operation_stack[Op_point])
					{
						case '+':
							Number_stack[Num_point] = Number_stack[Num_point] + Number_stack[Num_point + 1];
							Number_stack[Num_point + 1] = 0;
							break;
						case '-':
							Number_stack[Num_point] = Number_stack[Num_point] - Number_stack[Num_point + 1];
							Number_stack[Num_point + 1] = 0;
							break;
						case '/':
							Number_stack[Num_point] = Number_stack[Num_point] / Number_stack[Num_point + 1];
							Number_stack[Num_point + 1] = 0;
							break;
						case '*':
							Number_stack[Num_point] = Number_stack[Num_point] * Number_stack[Num_point + 1];
							Number_stack[Num_point + 1] = 0;
							break;
					}
					Num_point = 0;
					Op_point = 0;
					//value of all stack pointer set zero(0) 
				}
				else if( Order(Operation_stack[Op_point]) < Order(Operation_stack[Op_point + 1]) )
				{
					//pointer of operation stack move to forward
					//pointer of number stack move to forward 
					Num_point++; Op_point++;
				}
			}
			else
			{
				if( Operation_stack[Op_point + 1] == ')')
				{
					//value of number stack operate
					//if operation stack value is '(' then exchange the value to ' '
					//and then barket point location value exchange to ' '

				}
			}//if
		}//if
		else if( Operation_stack[Op_point] == '(')
		{
			//current location stack point throught barcket pointer value
			// movement to stack pointer
		}
	}//while
	Op_size = Op_Arrangement(Operation_stack, Op_size);
	Num_size = Num_Arrangement(Number_stack, Num_size);	
} //function calc
int Op_Arrangement(char *Op, int size)
{
	char *temp = (char*)malloc(sizeof(char)*size);
	int i, result_size = size;
	for( i = 0 ; i < size ; i++)
	{
		if( Op[i] != ' ')
		{
			temp[result_size++] = Op[i];
		}
	}
	Op = temp;
	return result_size - 1;
}
int Num_Arrangement(double *Num , int size)
{
	double *temp = (double*)malloc(sizeof(double)*size);
	int i, result_size = size;
	for( i = 0 ; i < size ; i++)
	{
		if( Num[i] != -1)
		{
			temp[result_size++] = Num[i];
		}
	}
	Num = temp;
	return result_size - 1;
}
int Order(char oper)
{
	int result_number = 3;
	switch(oper)
	{
		case '-':
		case '+':
			result_number = 1;
			break;
		case '/':
		case '*':
			result_number = 2;
			break;
	}
	return result_number;
}
