/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:30:29 by clovell           #+#    #+#             */
/*   Updated: 2023/12/13 17:37:24 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "texture.h"
#include "vector2.h"

#define SET pixel_set
#define GET pixel_get

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

// Copies pixel data from one texture to another with scale
void	texture_blit_s(t_texture src, t_texture dst, t_vec2 pos, int scale)
{
	int		x;
	int		y;
	float	a;
	int		col;

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

void	texture_clear(t_texture src, int colour)
{
	int	x;
	int	y;

	y = -1;
	while (++y < src.height)
	{
		x = -1;
		while (++x < src.width)
		{
			pixel_set(src, x, y, colour);
		}
	}
}

t_texture	texture_copy(void *mlx, t_texture tex, const t_vec2 reg[2], int scale)
{
	t_texture	new;
	t_vec2		size;
	t_vec2		pos;
	t_vec2		o;
	int			col;

	o = reg[0];
	size = v2sub(reg[1], reg[0]);
	new = texture_create(mlx, size.x * scale, size.y * scale);
	pos.y = 0;
	while (pos.y < size.y * scale)
	{
		pos.x = 0;
		while (pos.x < size.x * scale)
		{
			col = GET(tex, o.x + pos.x / scale, o.y + pos.y / scale);
			SET(new, pos.x, pos.y, col);
			pos.x++;
		}
		pos.y++;
	}
	return (new);
}


t_texture	texture_rotate(void *mlx, t_texture t, int rot)
{
	int			y;
	int			x;
	t_texture	dst;

	dst = texture_create(mlx, t.width, t.height);
	y = 0;
	while (y < t.height)
	{
		x = 0;
		while (x < t.width)
		{
			if (rot == 1)
				SET(dst, x, y, GET(t, y, t.width - x - 1));
			else if (rot == 2)
				SET(dst, x, y, GET(t, t.width - x - 1, t.height - y - 1));
			else if (rot == 3)
				SET(dst, x, y, GET(t, t.height - y - 1, x));
			else
				SET(dst, x, y, GET(t, x, y));
			x++;
		}
		y++;
	}
	return (dst);
}
