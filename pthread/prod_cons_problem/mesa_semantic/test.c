#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 1

pthread_mutex_t m;
pthread_cond_t empty;
pthread_cond_t full;
int count;

void get(int num)
{
	if (count == 0)
	{
		printf("%d wtf\n", num);
		exit(1);
	}
	--count;
	printf("consumer%d try get: left count is %d\n", num, count);
}

void put()
{
	++count;
	printf("producer try put: left count is %d\n", count);
}

void *produce(void *v)
{
	(void)v;
	printf("producer start\n");
	while (1) {
        pthread_mutex_lock(&m);
		printf("producer locked mutex\n");
        if (count == MAX)
		{
			printf("producer waiting\n");
    		pthread_cond_wait(&empty, &m);
			printf("producer recv signal - ready\n");
		}
        put();
        pthread_cond_signal(&full);
		printf("producer send signal\n");
        pthread_mutex_unlock(&m);
    }
	return (0);
}

void *consumer1(void *v)
{
	(void)v;
	printf("consumer1 start\n");
	while (1) {
        pthread_mutex_lock(&m);
		printf("consumer1 locked mutex\n");
        if (count == 0)
		{
			printf("consumer1 waiting\n");
        	pthread_cond_wait(&full, &m);
			printf("consumer1 recv signal - ready\n");
		}
        get(1);
        pthread_cond_signal(&empty);
		printf("consumer1 send signal\n");
        pthread_mutex_unlock(&m);
    }
	return (0);
}

void *consumer2(void *v)
{
	(void)v;
	printf("consumer2 start\n");
	while (1) {
        pthread_mutex_lock(&m);
		printf("consumer2 locked mutex\n");
        if (count == 0)
		{
			printf("consumer2 waiting\n");
        	pthread_cond_wait(&full, &m);
			printf("consumer2 recv signal - ready\n");
		}
        get(2);
        pthread_cond_signal(&empty);
		printf("consumer2 send signal\n");
        pthread_mutex_unlock(&m);
    }
	return (0);
}

int main()
{
	pthread_mutex_init(&m, NULL);
	pthread_cond_init(&full, NULL);
	pthread_cond_init(&empty, NULL);

	pthread_t p1, p2, p3;
	pthread_create(&p1, NULL, produce, NULL);
	pthread_create(&p2, NULL, consumer1, NULL);
	pthread_create(&p3, NULL, consumer2, NULL);
	
	pthread_join(p1, NULL);
	pthread_join(p2, NULL);
	pthread_join(p3, NULL);
	return (0);
}