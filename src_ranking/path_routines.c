#include "rank.h"

void	init_paths(t_graph *g)
{
	t_paths **new = (t_paths**)malloc(sizeof(t_paths*) * g->vertx);

	for (int i = 0; i < g->vertx ; i++)
	{
		new[i] = (t_paths*)malloc(sizeof(t_paths));
		new[i]->path = (t_vect*)malloc(sizeof(t_vect)*50);
		for (int j = 0; j < 50; j++)
			init_vector(&new[i]->path[j]);
		new[i]->size = 50;
		new[i]->used = 0;
	}
	g->paths = new;
}

void	extend_paths(t_graph *g, int start)
{
	size_t new_size = g->paths[start]->size * 2;

	t_vect *copy = (t_vect*)malloc(sizeof(t_vect)*new_size); 
	for (int i = 0; i < (int)new_size; i++)
		init_vector(&copy[i]);
	for (int i = 0; i < (int)g->paths[start]->size; i++)
	{
		for (int j = 0; j < (int)g->paths[start]->path[i].used; j++)
			push_back(&copy[i],g->paths[start]->path[i].tab[j]);
	}
	g->paths[start]->path = copy;
	g->paths[start]->size = new_size;
}

void	add_path(t_graph *g, t_vect *new, int start)
{
	size_t pos = g->paths[start]->used;
	size_t size = g->paths[start]->size;

	if (pos >= size)
		extend_paths(g, start);
	for (int i = 0 ; i < (int)new->used; i++)
		push_back(&g->paths[start]->path[pos], new->tab[i]);
	g->paths[start]->used++;
}
