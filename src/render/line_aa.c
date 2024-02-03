/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_aa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 12:27:00 by clovell           #+#    #+#             */
/*   Updated: 2024/02/03 22:17:29 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <math.h>
#include "texture.h"
#include "vector2i.h"

#include <stdio.h>

// void	texture_draw_line_aa(t_texture data, t_vec2 start, t_vec2 end, int colour)
// {
// 	start.y *= 256;
// 	end.y *= 256;
// 	if (fabs(end.y - start.y) < fabs(end.x - start.x))
// 	{
// 		if (start.x > end.x)
// 			bres_line_low(data, end, start, colour);
// 		else
// 			bres_line_low(data, start, end, colour);
// 	}
// 	else
// 	{
// 		if (start.y > end.y)
// 			bres_line_high(data, end, start, colour);
// 		else
// 			bres_line_high(data, start, end, colour);
// 	}
// }


static void	setPixelAA(t_texture tex, t_vec2i p, int alpha, int c)
{
	const int	t = (255 - alpha);
	const int	aa = (t << OF_RED) | (t << OF_GREEN) | (t << OF_BLUE) | R_ALPHA;

	pixel_set_s(tex, p.x, p.y, c & aa);
}

// void	texture_draw_line_aa(t_texture t, t_vec2i s, t_vec2i e, int c)
// {
//    int	dx = abs(e.x-s.x), sx = s.x<e.x ? 1 : -1;
//    int	dy = abs(e.y-s.y), sy = s.y<e.y ? 1 : -1; 
//    int	err = dx-dy, e2, x2;                       /* error value e_xy */
//    int	ed = dx+dy == 0 ? 1 : sqrt((float)dx*dx+(float)dy*dy);

// 	for ( ; ; ){                                         /* pixel loop */
// 		setPixelAA(t, v2inew(s.x,s.y), 255 * abs(err-dx+dy)/ed, c);
// 		e2 = err; x2 = s.x;
// 		if (2*e2 >= -dx) {				 /* x step */
// 			if (s.x == e.x) break;
// 			if (e2+dy < ed) setPixelAA(t, v2inew(s.x, s.y+sy), 255 * (e2+dy)/ed, c);
// 			err -= dy; s.x += sx; 
// 		} 
// 		if (2*e2 <= dy) {                                     /* y step */
// 			if (s.y == e.y) break;
// 			if (dx-e2 < ed) setPixelAA(t, v2inew(x2+sx,s.y), 255 * (dx-e2)/ed, c);
// 			err += dx; s.y += sy; 
// 	}
// 	}
// }

typedef struct s_bres_aa_ctx
{
	int	dx;
	int	dy;
	int	sy;
	int	sx;
	int	ed;
	int	err;
	int	e2;
	int	x2;
	int	c;
}		t_bres_aa_ctx;


static void	bres_setup(t_bres_aa_ctx *s, t_vec2i b, t_vec2i e)
{
	s->dx = abs(e.x - b.x);
	s->dy = abs(e.y - b.y);
	s->sx = 1;
	s->sy = 1;
	if (b.x >= e.x)
		s->sx = -1;
	if (b.y >= e.y)
		s->sy = -1;
	s->err = s->dx - s->dy;
	s->ed = 1;
	if (s->dx + s->dy != 0)
		s->ed = sqrt((float)s->dx * s->dx + (float)s->dy * s->dy);
}
// void	texture_draw_line_aa(t_texture t, t_vec2i s, t_vec2i e, int c)
// {

// 	while (1)
// 	{                                         /* pixel loop */
// 		setPixelAA(t, s.x,s.y, 255 * abs(err-dx+dy)/ed, c);
// 		e2 = err; x2 = s.x;
// 		if (2*e2 >= -dx) {				 /* x step */
// 			if (s.x == e.x) break;
// 			if (e2+dy < ed) setPixelAA(t, s.x, s.y+sy, 255 * (e2+dy)/ed, c);
// 			err -= dy; s.x += sx; 
// 		} 
// 		if (2*e2 <= dy) {                                     /* y step */
// 			if (s.y == e.y) break;
// 			if (dx-e2 < ed) setPixelAA(t, x2+sx,s.y, 255 * (dx-e2)/ed, c);
// 			err += dx; s.y += sy; 
// 	}
// 	}
// }

