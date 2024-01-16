#ifndef PLAYER_H
# define PLAYER_H

# include "vector2.h"
typedef struct s_game t_game;
typedef struct s_list t_list;

typedef struct s_player
{
	t_vec2 pos;
	t_vec2 dir;
	t_vec2 plane;

	double moveSpeed;
	double rotSpeed;
}	t_player;

void	player_setup(t_list *curr, t_game *game);

#endif
