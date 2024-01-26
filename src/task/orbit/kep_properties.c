/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kep_properties.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 22:57:23 by clovell           #+#    #+#             */
/*   Updated: 2024/01/27 01:46:35 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "orbit.h"
#include "cerror.h"

double	kep_time(t_kep_ang *ang)
{
	ft_asrt(ang == NULL, E_P E_F);
	return (86400.0 * (ang->time - ang->s_0.time0));
}

double	kep_period(t_kep_path *path)
{
	double	sma3;

	ft_asrt(path == NULL, E_P E_F);
	sma3 = (path->sma * path->sma * path->sma);
	return (2 * M_PI * sqrt(sma3 / path->sgp_u) / 86400.0);
}
