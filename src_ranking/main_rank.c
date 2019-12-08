/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_scc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaaouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 23:32:59 by mmaaouni          #+#    #+#             */
/*   Updated: 2019/12/08 03:04:25 by mmaaouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rank.h"

/*
** Checks that between two vertices all paths contain an unmarked vertex 
** or a vertex of a higher rank
*/

int		all_paths_are_good(t_graph *g, int src, int dest, int rank)
{
	size_t pos = 0;
	int		tag = 0;

	while (pos < g->paths[src]->used)
	{
		if (g->paths[src]->path[pos].tab[g->paths[src]->path[pos].used - 1] != dest )
		{
			pos++;
			continue;
		}
		tag = 0;
		if ((int)g->paths[src]->path[pos].used <= 2)
			return 0;
		for (int i = 1; i < (int)g->paths[src]->path[pos].used - 1; i++)
		{
			if (g->rank[g->paths[src]->path[pos].tab[i]] == 0 || g->rank[g->paths[src]->path[pos].tab[i]] > rank)
			{
				tag = 1;
				break;
			}
		}
		if (!tag)
			return 0;
		pos++;
	}
	return 1;
}

void	rank(t_graph *g, int root)
{
	t_queue_int *kyou = (t_queue_int*)malloc(sizeof(t_queue_int));
	kyou->size = 0;
	int			front;
	int			doable = 1;
	t_qlayer_int *tmp = (t_qlayer_int*)malloc(sizeof(t_qlayer));

	tmp->node = root;
	push_q_i(kyou, tmp);

	while (kyou->size > 0)
	{
		front = kyou->head->node;
		for (int  pos_rank = 1; pos_rank <= g->vertx; pos_rank++)
		{
			doable = 1;
			// checks if it is doable to assign this rank to this node with all vertices of the same rank
			for (int j = 0; j < (int)g->ranked[pos_rank].used; j++)
			{
				doable &= all_paths_are_good(g, front, g->ranked[pos_rank].tab[j], pos_rank);
				doable &= all_paths_are_good(g, g->ranked[pos_rank].tab[j], front, pos_rank);
			}
			if (doable)
			{
				g->rank[front] = pos_rank;
				push_back(&(g->ranked[pos_rank]), front);
				break;
			}
		}
		for (int i = 0; i < (int)g->adj[front].used; i++)
		{
			if (g->rank[g->adj[front].tab[i]] == 0)
			{
				t_qlayer_int *tt = (t_qlayer_int*)malloc(sizeof(t_qlayer));
				tt->node = g->adj[front].tab[i];
				push_q_i(kyou, tt);
			}
		}
		pop_q_i(kyou);
	}
}

int main()
{
	t_graph *g;
	g = generate_graph();
	init_paths(g);
	int unexplored = 1;
	// finds all paths between all points
	for (int i = 0; i < g->vertx; i++)
		find_all_paths(g, i);
	// loops over all scc s
	while (unexplored)
	{
		unexplored = 0;
		// greedy search for a minimal ranking
		rank(g, g->search);
		// check for unexplored vertices
		for (int i = 0; i < g->vertx; i++)
			if (g->rank[i] == 0)
			{
			   unexplored = 1;
			   g->search = i;
			}
	}
	for (int i = 0; i < g->vertx; i++)
		printf("%d ", g->rank[i]);
}
