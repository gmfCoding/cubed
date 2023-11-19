#ifndef STATE_H
# define STATE_H
#include "texture.h"

typedef struct s_game t_game;

struct s_game
{
	void *mlx;
	void *win;

	t_texture rt0;

	t_vec2 mouse;
};
#endif