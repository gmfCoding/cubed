/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmap_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:08:26 by kmordaun          #+#    #+#             */
/*   Updated: 2024/04/18 18:08:46 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_map.h"
#include "texture.h"
#include "state.h"

/*
 * this fucntionis called from input toggling
 * between the small mini map to the large minimap
 */
void	mmap_input(t_game *game, t_mmap *mmap)
{
	if (input_keydown(&game->input, KEY_M))
	{
		game->mmap.has_pressed = true;
		if (mmap->mm_small == true)
		{
			play_sound(game->app.sfx, SFX_SELECT, PLAY);
			mmap->mm_big = true;
			mmap->mm_small = false;
		}
		else
		{
			play_sound(game->app.sfx, SFX_SELECTION, PLAY);
			mmap->mm_big = false;
			mmap->mm_small = true;
		}
	}
}
