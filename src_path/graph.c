#include "path.h"

void	add_edge(t_graph *g, int a, int b)
{
	g->edg++;
	push_back(&g->adj[a],b);
	if (g->direct == 0)
	{
		g->edg++;
		push_back(&g->adj[b],a);
	}
}

void	insert_edges(t_pair *got, t_graph *g)
{
	int i = -1;

	while (++i < g->in_edg)
			add_edge(g, got[i].x, got[i].y);
}

int	init_adj(t_graph *g)
{
	if(!(g->adj = (t_vect*)malloc(sizeof(t_vect)*g->vertx)))
		return 0;
	for (int i = 0; i < g->vertx; i++)
		if (!(init_vector(&g->adj[i])))
			return 0;
	return 1;
}

int		get_dimensions(t_graph *new)
{
	int n, m, dir, node;

	scanf("%d %d %d %d", &n, &m, &dir, &node);
	if (!valid_dimensions(n,m,new))
	{
		free(new);
		return 0;
	}
	if (!valid_params(dir, node, new))
	{
		free(new);
		return 0;
	}
	if (!init_adj(new))
		return 0;
	return 1;
}

int 	get_edges(t_graph *g)
{
	t_pair *got = (t_pair*)malloc(sizeof(t_pair)*g->in_edg);

	for (int i = 0; i < g->in_edg; i++)
	{
		scanf("%d %d",&(got[i].x),&(got[i].y));
		if (!valid_edge(got, i, g))
			return (error_edge(got, i));
	}
	insert_edges(got, g);
	free(got);
	return 1;
}

t_graph *generate_graph()
{
	t_graph *new = (t_graph*)malloc(sizeof(t_graph));
	if (!get_dimensions(new))
		error(WRONG_INPUT);
	if (!get_edges(new))
		error(WRONG_EDGE);
	return (new);
}

