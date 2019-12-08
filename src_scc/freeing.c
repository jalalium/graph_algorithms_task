#include "scc.h"

void	free_components(t_graph *g)
{
	t_component *tmp;
	t_component *tmp1;

	tmp = g->head;
	while (tmp != NULL)
	{
		tmp1 = tmp->next;
		free(tmp->list->tab);
		free(tmp->list);
		free(tmp);
		tmp = tmp1;
	}
}

void	free_graph(t_graph *g)
{
	free(g->visited);
	for (int i = 0; i < g->vertx; i++)
	{
		free(g->adj[i].tab);
		free(g->rev_adj[i].tab);
	}
	free(g->adj);
	free(g->rev_adj);
	free_components(g);
	free(g);
}
