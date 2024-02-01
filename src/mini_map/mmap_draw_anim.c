#include "mini_map.h"
#include "texture.h"
#include "state.h"

void	mmap_draw_case_anim(t_game *game, t_vec2 pos)
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

void	mmap_draw_alert_anim(t_game *game, t_texture *img, t_vec2 pos, int i)
{
	if (game->fpsc % 30 > 15)
	{
		if (game->mmap.alert_m == true) 
			texture_blit(img[i+2], game->rt0, pos);
		if (game->mmap.alert_h == true) 
			texture_blit(img[i+4], game->rt0, pos);
	}
	else
	{
		if (game->mmap.alert_h == true)
			texture_blit(img[i+2], game->rt0, pos);
		else
			texture_blit(img[i], game->rt0, pos);
	}
}

