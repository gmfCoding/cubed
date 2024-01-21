#ifndef MINI_MAP_H
# define MINI_MAP_H

#include "state.h"
#include "map.h"
#include "config.h"
#include <mlx.h>
#include <stdlib.h>

//int mapX=6,mapY=6,mapS=32,mapSS=24;

//# define MAP_WIDTH 6
//# define MAP_HEIGHT 6
//# define SCR_CENTER_X (SCR_WIDTH / 2)
//# define SCR_CENTER_X (SCR_HEIGHT / 2)

# define MAP_POS_X 120
# define MAP_POS_Y (SCR_HEIGHT - 140)
# define MAP_S 24

typedef struct s_game t_game;


typedef struct s_mm_tile
{
	t_texture	*img;
	t_vec2		pos;

}		t_mm_tile;

typedef struct s_mmap
{
	t_texture	mm_img[20];
	void		*img;
	t_texture	img_case;
	t_mm_tile	tiles[MAP_MAX_X * MAP_MAX_Y];
	int		mmap_size;

}		t_mmap;

void	mmap_init(t_game *game);

void	mmap_draw(t_texture dst, t_mm_tile *tile, t_vec2 p_pos);

//void	draw_mini_map(t_game *game);
#endif
