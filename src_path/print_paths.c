#include "path.h"

void 	print_path_nb(t_graph *g)
{
	if (g->paths->used == 0)
		printf(BOLDWHITE "There is no path from vertex %d\n" RESET , g->start + 1);
	else if (g->paths->used == 1)
		printf(BOLDWHITE "There is 1 path from vertex %d\n" RESET , g->start + 1);
	else
		printf(BOLDWHITE "There are %zu paths from vertex %d\n" RESET , g->paths->used ,g->start + 1);
}

void	print_paths(t_graph *g)
{
	size_t i = 0;

	print_path_nb(g);
	qsort(g->paths->path,g->paths->used, sizeof(t_vect), cmp_path);
	while (i < g->paths->used)
	{
		int dest = g->paths->path[i].tab[g->paths->path[i].used - 1];
		printf(CYAN "Paths to vertex %d\n" RESET , dest + 1);
		while (i < g->paths->used && g->paths->path[i].tab[g->paths->path[i].used - 1] == dest)
		{
			for (int j = 0; j < g->paths->path[i].used; j++)
				printf("%d ", g->paths->path[i].tab[j] + 1);
			puts("");
			i++;
		}
	}
}
