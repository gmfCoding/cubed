/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   title_animation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:14:41 by kmordaun          #+#    #+#             */
/*   Updated: 2024/04/18 17:17:10 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "state.h"
#include "destroy.h"

void	title_animations_display(t_game *game)
{
	texture_blit(game->textures[TEX_TITLE_ENTER_06], \
		game->rt0, v2new(295, 705));
	texture_blit(game->textures[game->title.anim_frame], \
		game->rt0, v2new(300, 700));
}

void	title_animations(t_game *game)
{
	if (game->fpsc % 35 == 0)
	{
		game->fpsc = 0;
		if (game->title.anim_forward)
		{
			game->title.anim_frame++;
			if (game->title.anim_frame > TEX_TITLE_ENTER_06)
			{
				game->title.anim_frame = TEX_TITLE_ENTER_06 - 1;
				game->title.anim_forward = 0;
			}
		}
		else
		{
			game->title.anim_frame--;
			if (game->title.anim_frame < TEX_TITLE_ENTER_00)
			{
				game->title.anim_frame = TEX_TITLE_ENTER_00 + 1;
				game->title.anim_forward = 1;
			}
		}
	}
	title_animations_display(game);
}
