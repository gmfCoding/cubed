/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 22:55:52 by clovell           #+#    #+#             */
/*   Updated: 2024/04/29 18:05:44 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "vector2.h"

int	ccw(t_vec2 a, t_vec2 b, t_vec2 c)
{
	return ((c.y - a.y) * (b.x - a.x) > (b.y - a.y) * (c.x - a.x));
}

int	test_two_seg_intersect(t_vec2 a1, t_vec2 b1, t_vec2 a2, t_vec2 b2)
{
	return (ccw(a1, a2, b2) != ccw(b1, a2, b2) \
	&& ccw(a1, b1, a2) != ccw(a1, b1, b2));
}

// Find the intersection point of a1b1 and a2b2
t_vec2	two_seg_intersect(t_vec2 a1, t_vec2 b1, t_vec2 a2, t_vec2 b2)
{
	const t_vecd	a = v2det(a1, b1);
	const t_vecd	b = v2det(a2, b2);
	const t_vecd	c = f2det(f2det(a1.x, 1, b1.x, 1), f2det(a1.y, 1, b1.y, 1), \
	f2det(a2.x, 1, b2.x, 1), f2det(a2.y, 1, b2.y, 1));

	if (c == 0)
		return (v2new(0, 0));
	return \
	(v2new(f2det(a, f2det(a1.x, 1, b1.x, 1), b, f2det(a2.x, 1, b2.x, 1)) / c, \
	f2det(a, f2det(a1.y, 1, b1.y, 1), b, f2det(a2.y, 1, b2.y, 1)) / c));
}
