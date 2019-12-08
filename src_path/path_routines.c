#include "path.h"

/*
**	Path storing routines
*/

void	init_paths(t_graph *g)
{
	t_paths *new = (t_paths*)malloc(sizeof(t_paths));

	new->path = (t_vect*)malloc(sizeof(t_vect)*50);
	for (int i = 0; i < 50; i++)
		init_vector(&new->path[i]);
	new->size = 50;
	new->used = 0;
	g->paths = new;
}

void	extend_paths(t_graph *g)
{
	size_t new_size = g->paths->size * 2;

	t_vect *copy = (t_vect*)malloc(sizeof(t_vect)*new_size); 
	for (int i = 0; i < new_size; i++)
		init_vector(&copy[i]);
	for (int i = 0; i < g->paths->size; i++)
	{
		for (int j = 0; j < g->paths->path[i].used; j++)
			push_back(&copy[i],g->paths->path[i].tab[j]);
		free(g->paths->path[i].tab);
	}
	free(g->paths->path);
	g->paths->path = copy;
	g->paths->size = new_size;
}

void	add_path(t_graph *g, t_vect *new)
{
	size_t pos = g->paths->used;
	size_t size = g->paths->size;

	if (pos >= size)
		extend_paths(g);
	for (int i = 0 ; i < new->used; i++)
		push_back(&g->paths->path[pos], new->tab[i]);
	g->paths->used++;
}
