
#pragma once

#ifndef WORKER_H_
# define WORKER_H_

#include <pthread.h>

#define queue_size 30

typedef struct s_work
{
	int				keycode;
	struct s_work	*prev;
	struct s_work	*next;
}	t_work;

typedef struct s_waiting_queue
{
	t_work	*head;
	t_work	*last;
	int		cnt;
	pthread_cond_t	full;
	pthread_cond_t	empty;
	pthread_mutex_t	mut_thread_cond;
}	t_waiting_queue;

typedef struct s_thread_args
{
	pthread_t		thread_ident;
	int				thread_num;
	const char		*arg_str;
	t_waiting_queue	*queue;
}	t_thread_args;

int		init_thread_args(t_thread_args *arg, int thr_num, char *str);

void	str_to_upper(char *str);
void	output_thread(int thr_num, char *str, size_t str_length);

#endif