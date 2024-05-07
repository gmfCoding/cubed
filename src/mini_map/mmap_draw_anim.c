/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmap_draw_anim.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:20:17 by kmordaun          #+#    #+#             */
/*   Updated: 2024/04/18 18:21:55 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_map.h"
#include "texture.h"
#include "state.h"

/*
 * toggles background color for minimap case
 */
void	mmap_draw_case_anim(t_game *game, t_vec2 pos)
{
	if ((game->mmap.alert_m == true || game->mmap.alert_h == true) \
		&& game->mmap.has_pressed == false)
	{
		if (game->fpsc % 30 > 15)
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

/*
 * draws small alert icon
 * draws either on of the other image based apon the games fps counter
 * can adjust the speed by toggling numbers the number on the right
 * should be half of the left number to make images display at even times
 * there will be a jump on first image coz the fps counter
 * is constanly moving could add a condtion to change this
 */
void	mmap_draw_alert_anim(t_game *game, t_texture *img, t_vec2 pos, int i)
{
	if (game->fpsc % 30 > 15)
	{
		if (game->mmap.alert_m == true)
			texture_blit(img[i + 2], game->rt0, pos);
		if (game->mmap.alert_h == true)
			texture_blit(img[i + 4], game->rt0, pos);
	}
	else
	{
		if (game->mmap.alert_h == true)
			texture_blit(img[i + 2], game->rt0, pos);
		else
			texture_blit(img[i], game->rt0, pos);
	}
}
