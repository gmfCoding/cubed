/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equality.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 21:13:34 by clovell           #+#    #+#             */
/*   Updated: 2024/02/13 00:32:53 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <math.h>
#include "orbit.h"
#include "clmath.h"

double	orb_deviation(t_kep_path *a, t_kep_path *b)
{
	double	max;

	max = fabs(a->sma - b->sma) / KM_AU;
	max = fmax(max, fabs(a->ecc - b->ecc));
	if (max < 0.05)
		max = 0;
	max = fmax(max, fabs(angle_diff(a->inc, b->inc)) / M_PI);
	max = fmax(max, fabs(angle_diff(a->aop, b->aop)) / M_PI);
	max = fmax(max, fabs(angle_diff(a->lan, b->lan)) / M_PI);
	return (max);
}
