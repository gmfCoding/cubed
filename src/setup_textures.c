/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 22:01:57 by clovell           #+#    #+#             */
/*   Updated: 2024/05/06 22:04:07 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "state.h"

void	nsew_textures(t_game *game)
{
	t_mod *const	n = mod_get_mod(&game->world->map, MT_NORTH_TEXTURE, NULL);
	t_mod *const	s = mod_get_mod(&game->world->map, MT_SOUTH_TEXTURE, NULL);
	t_mod *const	e = mod_get_mod(&game->world->map, MT_EAST_TEXTURE, NULL);
	t_mod *const	w = mod_get_mod(&game->world->map, MT_WEST_TEXTURE, NULL);
	const char		*wall = "assets/wall.xpm";

	if (n)
		game->textures[TEX_WALLN] = texture_load(game->app.mlx, n->content);
	else
		game->textures[TEX_WALLN] = texture_load(game->app.mlx, wall);
	if (s)
		game->textures[TEX_WALLS] = texture_load(game->app.mlx, s->content);
	else
		game->textures[TEX_WALLS] = texture_load(game->app.mlx, wall);
	if (e)
		game->textures[TEX_WALLE] = texture_load(game->app.mlx, e->content);
	else
		game->textures[TEX_WALLE] = texture_load(game->app.mlx, wall);
	if (w)
		game->textures[TEX_WALLW] = texture_load(game->app.mlx, w->content);
	else
		game->textures[TEX_WALLW] = texture_load(game->app.mlx, wall);
}

//	game->textures[TEX_SKYBOX] = texture_load(game->app.mlx, \
//													"assets/new_skybox.xpm");
//	game->textures[TEX_SKYBOX] = texture_create(game->app.mlx, 1000, 5000);
void	generate_textures(t_game *game)
{
	game->textures[TEX_SKYBOX] = texture_load(game->app.mlx, \
													"assets/sptiled960.xpm");
	game->textures[TEX_WALL] = texture_load(game->app.mlx, "assets/wall.xpm");
}
