/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_blit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 20:39:14 by clovell           #+#    #+#             */
/*   Updated: 2024/02/20 17:48:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <math.h>
#include "texture.h"
#include "rect.h"

/* Copies pixel data from one texture to another, minimally. */
void	texture_blit_rect(t_texture *dst, t_texture *src, t_rect area)
{
	int	j;
	int	i;
	int	max_j;
	int	max_i;

	max_j = fmin(area.max.y, fmin(src->height, dst->height));
	max_i = fmin(area.max.x, fmin(src->width, dst->width));
	j = fmin(0, area.min.y) - 1;
	while (++j < max_j)
	{
		i = fmin(0, area.min.x) - 1;
		while (++i < area.max.x)
		{
			pixel_set(*dst, i, j, pixel_get(*src, i, j));
		}
	}
}

// Copies pixel data from one texture to another
void	texture_blit(t_texture src, t_texture dst, t_vec2 pos)
{
	int	x;
	int	y;
	int	col;

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

// Copies pixel data from one texture to another with scale
void	texture_blit_s(t_texture src, t_texture dst, t_vec2 pos, int scale)
{
	int	x;
	int	y;
	int	col;

	y = -1;
	while (++y < src.height * scale)
	{
		x = -1;
		while (++x < src.width * scale)
		{
			col = colour_blend(pixel_get_s(src, x / scale, y / scale), \
				pixel_get_s(dst, pos.x + x, pos.y + y));
			pixel_set_s(dst, pos.x + x, pos.y + y, col);
		}
	}
}
