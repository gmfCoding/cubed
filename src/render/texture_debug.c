/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_debug.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 21:24:09 by clovell           #+#    #+#             */
/*   Updated: 2024/05/06 22:46:33 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "state.h"
#include "texture.h"

t_texture	texture_get_debug_view(t_game *game, int view)
{
	if (game->views[view].rt.img == NULL)
	{
		game->views[view].win = mlx_new_window(game->app.mlx, game->rt0.width, \
												game->rt0.height, "DEBUG VIEW");
		game->views[view].rt = texture_create(game->app.mlx, game->rt0.width, \
															game->rt0.height);
		game->view_count++;
	}
	return (game->views[view].rt);
}

void	texture_draw_debug_view(t_game *game, int view)
{
	t_debug_texture	*debug;

	if (view >= MAX_DEBUG_VIEWS)
		return ;
	debug = &game->views[view];
	if (debug->win == NULL || debug->rt.img == NULL)
		return ;
	mlx_put_image_to_window(game->app.mlx, debug->win, debug->rt.img, 0, 0);
}

void	texture_debug_view_blit(t_game *game, int view, t_texture tex, \
																	t_vec2 pos)
{
	t_texture	rt;

	if (view >= MAX_DEBUG_VIEWS)
		return ;
	rt = texture_get_debug_view(game, view);
	texture_blit(tex, rt, pos);
	mlx_put_image_to_window(game->app.mlx, game->views[view].win, \
												game->views[view].rt.img, 0, 0);
}
