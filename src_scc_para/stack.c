#include "scc_para.h"

void	pop(t_stack *stk)
{
	t_layer		*tmp;

	if (stk->size <= 0)
		return ;
	if (stk->size == 1)
	{
		free(stk->top);
		stk->size--;
		return ;
	}
	tmp = stk->top->prev;
	free(stk->top);
	stk->top = tmp;
	stk->top->next = NULL;
	stk->size--;
}

void	push(t_stack *stk, int val)
{
	t_layer *new = (t_layer*)malloc(sizeof(t_layer));
	
	new->val = val;
	if (stk->size == 0)
		stk->top = new;
	else
	{
		new->next = NULL;
		new->prev = stk->top;
		stk->top->next = new;
		stk->top = new;
	}
	stk->size++;
}
