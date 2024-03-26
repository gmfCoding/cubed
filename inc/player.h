#ifndef PLAYER_H
# define PLAYER_H

# include "vector2.h"
typedef struct s_game t_game;
typedef struct s_list t_list;

typedef struct	s_player
{
	t_vec2	pos;
	t_vec2	dir;
	t_vec2	plane;
	t_vec2	plane_start;
	t_vec2	plane_end;
	int	oldp_x;//this can be a t_vec2i also, or get rid of it all together and come up with another way to see if the player has moved to a new tile
	int	oldp_y;
	double	moveSpeed;
	double	rotSpeed;
	double	angle;
	double	key_angle;
}		t_player;

void	player_setup(t_list *curr, t_game *game);

#endif
