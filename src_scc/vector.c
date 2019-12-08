#include "scc.h"

/*
** Implementation of extendable arrays
*/

int	init_vector(t_vect *v)
{
	v->size = 50;
	v->used = 0;
	if (!(v->tab = (int*)malloc(sizeof(int)*50)))
		return 0;
	return 1;
}

void	extend_vector(t_vect *v, int a)
{
	size_t	size = v->size;
	size_t	new_size = size * 2;
	int		*new_nodes = (int*)malloc(sizeof(int)*new_size);

	copy_vector(v->tab, new_nodes, size);
	free(v->tab);
	v->size = new_size;
	v->tab = new_nodes;
}

void	push_back(t_vect *v, int val)
{
	size_t pos = v->used;
	size_t size = v->size;

	if (pos + 1 == size)
		extend_vector(v, val);
	v->tab[pos] = val;
	v->used++;
}

void	copy_vector(int *src, int *dst, size_t size)
{
	for (int i = 0; i < size; i++)
		dst[i] = src[i];
}
