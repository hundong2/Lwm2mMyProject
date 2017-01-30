#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define PI 3.141592
#define RADIAN PI/180

void init_stack(void);	/*스택을 초기화*/
int push(int);	/*postfix로 바꾸는 스택의 push동작*/
int pop(void);	/*postfix로 바꾸는 스택의 pop동작*/
double calc_push(double);	/*계산스택의 push동작*/
double calc_pop(void);	/*계산스택의 pop동작*/
int get_stack_top(void);	/*postfix스택의 top의 값을 리턴*/
int is_stack_empty(void);	/*스택이 비어있는지*/
int is_operator(int);	/*연산자인지*/
int is_function(char *);	/*삼각함수인지*/
int precedence(int);	/*연산자의 순위를 리턴*/
void postfix(char *, char *);	/*postfix로 바꾸는 함수*/
void postfix_print(char *);	/*postfix로 바뀐것을 출력*/
double calc(char *);	/*연산하는 함수*/
double _calculator(char *data);
