/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   title_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:22:15 by kmordaun          #+#    #+#             */
/*   Updated: 2024/04/18 17:55:31 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "state.h"
#include "destroy.h"
#include <dirent.h>

void	title_imgs_load(void *x, t_texture *t)
{
	t[TEX_TITLE_BACKDROP] = texture_load(x, "assets/menu/backdrop.xpm");
	t[TEX_TITLE_ENTER_00] = texture_load(x, "assets/menu/enter_00.xpm");
	t[TEX_TITLE_ENTER_01] = texture_load(x, "assets/menu/enter_01.xpm");
	t[TEX_TITLE_ENTER_02] = texture_load(x, "assets/menu/enter_02.xpm");
	t[TEX_TITLE_ENTER_03] = texture_load(x, "assets/menu/enter_03.xpm");
	t[TEX_TITLE_ENTER_04] = texture_load(x, "assets/menu/enter_04.xpm");
	t[TEX_TITLE_ENTER_05] = texture_load(x, "assets/menu/enter_05.xpm");
	t[TEX_TITLE_ENTER_06] = texture_load(x, "assets/menu/enter_06.xpm");
	t[TEX_TITLE_LOADMAP] = texture_load(x, "assets/menu/loadmap.xpm");
	t[TEX_TITLE_OPTIONS_0] = texture_load(x, "assets/menu/options_0.xpm");
	t[TEX_TITLE_OPTIONS_1] = texture_load(x, "assets/menu/options_1.xpm");
	t[TEX_TITLE_QUIT_0] = texture_load(x, "assets/menu/quit_0.xpm");
	t[TEX_TITLE_QUIT_1] = texture_load(x, "assets/menu/quit_1.xpm");
	t[TEX_TITLE_SPACE_BACK] = texture_load(x, "assets/menu/space_back.xpm");
	t[TEX_TITLE_START_0] = texture_load(x, "assets/menu/start_0.xpm");
	t[TEX_TITLE_START_1] = texture_load(x, "assets/menu/start_1.xpm");
}
/*
//using forbidden functions here
int	load_map_str(t_game *game)
{
	int				i;
	DIR				*dir;
	struct dirent	*ent;

	i = 0;
	dir = opendir(MAP_PATH);
	if (dir == NULL)
		return (printf("Error\n failed to opening map directory\n"), 1);
	ent = readdir(dir);
	while (ent != NULL && i++ < 20)
	{
		if (!(ft_strcmp(ent->d_name, ".") && ft_strcmp(ent->d_name, "..") \
			&& ft_strcmp(ent->d_name, "bad_maps")))
		{
			ent = readdir(dir);
			continue ;
		}
		ft_strcpy(game->title.map_str[game->title.map_str_amount++], \
			ent->d_name);
		ent = readdir(dir);
	}
	return (closedir(dir));
}
*/

int	load_map_str(t_game *game)
{
	ft_strcpy(game->title.map_str[game->title.map_str_amount++], \
			MAP_STR1);
	ft_strcpy(game->title.map_str[game->title.map_str_amount++], \
			MAP_STR2);
	ft_strcpy(game->title.map_str[game->title.map_str_amount++], \
			MAP_STR3);
	ft_strcpy(game->title.map_str[game->title.map_str_amount++], \
			MAP_STR4);
	ft_strcpy(game->title.map_str[game->title.map_str_amount++], \
			MAP_STR5);
	ft_strcpy(game->title.map_str[game->title.map_str_amount++], \
			MAP_STR6);
	return (0);
}

void	title_setup_screens(t_game *game)
{
	title_imgs_load(game->app.mlx, game->textures);
	game->title.anim_frame = 0;
	game->title.anim_forward = 0;
	game->title.map_str_amount = 0;
	load_map_str(game);
}
