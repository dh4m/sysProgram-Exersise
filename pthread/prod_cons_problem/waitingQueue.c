#include "worker.h"

int queue_input(t_waiting_queue *q, int keycode)
{
	t_work	*work;

	work = malloc(sizeof(t_work));
	if (!work)
		exit(1);
	work->keycode = keycode;
	work->next = NULL;
	if (!q->head)
	{
		work->prev = NULL;
		q->head = work;
		q->last = work;
	}
	else
	{
		work->prev = q->last;
		q->last->next = work;
		q->last = q->last->next;
	}
	q->cnt++;
	return (0);
}

int queue_output(t_waiting_queue *q)
{
	if (!q->head)
	{
		////////
	}
}
