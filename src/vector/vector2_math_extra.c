/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2_math_extra.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:49:06 by clovell           #+#    #+#             */
/*   Updated: 2024/02/08 02:32:19 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <math.h>
#include "vector2.h"

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
