/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_loader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:57:15 by kmordaun          #+#    #+#             */
/*   Updated: 2024/04/18 18:39:02 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "state.h"

void	load_enemy_tex(t_game *game, char *b_path, char *file_type)
{
	char	path[100];
	char	index_str[5];

	if (++game->loaded_index[2] <= 18)
	{
		index_str[0] = '0';
		index_str[1] = '0';
		if (game->loaded_index[2] * 3 - 2 < 10)
		{
			index_str[2] = '0';
			index_str[3] = '0' + (game->loaded_index[2] * 3) - 2;
		}
		else
		{
			index_str[2] = '0' + (game->loaded_index[2] * 3 - 2) / 10;
			index_str[3] = '0' + (game->loaded_index[2] * 3 - 2) % 10;
		}
		index_str[4] = '\0';
		ft_strcpy(path, b_path);
		ft_strcat(path, index_str);
		ft_strcat(path, file_type);
		mlx_string_put(game->app.mlx, game->app.win, 400, 900, 0xffffff, path);
		game->textures[game->loaded_index[0]] = texture_load(game->app.mlx, path);
	}
}

void	load_enemy_directory(t_game *game, char *base_path)
{
	char	path[100];
	char	index_str[5];
	int		i;

	i = game->loaded_index[1];
	if (i <= 32)
	{
		if (i < 10)
		{
			index_str[0] = '0' + i;
			index_str[1] = '/';
			index_str[2] = '\0';
		}
		else
		{
			index_str[0] = '0' + i / 10;
			index_str[1] = '0' + i % 10;
			index_str[2] = '/';
			index_str[3] = '\0';
		}
		ft_strcpy(path, base_path);
		ft_strcat(path, index_str);
		load_enemy_tex(game, path, ".xpm");
	}
}

void	load_enemy_images_at_index(t_game *game)
{
	load_enemy_directory(game, "assets/enemy_sprites/");
	if (game->loaded_index[2] >= 18)
	{
		game->loaded_index[1]++;
		game->loaded_index[2] = 0;
	}
}

static const char	*g_image_paths[] = {
[TEX_WINDOW] = "assets/window.xpm",
[TEX_DOOR] = "assets/window.xpm",
[TEX_FLOOR] = "assets/metal_walkway_acg.xpm",
[TEX_CEILING] = "assets/metal_walkway_acg.xpm",
[TEX_TITLE_MISSION_COMPLETED] = "assets/menu/mission_competed.xpm",
[TEX_TITLE_MISSION_FAILED] = "assets/menu/mission_failed.xpm",
[TEX_TITLE_NEXT_LEVEL_0] = "assets/menu/next_level_0.xpm",
[TEX_TITLE_NEXT_LEVEL_1] = "assets/menu/next_level_1.xpm",
[TEX_TITLE_RETRY_0] = "assets/menu/retry_0.xpm",
[TEX_TITLE_RETRY_1] = "assets/menu/retry_1.xpm",
[TEX_TITLE_CREATED_CHRIS_KYLE] = "assets/menu/created_chris_kyle.xpm",
[TEX_TITLE_MAIN_MENU_0] = "assets/menu/main_menu_0.xpm",
[TEX_TITLE_MAIN_MENU_1] = "assets/menu/main_menu_1.xpm",
[TEX_FIVE_LIGHTS] = "assets/five_lights_wall.xpm",
[TEX_UI_CONTROLS] = "assets/ui/controls.xpm",
[TEX_UI_INTERACT_BRIGHT] = "assets/ui/interact_bright.xpm",
[TEX_UI_INTERACT_DUL] = "assets/ui/interact_dal.xpm",
[TEX_UI_DOOR_LOCKED] = "assets/ui/promt_door_locked.xpm",
[TEX_UI_TASK_INACTIVE] = "assets/ui/inactive_task.xpm",
};

void	load_image_at_index(t_game *game)
{
	if (game->loaded_index[0] < TEX_ENEMY_START)
	{
		if (g_image_paths[game->loaded_index[0]] != NULL)
		{
			mlx_string_put(game->app.mlx, game->app.win, 400, 900, 0xffffff, \
				g_image_paths[game->loaded_index[0]]);
			game->textures[game->loaded_index[0]] = texture_load(game->app.mlx, \
				g_image_paths[game->loaded_index[0]]);
		}
	}
	if (game->loaded_index[0] >= TEX_ENEMY_START && game->loaded_index[0] <= TEX_ENEMY_END)
		load_enemy_images_at_index(game);
	game->loaded_index[0]++;
}
