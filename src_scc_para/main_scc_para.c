/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_scc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaaouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 23:32:59 by mmaaouni          #+#    #+#             */
/*   Updated: 2019/12/08 02:55:17 by mmaaouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scc_para.h"
t_graph *G;
pthread_mutex_t mutex;

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
	new->scc = (int*)malloc(sizeof(int)*new->vertx);
	new->vis = (int*)malloc(sizeof(int)*new->vertx);
	memset(new->scc, -1, sizeof(int) * new->vertx);
	memset(new->vis, 0, sizeof(int) * new->vertx);
	return (new);
}

t_resource	*init_resource(pthread_mutex_t *m, t_vect *v)
{
	t_resource *new = (t_resource*)malloc(sizeof(t_resource));
	new->mtx = m;
	new->list = v;
	return new;
}

int		find(t_vect *v, int r)
{
	int low = 0;
	int hi = v->used;
	while (low <= hi)
	{
		int mid = (low+hi)/2;
		if (v->tab[mid] == r)
			return 1;
		else if (v->tab[mid] > r)
			hi = mid-1;
		else
			low = mid+1;
	}
	return 0;
}

void	*kernel(void *res)
{
	pthread_t tr[3];
	t_resource  *all = (t_resource*)res;
	t_vect list = *(all->list);
	t_vect dir_reach;
	t_vect ind_reach;
	t_stack	stk;
	int mark;

	pthread_mutex_lock(all->mtx);
	//inits the forward and backward reach vectors
	init_vector(&dir_reach);
	init_vector(&ind_reach);
	//In order to avoid redoing the same vertex twice
	if (G->scc[list.tab[0]] != -1)
	{
		pthread_mutex_unlock(all->mtx);
		return NULL;
	}
	//Case of single vertex SCC
	if (list.used < 2)
	{
		pthread_mutex_unlock(all->mtx);
		puts("New connected component");
		printf("%d\n", list.tab[0] + 1);
		G->scc[list.tab[0]] = list.tab[0];
		return (NULL);
	}
	qsort(list.tab, list.used,sizeof(int), cmp_int);
	push(&stk, list.tab[0]);
	G->vis[list.tab[0]] = 1;
	//forward reach of the pivot
	while (stk.size > 0)
	{
		int top = stk.top->val;
		int tag = 0;
		for (int i = 0; i < G->adj[top].used; i++)
		{
			if (find(&list, G->adj[top].tab[i]) && G->vis[G->adj[top].tab[i]] == 0 && G->scc[G->adj[top].tab[i]] == -1)
			{
				tag = 1;
				G->vis[G->adj[top].tab[i]] = 1;
				push_back(&dir_reach, G->adj[top].tab[i]);
				push(&stk, G->adj[top].tab[i]);
			}
		}
		if (!tag)
			pop(&stk);
	}
	//to avoid recreating a visited array
	for (int i = 0; i < dir_reach.used; i++)
		G->vis[dir_reach.tab[i]] = 0;
	push(&stk, list.tab[0]);
	//Backward reach of the pivot
	while (stk.size > 0)
	{
		int top = stk.top->val;
		int tag = 0;
		for (int i = 0; i < G->rev_adj[top].used; i++)
			if (find(&list, G->rev_adj[top].tab[i]) && G->vis[G->rev_adj[top].tab[i]] == 0 && G->scc[G->rev_adj[top].tab[i]] == -1)
			{
				tag =1;
				G->vis[G->rev_adj[top].tab[i]] = 1;
				push_back(&ind_reach, G->rev_adj[top].tab[i]);
				push(&stk, G->rev_adj[top].tab[i]);
			}
		if (!tag)
		pop(&stk);
	}
	//to avoid recreating a visited array
	G->vis[list.tab[0]] = 0;
	for (int i = 0; i < ind_reach.used; i++)
		G->vis[ind_reach.tab[i]] = 0;
	mark = list.tab[0];
	G->scc[list.tab[0]] = mark;
	t_vect *child = (t_vect*)malloc(sizeof(t_vect)*3);
	for (int i = 0; i < 3; i++)
		init_vector(&child[i]);
	//sort of forward and backward reach in order to search in log(n) with binary search
	qsort(dir_reach.tab, dir_reach.used,sizeof(int), cmp_int);
	qsort(ind_reach.tab, ind_reach.used,sizeof(int), cmp_int);
	puts("New connected component");
	printf("%d ", list.tab[0] + 1);
	for (int i = 1; i < list.used; i++)
	{
		//checks if vertex is in forward reach
		int dir = find(&dir_reach, list.tab[i]);
		//checks if vertex is in backward reach
		int ind = find(&ind_reach, list.tab[i]);
		//Case 1: in Scc so printed
		if (dir&ind)
		{
			printf("%d ", list.tab[i] + 1);
			G->scc[list.tab[i]] = mark;
		}
		//Case 2: Only if forward reach -> group 1
		else if (dir)
			push_back(&child[0], list.tab[i]);
		//Case 3: Only if backward reach -> group 2
		else if (ind)
			push_back(&child[1], list.tab[i]);
		//Case 4: not reachable -> group 3
		else
			push_back(&child[2], list.tab[i]);	
	}
	puts("");
	pthread_mutex_unlock(all->mtx);
	//recursive parallel call to the 3 subproblems
	t_resource **out = (t_resource**)malloc(sizeof(t_resource*)*3);
	for (int i = 0; i < 3; i++)
		out[i] = init_resource(all->mtx, &child[i]);
	for (int i = 0; i < 3; i++)
		pthread_create(&tr[i], NULL, kernel, out[i]);
	for (int i = 0; i < 3; i++)
		pthread_join(tr[i], NULL);
	return NULL;
}

void	initiate_vertices(t_vect *v)
{
	init_vector(v);
	for (int i = 0; i < G->vertx; i++)
		push_back(v, i);
}

int main()
{
	pthread_t ol;
	pthread_mutex_t mutex;
	t_vect new;

	G = generate_graph();
	pthread_mutex_init(&mutex, NULL);
	//puts all vertices as the first problem
	initiate_vertices(&new);
	t_resource *res = init_resource(&mutex, &new);
	pthread_create(&ol, NULL, kernel, res);
	pthread_join(ol, NULL);
}
