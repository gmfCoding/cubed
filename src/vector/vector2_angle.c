/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2_angle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 20:47:14 by clovell           #+#    #+#             */
/*   Updated: 2024/02/07 20:47:14 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "vector2.h"
#include "clmath.h"

/* Gets the angle from vec to positive x-axis, range: `[0, TAU]`*/
double	v2x2ang(t_vec2 vec)
{
	return (M_PI - atan2(vec.y, -vec.x));
}
