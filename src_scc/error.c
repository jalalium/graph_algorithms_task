#include "scc.h"

int		error_edge(t_pair *got, int i)
{
	printf("WRONG EDGE %d %d \n", got[i].x + 1, got[i].y + 1);
	return 0;
}

void	error(int a)
{
	if (a == WRONG_INPUT)
		printf("WRONG NUMBER OF VERTICES OF EDGES\n");
	else if (a == WRONG_EDGE)
		printf("WRONG EDGE\n");
	exit(0);
}
