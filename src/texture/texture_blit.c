/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_blit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 20:39:14 by clovell           #+#    #+#             */
/*   Updated: 2024/04/07 16:28:56 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <math.h>
#include "texture.h"
#include "rect.h"
#include <math.h>
#include "clmath.h"
#include <sys/param.h>

/* Copies pixel data from one texture to another, minimally. */
void	texture_blit_rect(t_texture *dst, t_texture *src, t_rect area)
{
	int	j;
	int	i;
	int	max_j;
	int	max_i;
	max_j = MIN(area.max.y, MIN(src->height, dst->height));
	max_i = MIN(area.max.x, MIN(src->width, dst->width));
	j = MIN(0, area.min.y) - 1;
	while (++j < max_j)
	{
		i = MIN(0, area.min.x) - 1;
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
	int	min_x;
	int	min_y;

	min_x = MIN(dst.width, src.width);
	min_y = MIN(dst.height, src.height);
	y = -1;
	while (++y < min_y)
	{
		x = -1;
		while (++x < min_x)
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
