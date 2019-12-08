NAME1 = scc
NAME2 = scc_para
NAME3 = paths
NAME4 = RANKING
FILES1 = src_scc/components.c\
		 src_scc/create_graph.c\
		 src_scc/error.c\
		 src_scc/freeing.c\
		 src_scc/main_scc.c\
		 src_scc/print_component.c\
		 src_scc/stack.c\
		 src_scc/validation.c\
		 src_scc/vector.c
FILES2 = src_scc_para/main_scc_para.c\
		 src_scc_para/create_graph.c\
		 src_scc_para/error.c\
		 src_scc_para/stack.c\
 		 src_scc_para/vector.c\
		 src_scc_para/validation.c
FILES3 = src_path/aux_funcs.c\
		 src_path/comparators.c\
		 src_path/errors.c\
		 src_path/free.c\
		 src_path/graph.c\
		 src_path/main_paths.c\
		 src_path/path_routines.c\
		 src_path/print_paths.c\
		 src_path/queue.c\
		 src_path/validation.c\
		 src_path/vector.c
FILES4 = src_ranking/aux_funcs.c\
		 src_ranking/comparators.c\
		 src_ranking/error.c\
		 src_ranking/graph.c\
		 src_ranking/main_rank.c\
		 src_ranking/path_routines.c\
		 src_ranking/queue.c\
		 src_ranking/validation.c\
		 src_ranking/queue_int.c\
		 src_ranking/vector.c

all: $(NAME1) $(NAME2) $(NAME3) $(NAME4)

$(NAME1):
		gcc -I ../src_scc/scc.h $(FILES1) -o scc
$(NAME2):
		gcc -I ../src_scc/scc_para.h $(FILES2) -o scc_para
$(NAME3):
		gcc -I ../src_scc/scc.h $(FILES3) -o paths
$(NAME4):
		gcc -I ../src_scc/scc.h $(FILES4) -o ranking
fclean:
		rm -r $(NAME1) $(NAME2) $(NAME3) $(NAME4)
