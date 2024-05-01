/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   title_end_screen.c                                 :+:      :+:    :+:   */
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

void	title_lose_screen_input(t_game *game, t_title *title)
{
	if (input_keydown(&game->input, KEY_ENTER))
	{
		play_sound(game->app.sfx, SFX_SELECT, PLAY);
		if (title->anim_frame == 0)
		{
			title_back_to_title(game);
			title_load_and_run(game);
		}
		if (title->anim_frame == 1)
			title->state = BACK_TO_TITLE;
		if (title->anim_frame == 2)
			game_destroy(game);
	}
}

void	title_lose_screen(t_game *game, t_texture *t, t_title *title)
{
	texture_blit(t[TEX_TITLE_SPACE_BACK], game->rt0, v2new(0, 0));
	texture_blit(t[TEX_TITLE_MISSION_FAILED], game->rt0, v2new(140, 250));
	texture_blit(t[TEX_TITLE_CREATED_CHRIS_KYLE], game->rt0, v2new(200, 900));
	if ((input_keydown(&game->input, KEY_UARROW) \
		|| input_keydown(&game->input, KEY_W)) && title->anim_frame--)
		play_sound(game->app.sfx, SFX_SELECTION, PLAY);
	if ((input_keydown(&game->input, KEY_DARROW) \
		|| input_keydown(&game->input, KEY_S)) && title->anim_frame++)
		play_sound(game->app.sfx, SFX_SELECTION, PLAY);
	title->anim_frame = (title->anim_frame + 3) % 3;
	texture_blit(t[TEX_TITLE_RETRY_0 + (title->anim_frame == 0)], \
		game->rt0, v2new(200, 500));
	texture_blit(t[TEX_TITLE_MAIN_MENU_0 + (title->anim_frame == 1)], \
		game->rt0, v2new(200, 600));
	texture_blit(t[TEX_TITLE_QUIT_0 + (title->anim_frame == 2)], \
		game->rt0, v2new(200, 700));
	title_lose_screen_input(game, title);
}

void	title_win_screen_input(t_game *game, t_title *title)
{
	if (input_keydown(&game->input, KEY_ENTER))
	{
		play_sound(game->app.sfx, SFX_SELECT, PLAY);
		if (title->anim_frame == 0 && title->anim_forward \
			!= title->map_str_amount)
		{
			title->anim_forward++;
			title_back_to_title(game);
			title_load_and_run(game);
		}
		if (title->anim_frame == 1)
			title->state = BACK_TO_TITLE;
		if (title->anim_frame == 2)
			game_destroy(game);
	}
}

void	title_win_screen(t_game *game, t_texture *t, t_title *title)
{
	texture_blit(t[TEX_TITLE_SPACE_BACK], game->rt0, v2new(0, 0));
	texture_blit(t[TEX_TITLE_MISSION_COMPLETED], game->rt0, v2new(40, 250));
	texture_blit(t[TEX_TITLE_CREATED_CHRIS_KYLE], game->rt0, v2new(200, 900));
	if ((input_keydown(&game->input, KEY_UARROW) \
		|| input_keydown(&game->input, KEY_W)) && title->anim_frame--)
		play_sound(game->app.sfx, SFX_SELECTION, PLAY);
	if (input_keydown(&game->input, KEY_DARROW) \
		|| input_keydown(&game->input, KEY_S) && title->anim_frame++)
		play_sound(game->app.sfx, SFX_SELECTION, PLAY);
	title->anim_frame = (title->anim_frame + 3) % 3;
	if (title->anim_forward != title->map_str_amount)
		texture_blit(t[TEX_TITLE_NEXT_LEVEL_0 + (title->anim_frame == 0)], \
		game->rt0, v2new(200, 500));
	texture_blit(t[TEX_TITLE_MAIN_MENU_0 + (title->anim_frame == 1)], \
		game->rt0, v2new(200, 600));
	texture_blit(t[TEX_TITLE_QUIT_0 + (title->anim_frame == 2)], \
		game->rt0, v2new(200, 700));
	title_win_screen_input(game, title);
}
