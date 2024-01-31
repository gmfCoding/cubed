

//mini_map set up stuff here VV

#include "mini_map.h"
#include "texture.h"
#include "state.h"
//mini_map setup stuff here ^^




// for vector_math_extra.s vvvv
/*
t_vec2	v2diff(t_vec2 f, t_vec2 s)
{
	t_vec2	vec;
	
	vec.x = 0;
	vec.y = 0;
	if (f.x > s.x)
		vec.x = f.x - s.x;
	else
		vec.x = s.x - f.x;
	if (f.y > s.y)
		vec.y = f.y - s.y;
	else
		vec.y = s.y - f.y;
	return (vec);
}
*/
// for vector_math_extra ^^^^


// in input vvvv
void	mmap_input(t_game *game)
{
	if (input_keydown(&game->input, KEY_M))
	{
		if(game->mmap.mm_small == true)
		{
			game->mmap.mm_big = true;
			game->mmap.mm_small = false;
		}
		else
		{
			game->mmap.mm_big = false;
			game->mmap.mm_small = true;
		}
	}
}
// in input ^^^^

//in update vvvv
int	mmap_is_inside(int x, int y)
{
	t_vec2 tile_pos = v2new(x, y);
	tile_pos = v2sub(tile_pos, v2new(MAP_POS_X, MAP_POS_Y));
	if (v2mag(tile_pos) > (MAP_CASE * 0.91))
		return (0);
	return (1);
}

void	mmap_draw_walls(t_texture dst, t_mm_tile *tile, t_vec2 p_pos, t_mmap mmap)
{
	int	i;
	t_vec2 pos;

	i = -1;
	while (tile[++i].img != NULL)
	{
		pos.x = tile[i].pos.x - p_pos.x * MAP_S;
		pos.y = tile[i].pos.y - p_pos.y * MAP_S;
		if (mmap.mm_big == true)
		{
			pos.x = ((tile[i].pos.x - MAP_POS_X - MAP_CASE) + (SCR_WIDTH / 2)) - p_pos.x * MAP_S;
			pos.y = ((tile[i].pos.y - MAP_POS_Y - MAP_CASE) + (SCR_HEIGHT / 2)) - p_pos.y * MAP_S;
			if (tile[i].vis == true || mmap_is_inside(pos.x - 455, pos.y + 225) == 1)
			{
				texture_blit(*(tile[i].img), dst, pos);
				tile[i].vis = true;
			}
			if (tile[i].alert == true)
			{
			
				printf("this spot right here\n");
			
			}	
		}
		else if (mmap_is_inside(pos.x - 116, pos.y - 115) == 1)
		{
			texture_blit(*(tile[i].img), dst, pos);
			tile[i].vis = true;
		}
	}
}

void	mmap_draw_player(t_game *game, t_vec2 m_pos, bool draw_full)
{
	t_vec2	pos;
	if (game->mmap.mm_big == true)
	{
		pos.x = (SCR_WIDTH / 2 - 7); 
		pos.y = (SCR_HEIGHT / 2 - 7);
		texture_blit(game->mmap.img_pp, game->rt0, pos);
		pos.x = (SCR_WIDTH / 2 - 4) + (game->player.dir.x * 9); 
		pos.y = (SCR_HEIGHT / 2 - 4) + (game->player.dir.y * 9);
		texture_blit(game->mmap.img_pr, game->rt0, pos);
	}
	else
	{
		pos.x = (m_pos.x + 125) + (game->player.dir.x * 9); 
		pos.y = (m_pos.y + 125) + (game->player.dir.y * 9);
		texture_blit(game->mmap.img_pr, game->rt0, pos);
	}
}

void	mmap_case_light(t_game *game, t_vec2 pos)
{
	if (game->mmap.alert_m == true || game->mmap.alert_h == true)
	{
		if (game->fpsc % 30 > 15)// && (game->mmap.alert_m == true || game->mmap.alert_h == true))
		{
			if (game->mmap.alert_m == true) 
				texture_blit(game->mmap.img_case[2], game->rt0, pos);
			if (game->mmap.alert_h == true) 
				texture_blit(game->mmap.img_case[3], game->rt0, pos);
		}
		else
		{
			if (game->mmap.alert_h == true)
				texture_blit(game->mmap.img_case[2], game->rt0, pos);
			else
				texture_blit(game->mmap.img_case[1], game->rt0, pos);
		}
	}
	else
		texture_blit(game->mmap.img_case[1], game->rt0, pos);
}

