#ifndef A_STAR_H
# define A_STAR_H

typedef struct s_game t_game;

typedef struct	s_star_node
{
	int			g_cost;
	int			f_cost;
	t_vec2			pos;
	struct	s_star_node	*parent;
	struct	s_star_node	*next;
}		t_star_node;


void	print_vector_path(t_game *game);

#endif
