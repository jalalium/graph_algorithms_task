#ifndef PATH_H
# define PATH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define  WRONG_INPUT 0
#define  WRONG_EDGE 1
#define RESET   "\033[0m"
#define CYAN    "\033[36m"
#define BOLDWHITE   "\033[1m\033[37m"

typedef struct	s_vect
{
	int			*tab;
	size_t		size;
	size_t		used;
}				t_vect;

typedef struct	s_paths
{
	struct	s_vect	*path;
	size_t			size;
	size_t			used;
}				t_paths;

typedef struct			s_graph
{
	struct s_vect		*adj;
	struct s_paths		*paths;
	int 				vertx;
	int 				edg;
	int 				in_edg;
	int					start;
	int					direct;
}						t_graph;

typedef	struct			s_qlayer
{
	struct s_vect		*prefix;
	struct s_qlayer		*prev;
	struct s_qlayer		*next;
	int					node;
}						t_qlayer;

typedef struct			s_queue
{
	struct s_qlayer		*head;
	struct s_qlayer		*tail;
	size_t				size;
}						t_queue;

typedef struct		s_pair
{
	int				x;
	int				y;
}					t_pair;

/*
**	VECTOR FUNCTIONS
*/

int	init_vector(t_vect *v);
void	extend_vector(t_vect *v, int a);
void	push_back(t_vect *v, int val);
void	copy_vector(int *src, int *dst, size_t size);

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

void		get_component(t_graph *g, int src, int cycl);
void		print_components(t_graph *g);
void		free_graph(t_graph *g);
t_graph 	*generate_graph();


/*
**	Comparators FUNCTIONS
*/

int 		cmp_int(const void *p, const void *q);
int		cmp_path(const void *p, const void *q);

/*
**	Validation FUNCTIONS
*/

int		valid_params(int dir, int node, t_graph *g);
int		valid_edge(t_pair *got, int i, t_graph *g);
int 		valid_dimensions(int n, int m, t_graph *g);

/*
**	Queue FUNCTIONS
*/


t_queue	*init_queue();
void	push_q(t_queue *que, t_qlayer *new);
void	pop_q(t_queue *que);

/*
**	Path FUNCTIONS
*/

void	init_paths(t_graph *g);
void	extend_paths(t_graph *g);
void	add_path(t_graph *g, t_vect *new);

/*
**	Aux FUNCTIONS
*/

void 		swap(int *a, int *b);
t_qlayer	*create_state(int node, t_vect *path);
t_vect		*append(t_vect *src, int add);

/*
**	Printing FUNCTIONS
*/

void	print_paths(t_graph *g);

#endif
