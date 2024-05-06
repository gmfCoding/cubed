/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kep_properties.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 22:57:23 by clovell           #+#    #+#             */
/*   Updated: 2024/05/06 21:49:44 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "orbit.h"
#include "cerror.h"

double	kep_time(t_kep_ang *ang)
{
	err(ang == NULL, E_P E_F);
	return (86400.0 * (ang->time - ang->s_0.time0));
}

double	kep_period(t_kep_path *path)
{
	double	sma3;

	err(path == NULL, E_P E_F);
	sma3 = (path->sma * path->sma * path->sma);
	return (2 * M_PI * sqrt(sma3 / path->sgp_u) / 86400.0);
}

void	kep_clamp(t_kep_path *path)
{
	if (path->aop == 0 || path->aop == M_TAU)
		path->aop = KEP_MIN_EPSILON;
	if (path->lan == 0 || path->aop == M_TAU)
		path->lan = KEP_MIN_EPSILON;
	if (path->inc == 0 || path->aop == M_TAU)
		path->inc = KEP_MIN_EPSILON;
	if (path->ecc == 0 || path->aop == M_TAU)
		path->ecc = KEP_MIN_EPSILON;
}
