/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 21:24:09 by clovell           #+#    #+#             */
/*   Updated: 2023/05/02 08:20:01 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <mlx.h>
#include "vector2.h"
#include "texture.h"
#include "state.h"

void    texture_draw(t_game *gs, t_texture tex, t_vec2 pos)
{
	mlx_put_image_to_window(gs->mlx, gs->win, tex.img, pos.x, pos.y);
}

// Copies pixel data from one texture to another
void    texture_blit(t_texture src, t_texture dst, t_vec2 pos)
{
	int x;
	int y;

	y = -1;
	while (++y < src.height)
	{
		x = -1;
		while (++x < src.width)
		{
			int color = pixel_get(src, x, y);
			if (color >> 24 && 0xFF > 0)
				pixel_set_s(dst, pos.x + x, pos.y + y, color);
		}
	}
}

#include <string.h>
// Copies pixel data from one texture to another
void    texture_clear(t_texture src)
{
	// FORBIDDEN
	memset(src.data, 0, (src.bpp / 8) * src.width * src.height);
}

t_texture texture_get_debug_view(t_game *game, int view)
{
	if (game->views[view].rt.img == NULL)
	{
		game->views[view].win = mlx_new_window(game->mlx, game->rt0.width, game->rt0.height, "DEBUG VIEW");
		game->views[view].rt = texture_create(game->mlx, game->rt0.width, game->rt0.height);
	} 
	return game->views[view].rt;
}

void texture_draw_debug_view(t_game *game, int view)
{
	t_texture rt;

	if (view >= MAX_DEBUG_VIEWS)
		return ;
	mlx_put_image_to_window(game->mlx, game->views[view].win, game->views[view].rt.img, 0, 0);
}

void texture_debug_view_blit(t_game *game, int view, t_texture tex, t_vec2 pos)
{
	t_texture rt;

	if (view >= MAX_DEBUG_VIEWS)
		return ;
	rt = texture_get_debug_view(game, view);
	texture_blit(tex, rt, pos);
	mlx_put_image_to_window(game->mlx, game->views[view].win, game->views[view].rt.img, 0, 0);
}
