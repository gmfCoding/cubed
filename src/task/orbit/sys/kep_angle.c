/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kep_angle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 22:54:35 by clovell           #+#    #+#             */
/*   Updated: 2024/05/06 21:49:44 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <math.h>
#include <stddef.h>
#include "orbit.h"
#include "cerror.h"

double	kep_mean_rate(t_kep_path *path)
{
	double	sma3;

	err(path == NULL, E_P E_F);
	sma3 = path->sma * path->sma * path->sma;
	return (sqrt((path->sgp_u) / (sma3)));
}

double	kep_mean(t_kep_path *path, t_kep_ang *ang)
{
	err(path == NULL || ang == NULL, E_P E_F);
	return (ang->s_0.mna0 + kep_time(ang) * kep_mean_rate(path));
}

double	kep_ta(t_kep_path *path, t_kep_ang *ang)
{
	double	x;
	double	y;

	err(path == NULL || ang == NULL, E_P E_F);
	x = sqrt(1.0 + path->ecc) * sin (ang->ea / 2.0);
	y = sqrt(1.0 - path->ecc) * cos(ang->ea / 2);
	return (2 * ft_atan2(x, y));
}

void	kep_ang_set(t_kep_path *path, t_kep_ang *ang, double v, t_angt t)
{
	err(path == NULL || ang == NULL, E_P E_F);
	if (t == ANG_TIME)
	{
		ang->time = v;
		ang->mna = kep_mean(path, ang);
		ang->ea = kep_anom_e(path, ang);
		ang->ta = kep_ta(path, ang);
	}
	else if (t == ANG_MEAN)
		kep_ang_set(path, ang, \
		orb_time_at_mean(path, ang, v) / 86400.0, ANG_TIME);
	else if (t == ANG_ECCA)
		kep_ang_set(path, ang, orb_time_at_mean(path, ang, \
		orb_ea_to_ma(v, path->ecc)) / 86400.0, ANG_TIME);
}

double	kep_anom_e(t_kep_path *path, t_kep_ang *ang)
{
	double	ea0;
	double	ea1;
	double	error;
	int		i;

	err(path == NULL || ang == NULL, E_P E_F);
	ea1 = ang->mna;
	if (path->ecc > 0.8)
		ea1 = M_PI;
	error = ea1 - path->ecc * sin(ea1) - ang->mna;
	i = -1;
	while (fabs(error) >= EA_MAX_ERROR && ++i < EA_MAX_ITER)
	{
		ea0 = ea1;
		ea1 = ea0 - (error / (1.0 - path->ecc * cos(ea0)));
		error = ea1 - path->ecc * sin(ea1) - ang->mna;
	}
	return (ea1);
}

// double kep_ang_step(t_kep_path *path, t_kep_ang *ang, double step)
// {
// 	ang->time += step;
// 	kep_ang_set(path, ang, ang->time);
// }