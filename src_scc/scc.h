#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define  WRONG_INPUT 0
#define  WRONG_EDGE 1
#define RESET   "\033[0m"
#define CYAN    "\033[36m"
#define BOLDWHITE   "\033[1m\033[37m"

#ifndef	SCC_H
# define	SCC_H

typedef struct	s_vect
{
	int			*tab;
	size_t		size;
	size_t		used;
}				t_vect;

typedef struct 			s_component
{
	struct s_vect		*list;
	struct s_component	*next;
	int					type;
	int					vrx_nb;
	int					edg_nb;
}						t_component;

typedef struct			s_graph
{
	struct s_vect		*adj;
	struct s_vect		*rev_adj;
	struct s_component	*head;
	struct s_component	*tail;
	int					*visited;
	int 				components;
	int 				vertx;
	int 				edg;
	int 				in_edg;
}						t_graph;

typedef struct		s_pair
{
	int				x;
	int				y;
}					t_pair;

typedef struct		s_layer
{
	struct s_layer	*prev;
	struct s_layer	*next;
	int				val;
}					t_layer;

typedef struct		s_stack
{
	struct s_layer	*top;
	size_t			size;
}					t_stack;

/*
**	VECTOR FUNCTIONS
*/

int	init_vector(t_vect *v);
void	extend_vector(t_vect *v, int a);
void	push_back(t_vect *v, int val);
void	copy_vector(int *src, int *dst, size_t size);
#endif

/*
**	STACK FUNCTIONS
*/

void	pop(t_stack *stk);
void	push(t_stack *stk, int val);

/*
**	Validation functions
*/

int 	valid_dimensions(int n, int m, t_graph *g);
int	valid_edge(t_pair *got, int i, t_graph *g);

/*
**	Error FUNCTIONS
*/

int		error_edge(t_pair *got, int i);
void		error(int a);

/*
**	Graph FUNCTIONS
*/

int 		get_edges(t_graph *g);
int		get_dimensions(t_graph *new);
int 		cmp_int(const void *p, const void *q);
void		get_component(t_graph *g, int src, int cycl);
void		print_components(t_graph *g);
void		free_graph(t_graph *g);