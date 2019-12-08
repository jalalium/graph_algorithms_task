#include "path.h"

/*
**	Implementation of a queue as a linked list
*/

t_queue	*init_queue()
{
	t_queue *new = (t_queue*)malloc(sizeof(t_queue));
	new->size = 0;
	return new;
}

void	push_q(t_queue *que, t_qlayer *new)
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

void	pop_q(t_queue *que)
{
	t_qlayer *tmp;
	if (que->size < 1)
	{
		free(que->head->prefix->tab);
		free(que->head->prefix);
		free(que->head);
		return;
	}
	else
	{
		tmp = que->head->next;
		free(que->head->prefix->tab);
		free(que->head->prefix);
		free(que->head);
		que->head = tmp;
		que->size--;
	}
}
