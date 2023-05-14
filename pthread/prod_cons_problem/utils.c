#include "utils.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int	islower(int c)
{
	return ('a' <= c && c <= 'z');
}

void	str_to_upper(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (islower(str[i]))
			str[i] = str[i] - ('a' - 'A');
		i ++;
	}
}

void	output_number(int num)
{
	char	buf;

	if (-10 < num && num < 10)
	{
		if (num < 0)
		{
			write(1, "-", 1);
			buf = -num - '0';
		}
		else
			buf = num - '0';
		write(1, &buf, 1);
		return ;
	}
	output_number(num / 10);
	if (buf < 0)
		buf = -(num % 10) - '0';
	else
		buf = (num % 10) - '0';
	write(1, &buf, 1);
}

void	output_thread(int thr_num, char *str, size_t str_length)
{
	write(1, "Thread -#", 9);
	output_number(thr_num);
	write(1, "- tells You!\n", 13);
	write(1, str, str_length);
	write(1, "\n\n", 2);
}