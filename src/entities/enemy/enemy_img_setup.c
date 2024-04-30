/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_img_setup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:55:13 by kmordaun          #+#    #+#             */
/*   Updated: 2024/04/30 16:55:15 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enemy.h"
#include "map.h"
#include "state.h"

void	enemy_load_textures(t_game *game, char *base_path, \
	char *file_type, int index)
{
	char	path[100];
	char	index_str[5];
	int		i;

	i = 0;
	while (++i <= 18)
	{
		index_str[0] = '0';
		index_str[1] = '0';
		if (i * 3 - 2 < 10)
		{
			index_str[2] = '0';
			index_str[3] = '0' + (i * 3) - 2;
		}
		else
		{
			index_str[2] = '0' + (i * 3 - 2) / 10;
			index_str[3] = '0' + (i * 3 - 2) % 10;
		}
		index_str[4] = '\0';
		ft_strcpy(path, base_path);
		ft_strcat(path, index_str);
		ft_strcat(path, file_type);
		game->textures[((index - 1) * 18) + i + TEX_ENEMY_START - 1] = texture_load(game->app.mlx, path);
	}
}

void	enemy_load_directory(t_game *game, char *base_path)
{
	char	path[100];
	char	index_str[5];
	int		i;

	i = 0;
	while (++i <= 32)
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
		enemy_load_textures(game, path, ".xpm", i);
	}
}