void	mmap_draw(t_game *game)
{
	t_vec2 pos;//can maybe store this in mmap struct

	pos.x = MAP_POS_X;
	pos.y = MAP_POS_Y;
	if (game->mmap.mm_small == true)
	{
		mmap_case_light(game, pos);
		mmap_draw_player(game, pos, false);
		mmap_draw_walls(game->rt0, game->mmap.tiles, game->player.pos, game->mmap);
		texture_blit(game->mmap.img_case[0], game->rt0, pos);
	}
	else if (game->mmap.mm_big == true)
	{
		mmap_draw_player(game, pos, true);
		mmap_draw_walls(game->rt0, game->mmap.tiles, game->player.pos, game->mmap);
	}
}
//in update ^^^
#include <stdio.h>
#include <unistd.h>
//////////////mmap_setup VVVVVVVVVVVVVVVVVV

void	mmap_init_img(t_game *game)
{
	game->mmap.img_pr = texture_load(game->app.mlx, "assets/minimap/mm_player_r.xpm");
	game->mmap.img_pp = texture_load(game->app.mlx, "assets/minimap/mm_player_p.xpm");
	game->mmap.img_case[0] = texture_load(game->app.mlx, "assets/minimap/mmcase.xpm");
	game->mmap.img_case[1] = texture_load(game->app.mlx, "assets/minimap/mm_back_b.xpm");
	game->mmap.img_case[2] = texture_load(game->app.mlx, "assets/minimap/mm_back_y.xpm");
	game->mmap.img_case[3] = texture_load(game->app.mlx, "assets/minimap/mm_back_r.xpm");
	game->mmap.mm_img[0] = texture_load(game->app.mlx, "assets/minimap/mm00.xpm");
	game->mmap.mm_img[1] = texture_load(game->app.mlx, "assets/minimap/mm01.xpm");
	game->mmap.mm_img[2] = texture_load(game->app.mlx, "assets/minimap/mm02.xpm");
	game->mmap.mm_img[3] = texture_load(game->app.mlx, "assets/minimap/mm03.xpm");
	game->mmap.mm_img[4] = texture_load(game->app.mlx, "assets/minimap/mm04.xpm");
	game->mmap.mm_img[5] = texture_load(game->app.mlx, "assets/minimap/mm05.xpm");
	game->mmap.mm_img[6] = texture_load(game->app.mlx, "assets/minimap/mm06.xpm");
	game->mmap.mm_img[7] = texture_load(game->app.mlx, "assets/minimap/mm07.xpm");
	game->mmap.mm_img[8] = texture_load(game->app.mlx, "assets/minimap/mm08.xpm");
	game->mmap.mm_img[9] = texture_load(game->app.mlx, "assets/minimap/mm09.xpm");
	game->mmap.mm_img[10] = texture_load(game->app.mlx, "assets/minimap/mm10.xpm");
	game->mmap.mm_img[11] = texture_load(game->app.mlx, "assets/minimap/mm11.xpm");
	game->mmap.mm_img[12] = texture_load(game->app.mlx, "assets/minimap/mm12.xpm");
	game->mmap.mm_img[13] = texture_load(game->app.mlx, "assets/minimap/mm13.xpm");
	game->mmap.mm_img[14] = texture_load(game->app.mlx, "assets/minimap/mm14.xpm");
	game->mmap.mm_img[15] = texture_load(game->app.mlx, "assets/minimap/mm15.xpm");
	game->mmap.mm_img[16] = texture_load(game->app.mlx, "assets/minimap/mm16.xpm");
	game->mmap.mm_img[17] = texture_load(game->app.mlx, "assets/minimap/mm17.xpm");
	game->mmap.mm_img[18] = texture_load(game->app.mlx, "assets/minimap/mm18.xpm");
	game->mmap.mm_img[19] = texture_load(game->app.mlx, "assets/minimap/mm19.xpm");
}

int	mmap_img_number_2(bool t, bool l, bool r, bool b)
{
	if (t == false && l == false && r == false && b == true)
		return(15);
	if (t == false && l == false && r == true && b == false)
		return(16);
	if (t == true && l == false && r == false && b == false)
		return(17);
	if (t == false && l == true && r == false && b == false)
		return(18);
	if (t == false && l == false && r == false && b == false)
		return(19);
	return (2);
}

