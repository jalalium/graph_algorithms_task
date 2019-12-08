#include "rank.h"


int		cmp_path(const void *p, const void *q)
{
	size_t lastp = ((t_vect*)p)->used;
	size_t lastq = ((t_vect*)q)->used;
	if ((*(t_vect*)p).tab[lastp-1] == (*(t_vect*)q).tab[lastq-1])
		return (((t_vect*)p)->used - ((t_vect*)q)->used);
	return ((*(t_vect*)p).tab[lastp-1] - (*(t_vect*)q).tab[lastq-1]);
}

int cmp_int(const void *p, const void *q)
{
	return (*(int*)p - *(int*)q);
}

