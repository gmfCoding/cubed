/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 21:24:09 by clovell           #+#    #+#             */
/*   Updated: 2023/12/10 21:36:28 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <mlx.h>
#include "vector2.h"
#include "texture.h"
#include "state.h"

void	texture_draw(t_game *gs, t_texture tex, t_vec2 pos)
{
	mlx_put_image_to_window(gs->app.mlx, gs->app.win, tex.img, pos.x, pos.y);
}

int	colour_blend(int first, int second)
{
	uint8_t *const	f = (uint8_t*)&first;
	uint8_t *const	s = (uint8_t*)&second;
	double			a;

	a = (f[3] / 255.0);
	f[0] = f[0] * a + s[0] * (1.0 - a);
	f[1] = f[1] * a + s[1] * (1.0 - a);
	f[2] = f[2] * a + s[2] * (1.0 - a);
	return (((int *)f)[0]);
}

// Copies pixel data from one texture to another
void	texture_blit(t_texture src, t_texture dst, t_vec2 pos)
{
	int		x;
	int		y;
	float	a;
	int		col;

	y = -1;
	while (++y < src.height)
	{
		x = -1;
		while (++x < src.width)
		{
			col = colour_blend(pixel_get_s(src, x, y), \
				pixel_get_s(dst, pos.x + x, pos.y + y));
			pixel_set_s(dst, pos.x + x, pos.y + y, col);
		}
	}
}

#include <string.h>
void	texture_clear(t_texture src)
{
	int	x;
	int	y;

	y = -1;
	while (++y < src.height)
	{
		x = -1;
		while (++x < src.width)
		{
			pixel_set(src, x, y, R_ALPHA);
		}
	}
	// FORBIDDEN
	//memset(src.data, 0, (src.bpp / 8) * src.width * src.height);
}

t_texture texture_get_debug_view(t_game *game, int view)
{
	if (game->views[view].rt.img == NULL)
	{
		game->views[view].win = mlx_new_window(game->app.mlx, game->rt0.width, game->rt0.height, "DEBUG VIEW");
		game->views[view].rt = texture_create(game->app.mlx, game->rt0.width, game->rt0.height);
	} 
	return game->views[view].rt;
}

void texture_draw_debug_view(t_game *game, int view)
{
	t_texture rt;

	if (view >= MAX_DEBUG_VIEWS)
		return ;
	mlx_put_image_to_window(game->app.mlx, game->views[view].win, game->views[view].rt.img, 0, 0);
}

void texture_debug_view_blit(t_game *game, int view, t_texture tex, t_vec2 pos)
{
	t_texture rt;

	if (view >= MAX_DEBUG_VIEWS)
		return ;
	rt = texture_get_debug_view(game, view);
	texture_blit(tex, rt, pos);
	mlx_put_image_to_window(game->app.mlx, game->views[view].win, game->views[view].rt.img, 0, 0);
}
