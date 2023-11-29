/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2_math.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:49:54 by clovell           #+#    #+#             */
/*   Updated: 2023/11/22 20:47:23 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "vector2.h"

t_vec2	v2add(t_vec2 f, t_vec2 s)
{
	t_vec2	vec;

	vec.x = f.x + s.x;
	vec.y = f.y + s.y;
	return (vec);
}

t_vec2	v2sub(t_vec2 f, t_vec2 s)
{
	t_vec2	vec;

	vec.x = f.x - s.x;
	vec.y = f.y - s.y;
	return (vec);
}

t_vec2	v2inv(t_vec2 f)
{
	t_vec2	vec;

	vec.x = -f.x;
	vec.y = -f.y;
	return (vec);
}

t_vec2	v2mulv(t_vec2 f, t_vec2 s)
{
	t_vec2	vec;

	vec.x = f.x * s.x;
	vec.y = f.y * s.y;
	return (vec);
}

t_vec2	v2muls(t_vec2 f, float s)
{
	t_vec2	vec;

	vec.x = f.x * s;
	vec.y = f.y * s;
	return (vec);
}
