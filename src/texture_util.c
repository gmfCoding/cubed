/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:30:29 by clovell           #+#    #+#             */
/*   Updated: 2023/05/17 21:28:34 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "texture.h"
#include "vector2.h"

#define SET pixel_set
#define GET pixel_get

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
