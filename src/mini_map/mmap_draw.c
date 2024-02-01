
#include "mini_map.h"
#include "texture.h"
#include "state.h"


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
	t_vec2	pos;

	i = -1;
	while (tile[++i].img != NULL)
	{
		pos = v2sub(tile[i].pos, v2muls(p_pos, MAP_S));
		if (mmap.mm_big == true)
		{
			pos.x = ((tile[i].pos.x - MAP_POS_X - MAP_CASE) + (SCR_WIDTH / 2)) - p_pos.x * MAP_S;
			pos.y = ((tile[i].pos.y - MAP_POS_Y - MAP_CASE) + (SCR_HEIGHT / 2)) - p_pos.y * MAP_S;
			if (tile[i].vis == true || mmap_is_inside(pos.x - 455, pos.y + 225) == 1)
			{
				texture_blit(*(tile[i].img), dst, pos);
				tile[i].vis = true;
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

void	mmap_draw_alert(t_game *game, t_vec2 p_pos, t_mmap *mmap)
{
	t_vec2 pos;
	int i;

	i = 20;
	if (mmap->alert_m == true || mmap->alert_h == true)
	{
		pos.x = ((mmap->al_pos.x * MAP_S)  - (p_pos.x * MAP_S) + (SCR_WIDTH / 2));
		pos.y = ((mmap->al_pos.y * MAP_S) - (p_pos.y * MAP_S) + (SCR_HEIGHT / 2) - 21);
		if (pos.x < 1 || pos.x > SCR_WIDTH - 24 || pos.y <  1 || pos.y > SCR_HEIGHT - 24)
		{
			if (pos.x < 1)
				pos.x = 1;
			if (pos.x > SCR_WIDTH - 24)
				pos.x = SCR_WIDTH - 24;
			if (pos.y < 1)
				pos.y = 1;
			if (pos.y > SCR_HEIGHT - 24)
				pos.y = SCR_HEIGHT - 24;
			i++;
		}
		mmap_draw_alert_anim(game, mmap->mm_img, pos, i);
	}
}

void	mmap_draw(t_game *game)
{
	t_vec2 pos;//can maybe store this in mmap struct

	pos.x = MAP_POS_X;
	pos.y = MAP_POS_Y;
	if (game->mmap.mm_small == true)
	{
		mmap_draw_case_anim(game, pos);
		mmap_draw_player(game, pos, false);
		mmap_draw_walls(game->rt0, game->mmap.tiles, game->player.pos, game->mmap);
		texture_blit(game->mmap.img_case[0], game->rt0, pos);
	}
	else if (game->mmap.mm_big == true)
	{
		mmap_draw_player(game, pos, true);
		mmap_draw_walls(game->rt0, game->mmap.tiles, game->player.pos, game->mmap);
		mmap_draw_alert(game, game->player.pos, &game->mmap);
	}
}
