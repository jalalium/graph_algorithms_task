#include "scc.h"

void	print_components(t_graph *g)
{
	t_component *tmp = g->head;

	if (g->components == 1)
		printf(BOLDWHITE "There is 1 strongly connected component:\n" RESET);
	else
		printf(BOLDWHITE "There are %d strongly connected components:\n" RESET, g->components);
	while (tmp != NULL)
	{
		if (tmp->type == 0)
		{
			printf(CYAN "A simple vertex and contains:\n" RESET);
			printf("%d\n", tmp->list->tab[0] + 1);
		}
		else if (tmp->type == 1)
		{
			printf(CYAN "A cycle of length %d and contains:\n" RESET,tmp->vrx_nb);
			for (int i = 0 ; i < tmp->list->used; i++)
				printf("%d ", tmp->list->tab[i] + 1);
			puts("");
		}
		else
		{
			printf(CYAN "A complex strong component with %d edges and %d vertices and contains:\n" RESET, tmp->edg_nb, tmp->vrx_nb);
			for (int i = 0 ; i < tmp->list->used; i++)
				printf("%d ", tmp->list->tab[i] + 1);
			puts("");
		}
		tmp = tmp->next;
	}
}
