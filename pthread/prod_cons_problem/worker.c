#include "worker.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void *reaction_keypress(void *args_thread)
{
	t_thread_args	*args;
	char			*temp;
	int				str_length;

	args = args_thread;
	while (1)
	{
		pthread_cond_wait(&args->thread_cond, &args->mut_thread_cond);
		str_length = strlen(args->arg_str);
		temp = malloc(str_length + 1);
		if (!temp)
		{
			write(2, "malloc fail\n", 12);
			return (NULL);
		}
		strlcpy(temp, args->arg_str, str_length + 1);
		sleep(2);
		str_to_upper(temp);
		output_thread(args->thread_num, temp, str_length);
		free(temp);
	}
}