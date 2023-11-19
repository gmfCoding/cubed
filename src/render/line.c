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

static void bres_line_low(t_texture data, t_vec2 start, t_vec2 end, int colour)
{
	t_vec2	pos;
	t_vec2	dv;
	int		yi;
	int		D;

	//bres_clip(&start, &end, data.width, data.height);
	dv = v2sub(end, start);
	yi = 1;
	if (dv.y < 0)
		yi = -1;
	if (dv.y < 0)
		dv.y = -dv.y;
	D = (2 * dv.y) - dv.x;
	pos = start;
	while (pos.x <= end.x)
	{
		if (pos.x >= 0 && pos.x < data.width && pos.y >= 0 && pos.y < data.height)
			pixel_set(data, (int)pos.x, (int)pos.y, colour);
		if (D > 0)
			pos.y = pos.y + yi;
		if (D > 0)
			D = D + (2 * (dv.y - dv.x));
		else
			D = D + 2 * dv.y;
		pos.x++;
	}
}

static void bres_line_high(t_texture data, t_vec2 start, t_vec2 end, int colour)
{
	t_vec2	pos;
	t_vec2	dv;
	int		xi;
	int		D;

	//bres_clip(&start, &end, data.width, data.height);
	dv = v2sub(end, start);
	xi = 1;
	if (dv.x < 0)
		xi = -1;
	if (dv.x < 0)
		dv.x = -dv.x;
	D = (2 * dv.x) - dv.y;
	pos = start;
	while (pos.y <= end.y)
	{
		// TODO instead of checking every pixel, squish the end and start to be within the screen, bres_clip.
		if (pos.x >= 0 && pos.x < data.width && pos.y >= 0 && pos.y < data.height)
			pixel_set(data, (int)pos.x, (int)pos.y, colour);
		if (D > 0)
			pos.x = pos.x + xi;
		if (D > 0)
			D = D + (2 * (dv.x - dv.y));
		else
			D = D + 2 * dv.x;
		pos.y++;
	}
}

void texture_draw_line(t_texture data, t_vec2 start, t_vec2 end, int colour)
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

void texture_draw_square(t_texture data, t_vec2 start, t_vec2 width, int colour)
{
	int y;
	int x;

	y = -1;
	while (++y < width.y)
	{
		x = -1;
		while (++x < width.x)
		{
			pixel_set_s(data, start.x + x, start.y + y, colour);
		}
	}
}