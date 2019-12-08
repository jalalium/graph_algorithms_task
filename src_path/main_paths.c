/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_scc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaaouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 23:32:59 by mmaaouni          #+#    #+#             */
/*   Updated: 2019/12/08 02:46:19 by mmaaouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path.h"

void	find_all_paths(t_graph *g)
{
	t_vect *spur = (t_vect*)malloc(sizeof(t_vect));
	t_queue *bfs = init_queue(); 
	init_vector(spur);
	push_back(spur, g->start);
	init_paths(g);
	push_q(bfs, create_state(g->start, spur));
	while (bfs->size > 0)
	{
		t_qlayer *front = bfs->head;
		for (int i = 0; i < g->adj[front->node].used; i++)
		{
			for (int j = 0; j < front->prefix->used; j++)
				if (front->prefix->tab[j] == g->adj[front->node].tab[i])
					goto st;
			add_path(g, append(front->prefix, g->adj[front->node].tab[i]));
			push_q(bfs, create_state(g->adj[front->node].tab[i], append(front->prefix, g->adj[front->node].tab[i])));
			st:;
		}	
		pop_q(bfs);
	}
	free(spur->tab);
	free(spur);
	free(bfs);
}

int main()
{
	t_graph *g;
	g = generate_graph();
	find_all_paths(g);
	print_paths(g);
	free_graph(g);
}
