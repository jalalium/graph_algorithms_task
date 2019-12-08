#include "path.h"

void	free_paths(t_graph *g)
{
	for (int i = 0; i < g->paths->size; i++)
		free(g->paths->path[i].tab);
	free(g->paths->path);
	free(g->paths);
}

void	free_graph(t_graph *g)
{
	for (int i = 0; i < g->vertx; i++)
		free(g->adj[i].tab);
	free(g->adj);
	free_paths(g);
	free(g);
}

