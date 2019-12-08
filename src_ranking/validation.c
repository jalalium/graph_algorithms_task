#include "rank.h"

int		valid_params(int dir, int node, t_graph *g)
{
	if (dir != 0 && dir != 1)
		return 0;
	if (node <= 0 || node > g->vertx)
		return 0;
	g->search = node - 1;
	g->direct = dir;
	return 1;
}

int		valid_edge(t_pair *got, int i, t_graph *g)
{
	got[i].x--;
	got[i].y--;
	if (got[i].x < 0 || got[i].x >= g->vertx)
	   return 0;
	if (got[i].y < 0 || got[i].y >= g->vertx)
		return 0;
	if (g->direct == 0 && got[i].x > got[i].y)
		swap(&got[i].x, &got[i].y);
	return 1;
}

int 	valid_dimensions(int n, int m, t_graph *g)
{
	if (n < 0 || m < 0)
		return 0;
	g->vertx = n;
	g->edg = 0;
	g->in_edg = m;
	return 1;
}

