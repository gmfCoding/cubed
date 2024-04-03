/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2_math_extra.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:49:06 by clovell           #+#    #+#             */
/*   Updated: 2024/03/19 00:20:22 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <math.h>
#include "vector2.h"

t_vecd	f4det(t_vecd x1, t_vecd y1, t_vecd x2, t_vecd y2)
{
	return (x1 * y2 - y1 * x2);
}

t_vecd	v2det(t_vec2 a, t_vec2 b)
{
	return (a.x * b.y - a.y * b.x);
}

t_vecd	v2dot(t_vec2 a, t_vec2 b)
{
	return (a.x * b.x + a.y * b.y);
}

t_vec2	v2lerp(t_vec2 a, t_vec2 b, double t)
{
	return (v2add(a, v2muls(v2sub(b, a), fmin(1, fmax(0, t)))));
}

double	v2invlerp(t_vec2 a, t_vec2 b, t_vec2 c)
{
	const t_vec2	ac = v2sub(c, a);
	const t_vec2	ab = v2sub(b, a);

	return (v2dot(ac, ab) / v2dot(ab, ab));
}

t_vec2	v2diff(t_vec2 f, t_vec2 s)
{
	t_vec2	vec;
	
	vec.x = 0;
	vec.y = 0;
	if (f.x > s.x)
		vec.x = f.x - s.x;
	else
		vec.x = s.x - f.x;
	if (f.y > s.y)
		vec.y = f.y - s.y;
	else
		vec.y = s.y - f.y;
	return (vec);
}

/*
	Projects point a onto line segment BC
*/
t_vec2	v2proj_line(t_vec2 a, t_vec2 b, t_vec2 c)
{
	const t_vec2	diff = v2sub(a, b);
	const t_vec2	dir = v2norm(v2sub(b, c));
	const t_vecd	scale = v2dot(dir, diff);

	return (v2add(b, v2muls(dir, scale)));
}