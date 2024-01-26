/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kep_angle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 22:54:35 by clovell           #+#    #+#             */
/*   Updated: 2024/01/27 01:50:42 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <math.h>
#include <stddef.h>
#include "orbit.h"
#include "cerror.h"

double	kep_mean_rate(t_kep_path *path)
{
	double	sma3;

	ft_asrt(path == NULL, E_P E_F);
	sma3 = path->sma * path->sma * path->sma;
	return (sqrt((path->sgp_u) / (sma3)));
}

double	kep_mean(t_kep_path *path, t_kep_ang *ang)
{
	ft_asrt(path == NULL || ang == NULL, E_P E_F);
	return (ang->s_0.mna0 + kep_time(ang) * kep_mean_rate(path));
}

double	kep_ta(t_kep_path *path, t_kep_ang *ang)
{
	double	x;
	double	y;

	ft_asrt(path == NULL || ang == NULL, E_P E_F);
	x = sqrt(1.0 + path->ecc) * sin (ang->ea / 2.0);
	y = sqrt(1.0 - path->ecc) * cos(ang->ea / 2);
	return (2 * atan2(x, y));

}

double	kep_ang_set(t_kep_path *path, t_kep_ang *ang, double tn)
{
	ft_asrt(path == NULL || ang == NULL, E_P E_F);
	ang->time = tn;
	ang->mna = kep_mean(path, ang);
	ang->ea = kep_anom_e(path, ang);
	ang->ta = kep_ta(path, ang);
}

double	kep_anom_e(t_kep_path *path, t_kep_ang *ang)
{
	double	target;
	double	error;
	double	prev;
	int		i;

	ft_asrt(path == NULL || ang == NULL, E_P E_F);
	target = ang->mna;
	if (path->ecc > 0.8)
		target = M_PI;
	error = target - path->ecc * sin(target) - ang->mna;
	i = -1;
	while (fabs(error) >= EA_MAX_ERROR && ++i < EA_MAX_ITER)
	{
		prev = target;
		target = prev - (error / 1.0 - path->ecc * cos(prev));
		error = target - path->ecc * sin(target) - ang->mna;
	}
	return (target);
}

// double kep_ang_step(t_kep_path *path, t_kep_ang *ang, double step)
// {
// 	ang->time += step;
// 	kep_ang_set(path, ang, ang->time);
// }