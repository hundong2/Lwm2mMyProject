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
	int num_stack_pt = 0, op_stack_pt = 0;
	int i;
	char *Op = (char*)malloc(sizeof(char) * n);
	int  *Num = (int*)malloc(sizeof(int)  * n);
	char temp_op;
	for(i = 0 ; i < n ; i++)
	{
		switch(Data[i][0])
		{
			//push operator stack
			
			if( op_stack_pt == 0 &&(Data[i][0] == '+' || Data[i][0] == '-' || Data[i][0] == '*' || Data[i][0] == '/' || Data[i][0] == '(' || Data[i][0] == ')'))
			{
				Op[op_stack_pt++] = Data[i][0];
				break;
			}
			case '+':
			case '-':
				if( Op[op_stack_pt - 1] == ')' || Op[op_stack_pt - 1] == '*' || Op[op_stack_pt - 1] == '/' || Op[op_stack_pt - 1] == '(')
				{
					
					//Op[op_stack_pt++] = Data[i][0];
					//pop op
					//calcurator Data
					temp_op = Op[op_stack_pt - 1];
					Op[op_stack_pt - 1] = Data[i][0];
				}
				else 
				{
					//push op data
					Op[op_stack_pt++] = Data[i][0];
				}
				break;
			case '/':
			case '*':
				if(Op[op_stack_pt - 1] == ')' || Op[op_stack_pt - 1] == '(' || Op[op_stack_pt - 1] == '+' || Op[op_stack_pt - 1] == '-')
				{
					//push op
					Op[op_stack_pt++] = Data[i][0];
				}
				else if( Op[op_stack_pt - 1] == '*' || Op[op_stack_pt - 1] == '/')
				{
					//pop op
					//calcurator data
					temp_op = Op[op_stack_pt - 1];
					Op[op_stack_pt - 1] = Data[i][0];
					
				}
				break;
			case '(':
				Op[op_stack_pt - 1] = Data[i][0];
				break;
			case ')':
				while( Op[op_stack_pt - 1] != '(')
				{
					temp_op = Op[op_stack_pt - 1];
					//calcurator data
					op_stack_pt--;
				}
				op_stack_pt--;
				break;
			default :
				//push number stack
				Num[num_stack_pt++] = atoi(Data[i]);
				break;
		}//switch 
	}//for
	
	return result;
} //function calc
