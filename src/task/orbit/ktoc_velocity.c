/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ktoc_velocity.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 23:36:47 by clovell           #+#    #+#             */
/*   Updated: 2024/01/27 01:12:28 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "orbit.h"
#include "cerror.h"

double	orb_speed(t_kep_path *path, t_kep_ang *ang)
{
	ft_asrt(path == NULL || ang == NULL, E_P E_F);
	return (path->sma * (1.0 - path->ecc * cos(ang->ea)));
}

void	orb_cart_vel(t_kep_path *path, t_kep_ang *ang, t_orb_cart *cart)
{
	double	speed;
	double	x;
	double	y;

	ft_asrt(path == NULL || ang == NULL || cart == NULL, E_P E_F);
	x = -sin(ang->ea);
	y = sqrt(1.0 - path->ecc * path->ecc) * cos(ang->ea);
	speed = orb_speed(path, ang);
	cart->ref = OCRF_ORF;
	cart->vel = v3new(speed * x, speed * y, 0);
}
