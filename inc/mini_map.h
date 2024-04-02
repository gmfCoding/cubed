#ifndef MINI_MAP_H
# define MINI_MAP_H

#include <mlx.h>
#include <stdlib.h>
#include "vector2.h"
#include "texture.h"
#include "map.h"
#include "config.h"

//int mapX=6,mapY=6,mapS=32,mapSS=24;

//# define MAP_WIDTH 6
//# define MAP_HEIGHT 6
//# define SCR_CENTER_X (SCR_WIDTH / 2)
//# define SCR_CENTER_X (SCR_HEIGHT / 2)
# define MAP_CASE 128
# define MAP_POS_X (140 - MAP_CASE)
# define MAP_POS_Y (SCR_HEIGHT - 140 - MAP_CASE)
# define MAP_S 24

typedef struct s_game t_game;
typedef struct s_app t_app;

typedef struct s_mm_tile
{
	t_texture	*img;
	t_vec2		pos;
	int16_t		ref;
	bool		vis;
	bool		vertical;
	bool		alert;
}		t_mm_tile;

typedef struct	s_mmap
{
	t_texture	mm_img[26];
	t_texture	img_case[4];
	t_texture	img_pp;
	t_texture	img_pr;
	t_mm_tile	tiles[MAP_MAX_X * MAP_MAX_Y];
	t_vec2		al_pos;
	bool		mm_small;
	bool		mm_big;
	bool		alert_m;
	bool		alert_h;
}			t_mmap;

void	mmap_init(t_game *game);
void	mmap_draw(t_game *game);
void	mmap_input(t_game *game, t_mmap *mmap);

void	mmap_draw_case_anim(t_game *game, t_vec2 pos);
void	mmap_draw_alert_anim(t_game *game, t_texture *img, t_vec2 pos, int i);
int	mmap_decide_img(t_tile *tile, int w, int h, int pos);
void	mmap_init_img_1(t_mmap *mmap, void *mlx);
int	mmap_tile_assign(t_game *game, int i, int y);

#endif