static void	bres_aa_x(t_bres_aa_ctx *s, t_texture t, t_vec2i *b, t_vec2i e)
{
	const int	c = (255 * (s->e2 + s->dy));

	if (s->e2 + s->dy < s->ed)
		setPixelAA(t, v2inew(b->x, b->y + s->sy), 255 * (s->e2+s->dy)/s->ed, c);
	//setPixelAA(t, v2inew(b->x, b->y + s->sy), (c / s->ed), c);
	s->err -= s->dy;
	b->x += s->sx;
}

static void	bres_aa_y(t_bres_aa_ctx *s, t_texture t, t_vec2i *b, t_vec2i e)
{
	const int	c = (255 * (s->dx - s->e2));
	if (s->dx - s->e2 < s->ed)
 		setPixelAA(t, v2inew(s->x2+s->sx,b->y), 255 * (s->dx-s->e2)/s->ed, c);
	//setPixelAA(t, v2inew(s->x2 + s->sx, b->y), c / s->ed, c);
	s->err += s->dx;
	b->y += s->sy;
}

void	texture_draw_line_aa(t_texture t, t_vec2i b, t_vec2i e, int c)
{
	t_bres_aa_ctx	s;

	bres_setup(&s, b, e);
	while (1)
	{
		// c = ((255 * abs(s.err - s.dx + s.dy) / s.ed) << OF_ALPHA) \
		// | (~M_APLHA & c);
		//setPixelAA(t, v2inew(b.x, b.y), 255 * abs(s.err - s.dx + s.dy) / s.ed, c);
		setPixelAA(t, v2inew(b.x, b.y), 255 * abs(s.err - s.dx + s.dy) / s.ed, c);

		s.e2 = s.err;
		s.x2 = b.x;
		if (2 * s.e2 >= -s.dx)
		{
			if (b.x == e.x)
				break ;
			bres_aa_x(&s, t, &b, e);
		}
		if (2 * s.e2 <= s.dy)
		{
			if (b.y == e.y)
				break ;
			bres_aa_y(&s, t, &b, e);
		}
	}
}


// static void	setPixelAA(t_texture tex, int x, int y, int c)
// {
// 	const int	t = (255 - ((c & M_APLHA) >> OF_ALPHA));
// 	const int	a = (t << OF_RED) | (t << OF_GREEN) | (t << OF_BLUE) | R_ALPHA;

// 	pixel_set_s(tex, x, y, c & a);
// }
// void	texture_draw_line_aa(t_texture t, t_vec2i b, t_vec2i e, int c)
// {
// 	int			ed;
// 	int			e2;
// 	int			x2;
// 	int			err;
// 	t_vec2i		d;
// 	t_vec2i		s;

// 	d = v2inew(abs(e.x - b.x), abs(e.y - b.y));
// 	s.x = -1;
// 	if (b.x < e.x)
// 		s.x = 1;
// 	s.y = -1;
// 	if (b.y < e.y)
// 		s.y = 1;
// 	ed = 1;
// 	if (d.x + d.y == 0)
// 		ed = sqrt((float)d.x * d.x + (float)d.y * d.y);
// 	err = d.x - d.y;
// 	while (1)
// 	{
// 		c = ((255 * abs(err - d.x + d.y) / ed) << OF_ALPHA) | (~M_APLHA & c);
// 		setPixelAA(t, b.x, b.y, c);
// 		e2 = err;
// 		x2 = b.x;
// 		if (2 * e2 >= -d.x)
// 		{
// 			c = ((255 * (e2 + d.y) / ed) << OF_ALPHA) | (~M_APLHA & c);
// 			if (b.x == e.x)
// 				break ;
// 			if (e2 + d.y < ed)
// 				setPixelAA(t, b.x, b.y + s.y, c);
// 			err -= d.y;
// 			b.x += s.x;
// 		}
// 		if (2 * e2 <= d.y)
// 		{
// 			c = ((255 * (d.x - e2) / ed) << OF_ALPHA) | (~M_APLHA & c);
// 			if (b.y == e.y)
// 				break ;
// 			if (d.x - e2 < ed)
// 				setPixelAA(t, x2 + s.x, b.y, c);
// 			err += d.x;
// 			b.y += s.y;
// 		}
// 	}
// }
