#include "scc.h"

t_graph *generate_graph()
{
	t_graph *new = (t_graph*)malloc(sizeof(t_graph));
	new->head = NULL;
	new->tail = NULL;
	new->components = 0;
	if (!get_dimensions(new))
		error(WRONG_INPUT);
	if (!get_edges(new))
		error(WRONG_EDGE);
	return (new);
}

void	dfs(int x, t_graph *g, t_stack *out)
{
	t_stack	*stk = (t_stack*)malloc(sizeof(t_stack));
	stk->size = 0;
	int tag;
	int top;

	push(stk,x);
	while (stk->size > 0)
	{
		tag = 0;
		top = stk->top->val;
		g->visited[top] = 1;
		for (int i = 0; i < g->adj[top].used; i++)
		{
			if (g->visited[g->adj[top].tab[i]] == 0)
			{
				push(stk, g->adj[top].tab[i]);
				tag = 1;
			}
		}
		if (!tag)
		{
			push(out, top);
			pop(stk);
		}
	}
	free(stk);
}

//stacks vertices to be processed in second pass

t_stack	*first_pass(t_graph *g)
{
	t_stack	*out = (t_stack*)malloc(sizeof(t_stack));
	out->size = 0;
	memset(g->visited,0,sizeof(int)*g->vertx);
	for (int i = 0; i < g->vertx; i++)
	{
		if (g->visited[i] == 0)
			dfs(i, g, out);
	}
	return out;
}

//gets components from the transpose graph

void	second_pass(t_graph *g, t_stack *stk)
{
	memset(g->visited,0,sizeof(int)*g->vertx);
	while (stk->size > 0)
	{
		if (g->visited[stk->top->val] == 0)
			get_component(g,stk->top->val,++g->components);
		pop(stk);
	}
}

/*
**	Kosaraju's algorithm
*/

void	find_scc(t_graph *g)
{
	t_stack *stk = first_pass(g); 
	second_pass(g, stk);
	free(stk);
}

int main()
{
	t_graph *g;
	g = generate_graph();
	find_scc(g);
	print_components(g);
	free_graph(g);
}
