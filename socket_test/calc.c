#include "calc.h"
int stack[MAX];
double calc_stack[MAX];
int top;
double _calculator(char *data)
{
	char c;
	int i=0;
	char src[256];
	char expr[256];
	double result;
	printf("%s\n", data);
	postfix(expr, data);
	postfix_print(expr);
	result=calc(expr);
	printf("  Answer : %.8g\n", result);
	
	return result;
	/*while((c=getchar()) != '\n')
		src[i++]=c;
	src[i]='\0';
	while(src[0] != EOF)
	{
		postfix(expr, src);
		postfix_print(expr);
		result=calc(expr);
		printf("  Answer : %.8g\n", result);
		i=0;
		while((c=getchar()) != '\n')
			src[i++]=c;
		src[i]='\0';
	}
	puts("Good bye");
	*/
}
void postfix_print(char *p)
{
	printf("  Postfix : ");
	while(*p)
	{
		switch (*p)
		{
		case 's' :
			printf("sin");
			break;
		case 'c' :
			printf("cos");
			break;
		case 't' :
			printf("tan");
			break;
		case '_' :
			printf("(-)");
			break;
		default :
			printf("%c", *p);
			break;
		}
		p++;
	}
	printf("\n");
}
double calc(char *p)
{
	double a, b;
	init_stack();
	while(*p)
	{
		if(*p == '.' || (*p >= '0' && *p <= '9'))
		{
			char strtemp[20];
			int j=0;
			while(*p == '.' || (*p >= '0' && *p <= '9'))
			{
				strtemp[j++]=*p;
				p++;
			}
			strtemp[j]='\0';
			calc_push(atof(strtemp));
		}
		else if(*p == 's')
		{
			a=calc_pop();
			calc_push(sin(a*RADIAN));
			p++;
		}
		else if(*p == 'c')
		{
			a=calc_pop();
			calc_push(cos(a*RADIAN));
			p++;
		}
		else if(*p == 't')
		{
			a=calc_pop();
			calc_push(tan(a*RADIAN));
			p++;
		}
		else if(*p == '_')
		{
			a=calc_pop();
			calc_push(-1*a);
			p++;
		}
		else if(*p == '+')
		{
			a=calc_pop();
			b=calc_pop();
			calc_push(a+b);
			p++;
		}
		else if(*p == '-')
		{
			a=calc_pop();
			b=calc_pop();
			calc_push(b-a);
			p++;
		}
		else if(*p == '*')
		{
			a=calc_pop();
			b=calc_pop();
			calc_push(a*b);
			p++;
		}
		else if(*p == '/')
		{
			a=calc_pop();
			b=calc_pop();
			calc_push(b/a);
			p++;
		}
		else
			p++;
	}
	return calc_pop();
}
double calc_push(double t)
{
	if(top >= MAX)
	{
		printf("\n Stack overflow.");
		exit(1);
	}
	calc_stack[top++]=t;
	return t;
}
double calc_pop(void)
{
	if(top < 1)
	{
		printf("\n Stack underflow.");
		exit(1);
	}
	return calc_stack[--top];
}
void postfix(char *dst, char *src)
{
	int i=0;
	int j;
	init_stack();
	while(*src)
	{
		if(*src == '(')
		{
			push(*src);
			src++;
		}
		else if(*src == ')')
		{
			while(get_stack_top() != '(')
			{
				*dst++=pop();
				*dst++=' ';
			}
			pop();
			src++;
		}
		else if(is_operator(*src))
		{
			if(*src == '-' && (i == 0 || *(src-1) == '(' || is_operator(*(src-1))))
			{/*이것은 단항연산자 '(-)'이다.*/
				push('_');
				src++;
			}
			else
			{
				while(!is_stack_empty() && precedence(get_stack_top()) >= precedence(*src))
				{
					*dst++=pop();
					*dst++=' ';
				}
				push(*src);
				src++;
			}
		}
		else if((*src >= '0' && *src <= '9') || (*src == '.'))
		{
			do
			{
				*dst++=*src++;
			} while((*src >= '0' && *src <= '9') || (*src == '.'));
			*dst++=' ';
		}
		else if(j=is_function(src))
		{
			push(j);
			while(*src != '(')
				src++;
		}
		else
		{
			src++;
		}
		i++;
	}
	while(!is_stack_empty())
	{
		*dst++=pop();
		*dst++=' ';
	}
	dst--;
	*dst='\0';
}
void init_stack(void)
{
	top=0;
}
int push(int t)
{
	if(top >= MAX)
	{
		printf("\n Stack overflow.");
		exit(1);
	}
	stack[top++]=t;
	return t;
}
int pop(void)
{
	if(top < 1)
	{
		printf("\n Stack underflow.");
		exit(1);
	}
	return stack[--top];
}
int get_stack_top(void)
{
	return (top < 1) ? -1: stack[top-1];
}
int is_stack_empty(void)
{
	return (top < 1);
}
int is_operator(int k)
{
	return (k == '+' || k == '-' || k == '*' || k == '/');
}
int is_function(char *k)
{
	char temp[5];
	int i, j;
	j=*k;
	for(i=0; i < 3; i++)
	{
		temp[i]=*(k+i);
	}
	temp[i]='\0';
	if(!strcmp(temp, "sin") || !strcmp(temp, "cos") || !strcmp(temp, "tan"))
		return j;
	else
		return -1;
}
int precedence(int op)
{
	if(op == '(')
		return 0;
	else if(op == '+' || op == '-')
		return 1;
	else if(op == '*' || op == '/')
		return 2;
	else if(op == '_' || op == 's' || op == 'c' || op == 't')
		return 3;
	else
		return 4;
}
