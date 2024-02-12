#ifndef A_STAR_H
# define A_STAR_H

# define DELTAS_LEN 8
# define DELTAS {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}}

typedef struct s_game t_game;

typedef struct	s_star_node
{
	int			g_cost;
	t_vec2			pos;
	struct	s_star_node	*parent;
	struct	s_star_node	*next;
}		t_star_node;


void    star_deallocate_node(t_star_node **node);
void    star_insert_node(t_game *game, t_star_node **node, t_star_node *parent, t_vec2 pos);
t_vec2	*star_construct_path(t_star_node *end_node, t_star_node **open, t_star_node **close);
t_vec2	*star_find_path(t_game *game, t_vec2 start, t_vec2 target);
void	print_vector_path(t_game *game);

#endif
