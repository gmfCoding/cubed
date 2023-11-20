#ifndef STATE_H
# define STATE_H
#include "texture.h"

typedef struct s_game t_game;

#define MAX_DEBUG_VIEWS 10
typedef struct s_debug_texture t_debug_texture;
struct s_debug_texture
{
	void *win;
	t_texture rt;
};

struct s_game
{
	void *mlx;
	void *win;

	t_texture rt0;
	t_texture tex;
	t_vec2 mouse;
	t_vec2 pos;

	t_debug_texture views[MAX_DEBUG_VIEWS];
	int view_count;

	int debug;
};

void texture_debug_view(t_game *game, int view, t_texture tex, t_vec2 pos);
#endif