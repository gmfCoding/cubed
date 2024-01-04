/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2_math_extra.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:49:06 by clovell           #+#    #+#             */
/*   Updated: 2023/12/26 16:31:06 by marvin           ###   ########.fr       */
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

t_vecd v2pcross(t_vec2 a, t_vec2 b)
{
	return (a.x * b.y - a.y * b.x);
}