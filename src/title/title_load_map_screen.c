/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   title_load_map_screen.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:17:29 by kmordaun          #+#    #+#             */
/*   Updated: 2024/04/18 17:20:31 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "state.h"
#include "destroy.h"

void	title_back_to_title(t_game *game)
{
	int	i;

	i = -1;

	stop_all_sound(game->app.sfx);
	while (game->mmap.tiles[++i].img != NULL)
		game->mmap.tiles[i].img = NULL;
	world_destroy(game);
	game->world = malloc(sizeof(t_world));
	*game->world = (t_world){0};
	game->title.anim_frame = 10;
	game->title.state = TITLE;
	play_sound(game->app.sfx, SFX_INTRO, PLAY);
}

void	title_load_and_run(t_game *game)
{
	char	path[50];
	char	*argv[2];

	ft_strcpy(path, "maps/");
	ft_strcat(path, game->title.map_str[game->title.anim_forward]);
	argv[0] = "";
	argv[1] = path;
	printf("file load%s\n", argv[1]);
	game->title.anim_frame = 10;
	setup_world(2, argv, game);
	game->title.state = RUNNING_GAME;
}

void	title_display_maps(t_game *game)
{
	int	y;
	int	i;

	y = 200;
	i = -1;
	while (++i < game->title.map_str_amount)
	{
		mlx_string_put(game->app.mlx, game->app.win, 400, y += 30, 0x333333, \
			game->title.map_str[i]);
		if (i == game->title.anim_forward)
			mlx_string_put(game->app.mlx, game->app.win, 400, y, 0xffffff, \
				game->title.map_str[i]);
	}
}

void	title_show_load_map(t_game *game)
{
	texture_blit(game->textures[TEX_TITLE_SPACE_BACK], game->rt0, v2new(0, 0));
	texture_blit(game->textures[TEX_TITLE_LOADMAP], game->rt0, v2new(270, 105));
	if (input_keydown(&game->input, KEY_BACKSPACE))
	{
		play_sound(game->app.sfx, SFX_SELECT, PLAY);
		game->title.state = SELECT_START;
	}
	if (input_keydown(&game->input, KEY_UARROW) \
		|| input_keydown(&game->input, KEY_W))
	{
		play_sound(game->app.sfx, SFX_SELECTION, PLAY);
		game->title.anim_forward--;
	}
	if (input_keydown(&game->input, KEY_DARROW) \
		|| input_keydown(&game->input, KEY_S))
	{
		play_sound(game->app.sfx, SFX_SELECTION, PLAY);
		game->title.anim_forward++;
	}
	if (game->title.anim_forward < 0)
		game->title.anim_forward = game->title.map_str_amount - 1;
	if (game->title.anim_forward > game->title.map_str_amount - 1)
		game->title.anim_forward = 0;
	if (input_keydown(&game->input, KEY_ENTER))
	{
		play_sound(game->app.sfx, SFX_SELECT, PLAY);
		game->title.state = LOAD_AND_RUN;
	}
}
