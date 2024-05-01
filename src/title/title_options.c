/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   title_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:20:56 by kmordaun          #+#    #+#             */
/*   Updated: 2024/04/18 17:22:00 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "state.h"
#include "destroy.h"

//if(input_keydown(&game->input, KEY_UARROW))
//		game->title.state = SELECT_QUIT;
void	title_show_options(t_game *game)
{
	texture_blit(game->textures[TEX_TITLE_SPACE_BACK], game->rt0, v2new(0, 0));
	texture_blit(game->textures[TEX_TITLE_OPTIONS_0], \
		game->rt0, v2new(270, 105));
	if (input_keydown(&game->input, KEY_BACKSPACE))
	{
		play_sound(game->app.sfx, SFX_SELECT, PLAY);
		game->title.state = SELECT_START;
	}
}
