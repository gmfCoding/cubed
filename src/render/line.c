/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 12:27:00 by clovell           #+#    #+#             */
/*   Updated: 2024/05/03 20:00:49 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <math.h>
#include "texture.h"
#include "vector2.h"

#include <stdio.h>

// INCORRECT
// static void bres_clip(t_vec2 *start, t_vec2 *end, int maxX, int maxY)
// {
// 	maxX = 400;
// 	maxY = 400;
// 	if (start->x < 0)
// 		start->x = 0;
// 	if (start->y < 0)
// 		start->y = 0;
// 	if (end->x >= maxX)
// 		end->x = maxX - 1;
// 	if (end->y >= maxY)
// 		end->y = maxY - 1;
// }
//bres_clip(&start, &end, data.width, data.height);
static void	bres_line_low(t_texture dst, t_vec2 start, t_vec2 end, int colour)
{
	t_vec2	pos;
	t_vec2	dv;
	int		yi;
	int		error;

	dv = v2sub(end, start);
	yi = 1;
	if (dv.y < 0)
		yi = -1;
	if (dv.y < 0)
		dv.y = -dv.y;
	error = (2 * dv.y) - dv.x;
	pos = start;
	while (pos.x <= end.x)
	{
		pixel_set_s(dst, (int)pos.x, (int)pos.y, colour);
		if (error > 0)
			pos.y = pos.y + yi;
		if (error > 0)
			error = error + (2 * (dv.y - dv.x));
		else
			error = error + 2 * dv.y;
		pos.x++;
	}
}

//bres_clip(&start, &end, data.width, data.height);
static void	bres_line_high(t_texture dst, t_vec2 start, t_vec2 end, int colour)
{
	t_vec2	pos;
	t_vec2	dv;
	int		xi;
	int		error;

	dv = v2sub(end, start);
	xi = 1;
	if (dv.x < 0)
		xi = -1;
	if (dv.x < 0)
		dv.x = -dv.x;
	error = (2 * dv.x) - dv.y;
	pos = start;
	while (pos.y <= end.y)
	{
		pixel_set_s(dst, (int)pos.x, (int)pos.y, colour);
		if (error > 0)
			pos.x = pos.x + xi;
		if (error > 0)
			error = error + (2 * (dv.x - dv.y));
		else
			error = error + 2 * dv.x;
		pos.y++;
	}
}

void	texture_draw_line(t_texture data, t_vec2 start, t_vec2 end, int colour)
{
	if (fabs(end.y - start.y) < fabs(end.x - start.x))
	{
		if (start.x > end.x)
			bres_line_low(data, end, start, colour);
		else
			bres_line_low(data, start, end, colour);
	}
	else
	{
		if (start.y > end.y)
			bres_line_high(data, end, start, colour);
		else
			bres_line_high(data, start, end, colour);
	}
}

void	texture_draw_square(
	t_texture dst, t_vec2 start, t_vec2 width, int colour)
{
	int	y;
	int	x;

	y = -1;
	while (++y < width.y)
	{
		x = -1;
		while (++x < width.x)
		{
			pixel_set_s(dst, start.x + x, start.y + y, colour);
		}
	}
}
