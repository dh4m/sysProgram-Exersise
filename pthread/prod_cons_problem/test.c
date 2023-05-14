#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 2

pthread_mutex_t m;
pthread_cond_t empty;
pthread_cond_t full;
int count;

void get()
{
	if (count == 0)
		exit(1);
	printf("%d", count);
	--count;
}

void put()
{
	++count;
}

void *produce(void *v)
{
	(void)v;
	while (1) {
        pthread_mutex_lock(&m);  // 대기큐 empty,fill 와 count 변수에 대한 lock (상호배제)
        while (count == MAX)              
    		pthread_cond_wait(&empty, &m);    // 수정된 부분 (소비이벤트를 기다림)
        put();
        pthread_cond_signal(&full);           // 수정된 부분 (생산이벤트 발생시킴)
        pthread_mutex_unlock(&m);// 대기큐 empty,fill 와 count 변수에 대한 lock (상호배제)
    }
	return (0);
}

void *consumer(void *v)
{
	(void)v;
	while (1) {
        pthread_mutex_lock(&m);    // 대기큐 empty,fill 와 count 변수에 대한 lock (상호배제)
        while (count == 0)
        	pthread_cond_wait(&full, &m);  // 수정된 부분 (생산이벤트 기다림)
        get();
        pthread_cond_signal(&empty);       // 수정된 부분 (소비이벤트 발생시킴)
        pthread_mutex_unlock(&m);  // 대기큐 empty,fill 와 count 변수에 대한 lock (상호배제)
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
	pthread_create(&p2, NULL, consumer, NULL);
	pthread_create(&p3, NULL, consumer, NULL);

	pthread_join(p1, NULL);
	pthread_join(p2, NULL);
	pthread_join(p3, NULL);
	return (0);
}