#include "worker.h"
#include "utils.h"
#include <unistd.h>

int	init_thread_args(t_thread_args *arg, int thr_num, char *str)
{
	arg->thread_num = thr_num;
	pthread_mutex_init(&arg->mut_str, NULL);
	pthread_mutex_init(&arg->mut_thread_cond, NULL);
	pthread_cond_init(&arg->thread_cond, NULL);
	arg->arg_str = str;
	return (1);
}

int	thread_run(void)
{

}

int main(void)
{
	
}