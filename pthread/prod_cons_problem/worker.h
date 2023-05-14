
#pragma once

#ifndef WORKER_H_
# define WORKER_H_

#include <pthread.h>

typedef struct s_thread_args
{
	pthread_t		thread_ident;
	int				thread_num;
	const char		*arg_str;
	pthread_mutex_t	mut_str;
	pthread_cond_t	thread_cond;
	pthread_mutex_t	mut_thread_cond;
}	t_thread_args;

int		init_thread_args(t_thread_args *arg, int thr_num, char *str);

void	str_to_upper(char *str);
void	output_thread(int thr_num, char *str, size_t str_length);

#endif