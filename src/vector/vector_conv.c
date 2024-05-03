/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_conv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:51:05 by kmordaun          #+#    #+#             */
/*   Updated: 2024/05/03 16:52:21 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector2.h"
#include "vector3.h"
#include "vector2i.h"

t_vec2	v3tov2(t_vec3 a)
{
	t_vec2	b;

	b.x = a.x;
	b.y = a.y;
	return (b);
}

t_vec3	v2tov3(t_vec2 a)
{
	t_vec3	b;

	b.x = a.x;
	b.y = a.y;
	b.z = 0;
	return (b);
}

t_vec2i	v3tov2i(t_vec3 a)
{
	t_vec2i	b;

	b.x = a.x;
	b.y = a.y;
	return (b);
}

t_vec3	v2itov3(t_vec2i a)
{
	t_vec3	b;

	b.x = a.x;
	b.y = a.y;
	b.z = 0;
	return (b);
}

t_vec2	v2itov2(t_vec2i a)
{
	t_vec2	b;

	b.x = a.x;
	b.y = a.y;
	return (b);
}

t_vec2i	v2tov2i(t_vec2 a)
{
	t_vec2i	b;

	b.x = a.x;
	b.y = a.y;
	return (b);
}
