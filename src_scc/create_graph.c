#include "scc.h"

int cmp_int(const void *p, const void *q)
{
	return (*(int*)p - *(int*)q);
}

int	init_adj(t_graph *g)
{
	if(!(g->adj = (t_vect*)malloc(sizeof(t_vect)*g->vertx)))
		return 0;
	if(!(g->rev_adj = (t_vect*)malloc(sizeof(t_vect)*g->vertx)))
		return 0;
	for (int i = 0; i < g->vertx; i++)
		if (!(init_vector(&g->adj[i])))
			return 0;
	for (int i = 0; i < g->vertx; i++)
		if (!(init_vector(&g->rev_adj[i])))
			return 0;
	return 1;
}

//gets the number of vertices and edges

int		get_dimensions(t_graph *new)
{
	int n,m;

	scanf("%d %d", &n, &m);
	if (!valid_dimensions(n,m,new))
	{
		free(new);
		return 0;
	}
	if (!init_adj(new))
		return 0;
	if (!(new->visited = (int*)malloc(sizeof(int) * new->vertx)))
		return 0;
	return 1;
}

//adds edge

void	add_edge(t_graph *g, int a, int b)
{
	g->edg++;
	push_back(&g->adj[a],b);
}

//adds edge in transpose graph

void	add_redge(t_graph *g, int a, int b)
{
	push_back(&g->rev_adj[a],b);
}

void	insert_edges(t_pair *got, t_graph *g)
{
	int i = -1;

	while (++i < g->in_edg)
			add_edge(g, got[i].x,got[i].y);
}

void	insert_redges(t_pair *got, t_graph *g)
{
	int i = -1;

	while (++i < g->in_edg)
			add_redge(g, got[i].y, got[i].x);
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
	insert_redges(got, g);
	free(got);
	return 1;
}
