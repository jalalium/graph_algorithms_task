#include "scc.h"

//calculates number of edges in each scc

int		process_traversed(t_vect *edgs)
{
	int num = 0;

	qsort(edgs->tab, edgs->used, sizeof(int), cmp_int);
	for (int i = 0; i < edgs->used; i++)
		if (i == 0 || edgs->tab[i] != edgs->tab[i-1])
			num++;
	free(edgs->tab);
	free(edgs);
	return num;
}

t_component *init_component()
{
	t_component *new = (t_component*)malloc(sizeof(t_component));
	t_vect *l = (t_vect*)malloc(sizeof(t_vect));

	init_vector(l);
	new->vrx_nb = 0;
	new->edg_nb = 0;
	new->list = l;
	return (new);
}

void	fill_component(int x, t_graph *g, t_component *new, int cycl)
{
	t_stack	*stk = (t_stack*)malloc(sizeof(t_stack));
	t_vect	*edgs = (t_vect*)malloc(sizeof(t_vect));
	init_vector(edgs);
	stk->size = 0;
	int tag;
	int top;
	int cnt = 0;

	push(stk,x);
	g->visited[x] = cycl;
	while (stk->size > 0)
	{
		tag = 0;
		top = stk->top->val;
		for (int i = 0; i < g->rev_adj[top].used; i++)
		{
			if (g->visited[g->rev_adj[top].tab[i]] == 0)
			{
				g->visited[g->rev_adj[top].tab[i]] = cycl;
				push(stk, g->rev_adj[top].tab[i]);
				tag = 1;
			}
			else if (g->visited[g->rev_adj[top].tab[i]] == cycl)
				push_back(edgs, g->vertx * top + g->rev_adj[top].tab[i]);
		}
		if (!tag)
		{
			new->vrx_nb++;
			push_back(new->list,top);
			pop(stk);
		}
	}
	new->edg_nb = process_traversed(edgs);
	free(stk);
}

void	classify_component(t_component *c)
{
	if (c->edg_nb > c->vrx_nb)
		c->type = 2;
	else if (c->edg_nb == 0)
		c->type = 0;
	else
		c->type = 1;
}

void	add_component(t_graph *g, t_component *c)
{
	if (g->head == NULL)
	{
		g->head = c;
		g->tail = c;
		c->next = NULL;
	}
	else
	{
		g->tail->next = c;
		c->next = NULL;
		g->tail = c;
	}
}

void	get_component(t_graph *g, int src, int cycl)
{
	t_component *new = init_component();

	fill_component(src,g,new, cycl);
	classify_component(new);
	add_component(g, new);
}
