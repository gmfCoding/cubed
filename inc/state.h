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

typedef struct s_player t_player;

struct s_player
{
	t_vec2 pos;
	t_vec2 dir;
	t_vec2 plane;

	double moveSpeed;
	double rotSpeed;
};

struct s_game
{
	void *mlx;
	void *win;

	t_texture rt0;
	t_texture rt1;

	t_vec2 mouse;
	t_vec2 pos;

	t_debug_texture views[MAX_DEBUG_VIEWS];
	int view_count;

	t_player	player;
};

void texture_debug_view_blit(t_game *game, int view, t_texture tex, t_vec2 pos);
void texture_draw_debug_view(t_game *game, int view);
t_texture texture_get_debug_view(t_game *game, int view);

#endif