int	mmap_img_number_1(bool t, bool l, bool r, bool b)
{
	if (t == true && l == false && r == false && b == true)
		return(0);
	if (t == false && l == true && r == true && b == false)
		return(1);
	if (t == true && l == true && r == true && b == true)
		return(2);
	if (t == true && l == false && r == true && b == true)
		return(3);
	if (t == true && l == true && r == true && b == false)
		return(4);
	if (t == true && l == true && r == false && b == true)
		return(5);
	if (t == false && l == true && r == true && b == true)
		return(6);
	if (t == false && l == false && r == true && b == true)
		return(7);
	if (t == true && l == false && r == true && b == false)
		return(8);
	if (t == true && l == true && r == false && b == false)
		return(9);
	if (t == false && l == true && r == false && b == true)
		return(10);
	return(mmap_img_number_2(t, l, r, b));
}

int	mmap_decide_img(t_tile *tile, int w, int h, int pos)
{
	bool	t;
	bool	l;
	bool	r;
	bool	b;
	
	t = false;
	l = false;
	r = false;
	b = false;
	if (pos - w >= 0 && (tile[pos-w].type == WALL || tile[pos-w].type == DOOR))
		t = true;
	if (pos - 1 >= 0 && (tile[pos-1].type == WALL || tile[pos-1].type == DOOR) && pos % w != 0)
		l = true;
	if (pos + 1 < (w * h) && (tile[pos + 1].type == WALL || tile[pos + 1].type == DOOR) && (pos + 1) % w != 0)
		r = true;
	if (pos + w < (w * h) && (tile[pos + w].type == WALL || tile[pos + w].type == DOOR))
		b = true;
	return (mmap_img_number_1(t,l,r,b));
}

t_texture	*mmap_get_img(t_game *game, int pos)
{
	int	index;

	index = mmap_decide_img(game->world->map.tiles, game->world->map.width, game->world->map.height, pos);
	return (&game->mmap.mm_img[index]);
}

t_texture	*mmap_get_door_img(t_game *game, int pos, int i)
{
	if (game->world->map.tiles[pos+1].type == FLOOR)
	{
		game->mmap.tiles[i].vertical = true;
		return (&game->mmap.mm_img[13]);
	}
	else
	{
		game->mmap.tiles[i].vertical = false;
		return (&game->mmap.mm_img[11]);
	}
}

int	mmap_tile_assign(t_game *game, int i, int y)
{
	int	x;
	int	index;

	x = -1;
	while (++x < game->world->map.width)
	{
		index = x + y * game->world->map.width;
		if (game->world->map.tiles[index].type == WALL)
		{
			if (game->mmap.tiles[i].img == NULL)
				game->mmap.tiles[i].img = mmap_get_img(game, index);
			game->mmap.tiles[i].pos.x = x * MAP_S + MAP_POS_X + MAP_CASE;
			game->mmap.tiles[i].pos.y = y * MAP_S + MAP_POS_Y + MAP_CASE;
			game->mmap.tiles[i].ref = index;
			game->mmap.tiles[i].alert = false;
			game->mmap.tiles[i++].vis = false;//change map vis here need to make a modifier tho
		}
		if (game->world->map.tiles[index].type == DOOR)
		{
			game->mmap.tiles[i].img = mmap_get_door_img(game, index, i);
			game->mmap.tiles[i].pos.x = x * MAP_S + MAP_POS_X + MAP_CASE;
			game->mmap.tiles[i].pos.y = y * MAP_S + MAP_POS_Y + MAP_CASE;
			game->mmap.tiles[i].ref = index;
			game->mmap.tiles[i].alert = false;
			game->mmap.tiles[i++].vis = false;//change map vis here need to make a modifier tho
		}
	}
	return (i);
}


bool	mmap_fog_check(t_game *game)
{
	int	i;

	i = -1;
	while (game->world->map.mods[i].type != MINI_MAP)
		i++;
	if (game->world->map.mods[i].content == NULL)
		return (false);
	if (game->world->map.mods[i].content[0] == 'F')
		return (false);
	return (true);
}

void	mmap_init(t_game *game)
{
	int	x;
	int	y;
	int	index;
	int	i;

	game->mmap.mm_big = false;
	game->mmap.mm_small = true;
	game->mmap.alert_m = false;
	game->mmap.alert_h = false;
	mmap_init_img(game);
	y = -1;
	i = 0;
	while (++y < game->world->map.height)
		i = mmap_tile_assign(game, i, y);
	while(i > -1)
		game->mmap.tiles[i--].vis = mmap_fog_check(game);
}
