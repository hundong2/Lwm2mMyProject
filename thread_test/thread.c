#include <stdio.h>
#include <pthread.h>

#define MAX_THREAD 3

//int pthread_join(pthread_t th, void **thread_return);
void *t_func(void *count)
{
	(*(int*)count)++;
	printf("%d = %d\n" ,thread_id , *(int*)count);
	sleep(1);
}

int main(int argc , char **argv)
{
	pthread_t thread_id[MAX_THREAD];
	int i = 0;
	int count = 0;
	for( i = 0 ; i < MAX_THREAD ; i++)
	{
		pthread_create(&thread_id[i] , NULL , t_func , (void *)&count);
		usleep(5000);
	}
	for(i = 0 ; i < MAX_THREAD ; i++)
	{
		printf("thread pid %d\n" , pthread_join(thread_id[i] , NULL));
	}
	return 0;
}
