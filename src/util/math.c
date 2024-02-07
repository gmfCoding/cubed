/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:29:40 by clovell           #+#    #+#             */
/*   Updated: 2024/02/05 17:31:22 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <math.h>
#include "clmath.h"


/* Returns the signed angle difference between a and b. range: `[-PI, PI]`*/
double	angle_diff(double a, double b)
{
	return (atan2(sin(b - a), cos(b - a)));
}

double	flerp(float lerp, float min, float max)
{
	return ((lerp) * (max - min) + min);
}

double	ft_atan2(double y, double x)
{
	if (x > 0)
		return (atan(y / x));
	else if (y >= 0 && x < 0)
		return (atan(y / x) + M_PI);
	else if (y < 0 && x < 0)
		return (atan(y / x) - M_PI);
	else if (y > 0 && x == 0)
		return (M_PI / 2);
	else if (y < 0 && x == 0)
		return (-M_PI / 2);
	else
		return (0);
}

double	facos(double x)
{
	if (x > 1)
		return (0);
	if (x < -1)
		return (M_PI);
	return (acos(x));
}
