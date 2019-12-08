#include "rank.h"

void	push_q_i(t_queue_int *que, t_qlayer_int *new)
{
	if (que->size == 0)
	{
		new->next = NULL;
		new->prev = NULL;
		que->head = new;
		que->tail = new;
	}
	else
	{
		new->prev = que->tail;
		que->tail->next = new;
		que->tail = new;
		new->next = NULL;
	}
	que->size++;
}

void	pop_q_i(t_queue_int *que)
{
	t_qlayer_int *tmp;
	if (que->size < 1)
		return;
	else
		tmp = que->head->next;
		que->head = tmp;
		que->size--;
}

