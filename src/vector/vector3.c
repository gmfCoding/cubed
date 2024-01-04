/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:50:56 by clovell           #+#    #+#             */
/*   Updated: 2023/12/26 16:11:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "vector3.h"

t_vec3	v3new(t_vecd x, t_vecd y, t_vecd z)
{
	t_vec3	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}
