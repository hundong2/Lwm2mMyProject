#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *test(void **data)
{
	int i;
	int a = *(int *)data;
	for( i = 0 ; i < 10 ; i++)
	{
		printf("%d\n" , i*a);
	}
	return (void*)(i * 100);
}

int main()
{

	cher a[10] = "102+";
	pthread_t thread_t;
	int status;

	if(pthread_create(&thread_t , NULL , test , ((void *)&a))  < 0 )
	{
		perror("thread create error:");
		exit(0);
	}
	pthread_join(thread_t , (void**)&status);
	printf("Thread End %d \n" , status);
	return 0;
}
