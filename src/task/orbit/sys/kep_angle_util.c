/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kep_angle_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 21:49:47 by clovell           #+#    #+#             */
/*   Updated: 2024/02/04 21:54:35 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "orbit.h"

double	orb_time_at_mean(t_kep_path *path, t_kep_ang *ang, double mean)
{
	return ((mean - ang->s_0.mna0) / kep_mean_rate(path));
}

double	orb_ea_to_ma(double ea, double ecc)
{
	return (ea - ecc * sin(ea));
}
