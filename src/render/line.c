#include <math.h>
#include "texture.h"
#include "vector2.h"

#include <stdio.h>
static void bres_line_low(t_texture data, t_vec2 start, t_vec2 end, int colour)
{
	t_vec2	pos;
	t_vec2	dv;
	int		yi;
	int		D;

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
		pixel_set(data, (int)pos.x, (int)pos.y, colour);
		if (D > 0)
		{
			pos.y = pos.y + yi;
			D = D + (2 * (dv.y - dv.x));
		}
		else
			D = D + 2 * dv.y;
		pos.x++;
	}
}

// plotLineLow(x0, y0, x1, y1)
//     dx = x1 - x0
//     dy = y1 - y0
//     yi = 1
//     if dy < 0
//         yi = -1
//         dy = -dy
//     end if
//     D = (2 * dy) - dx
//     y = y0

//     for x from x0 to x1
//         plot(x, y)
//         if D > 0
//             y = y + yi
//             D = D + (2 * (dy - dx))
//         else
//             D = D + 2*dy
//         end if

static void bres_line_high(t_texture data, t_vec2 start, t_vec2 end, int colour)
{
	t_vec2	pos;
	t_vec2	dv;
	int		xi;
	int		D;

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
		pixel_set(data, (int)pos.x, (int)pos.y, colour);
		if (D > 0)
		{
			pos.x = pos.x + xi;
			D = D + (2 * (dv.x - dv.y));
		}
		else
			D = D + 2 * dv.x;
		pos.y++;
	}
}
// plotLineHigh(x0, y0, x1, y1)
//     dx = x1 - x0
//     dy = y1 - y0
//     xi = 1
//     if dx < 0
//         xi = -1
//         dx = -dx
//     end if
//     D = (2 * dx) - dy
//     x = x0

//     for y from y0 to y1
//         plot(x, y)
//         if D > 0
//             x = x + xi
//             D = D + (2 * (dx - dy))
//         else
//             D = D + 2*dx
//        end if


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

// plotLine(x0, y0, x1, y1)
//     if abs(y1 - y0) < abs(x1 - x0)
//         if x0 > x1
//             plotLineLow(x1, y1, x0, y0)
//         else
//             plotLineLow(x0, y0, x1, y1)
//         end if
//     else
//         if y0 > y1
//             plotLineHigh(x1, y1, x0, y0)
//         else
//             plotLineHigh(x0, y0, x1, y1)
//         end if
//     end if

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
			pixel_set(data, start.x + x, start.y + y, colour);
		}
	}
}