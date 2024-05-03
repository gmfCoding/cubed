/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   title_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:39:01 by kmordaun          #+#    #+#             */
/*   Updated: 2024/05/04 02:17:17 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "state.h"
#include "destroy.h"

void	title_show_select_start_input(t_game *game)
{
	if (input_keydown(&game->input, KEY_ENTER))
	{
		play_sound(game->app.sfx, SFX_SELECT, PLAY);
		if (game->title.anim_frame == 0)
			game->title.state = LOAD_MAP;
		if (game->title.anim_frame == 1)
			game->title.state = OPTIONS;
		if (game->title.anim_frame == 2)
			game_destroy(game);
	}
}

void	title_show_select_start(t_game *game)
{
	game->title.anim_forward = 0;
	texture_blit(game->textures[TEX_TITLE_SPACE_BACK], game->rt0, v2new(0, 0));
	if (input_keydown(&game->input, KEY_UARROW) \
		|| input_keydown(&game->input, KEY_W))
	{
		play_sound(game->app.sfx, SFX_SELECTION, PLAY);
		game->title.anim_frame--;
	}
	if (input_keydown(&game->input, KEY_DARROW) \
		|| input_keydown(&game->input, KEY_S))
	{
		play_sound(game->app.sfx, SFX_SELECTION, PLAY);
		game->title.anim_frame++;
	}
	game->title.anim_frame = (game->title.anim_frame + 3) % 3;
	texture_blit(game->textures[TEX_TITLE_START_0 + \
		(game->title.anim_frame == 0)], game->rt0, v2new(295, 105));
	texture_blit(game->textures[TEX_TITLE_OPTIONS_0 + \
		(game->title.anim_frame == 1)], game->rt0, v2new(295, 305));
	texture_blit(game->textures[TEX_TITLE_QUIT_0 + \
		(game->title.anim_frame == 2)], game->rt0, v2new(295, 505));
	title_show_select_start_input(game);
}

void	title_show_title(t_game *game)
{
	texture_blit(game->textures[TEX_TITLE_BACKDROP], game->rt0, v2new(0, 0));
	title_animations(game);
	if (input_keyheld(&game->input, KEY_ENTER) \
		|| input_keyheld(&game->input, KEY_SPACE) \
		|| input_keyheld(&game->input, KEY_ENTER) \
		|| input_keydown(&game->input, MB_LEFT))
	{
		play_sound(game->app.sfx, SFX_SELECTION, PLAY);
		game->title.anim_frame = 0;
		game->title.state = SELECT_START;
	}
}

void	game_title_states(t_game *game)
{
	if (game->title.state == TITLE)
		title_show_title(game);
	else if (game->title.state == SELECT_START)
		title_show_select_start(game);
	else if (game->title.state == LOAD_MAP)
		title_show_load_map(game);
	else if (game->title.state == OPTIONS)
		title_show_options(game);
	else if (game->title.state == LOAD_AND_RUN)
		title_load_and_run(game);
	else if (game->title.state == LOSE_SCREEN)
		title_lose_screen(game, game->textures, &game->title);
	else if (game->title.state == WIN_SCREEN)
		title_win_screen(game, game->textures, &game->title);
	else if (game->title.state == BACK_TO_TITLE)
		title_back_to_title(game);
}

void	game_screen_states(t_game *game)
{
	if (game->title.state == RUNNING_GAME)
	{
		while (game->loaded_index[0] < TEX_ARRAY_SIZE)
			load_image_at_index(game);
		game_update(game);
		game->menu_reloaded = false;
	}
	else
	{
		game->menu_reloaded = true;
		control_core_process(game);
		game_title_states(game);
		texture_draw(game->app, game->rt0, v2new(0, 0));
		if (game->title.state == LOAD_MAP)
			title_display_maps(game);
		if (game->loaded_index[0] < TEX_ARRAY_SIZE)
			load_image_at_index(game);
	}
}
