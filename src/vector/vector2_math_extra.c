/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2_math_extra.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:49:06 by clovell           #+#    #+#             */
/*   Updated: 2024/03/09 02:33:29 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <math.h>
#include "vector2.h"

t_vecd	v2sqrmag(t_vec2 vec)
{
	return (vec.x * vec.x + vec.y * vec.y);
}

t_vecd	v2mag(t_vec2 vec)
{
	return (sqrt(v2sqrmag(vec)));
}

t_vec2	v2norm(t_vec2 vec)
{
	t_vecd	mag;

	mag = v2mag(vec);
	if (mag == 0)
		return (v2new(0, 0));
	vec.x /= mag;
	vec.y /= mag;
	return (vec);
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

double v2dot(t_vec2 a, t_vec2 b)
{
  return (a.x * b.x + a.y * b.y);
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

double	v2invlerp(t_vec2 a, t_vec2 b, t_vec2 c)
{
	const t_vec2	ac = v2sub(c, a);
	const t_vec2	ab = v2sub(b, a);

	return (v2dot(ac, ab) / v2dot(ab, ab));
}
