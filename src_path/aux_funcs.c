#include "path.h"


void swap(int *a, int *b)
{
	int tmp = *a;
	
	*a = *b;
	*b = tmp;
}

//creates a state that will be the next spur path

t_qlayer	*create_state(int node, t_vect *path)
{
	t_qlayer	*new = (t_qlayer*)malloc(sizeof(t_qlayer));
	t_vect		*copy = (t_vect*)malloc(sizeof(t_vect));

	init_vector(copy);
	for (int i = 0;i < path->used; i++)
		push_back(copy, path->tab[i]);
	new->prefix = copy;
	new->node = node;
	return new;
}

//appends a vertex to a path

t_vect	*append(t_vect *src, int add)
{
	t_vect		*copy = (t_vect*)malloc(sizeof(t_vect));

	init_vector(copy);
	for (int i = 0;i < src->used; i++)
		push_back(copy, src->tab[i]);
	push_back(copy, add);
	return copy;
}
