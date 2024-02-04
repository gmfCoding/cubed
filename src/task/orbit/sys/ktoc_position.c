/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ktoc_position.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 23:36:47 by clovell           #+#    #+#             */
/*   Updated: 2024/01/27 01:12:36 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "orbit.h"
#include "cerror.h"

double	orb_radius(t_kep_path *path, t_kep_ang *ang)
{
	ft_asrt(path == NULL || ang == NULL, E_P E_F);
	return (path->sma * (1.0 - path->ecc * cos(ang->ea)));
}

void	orb_pos(t_kep_path *path, t_kep_ang *ang, t_vec3 *cart)
{
	double		radius;

	ft_asrt(path == NULL || ang == NULL || cart == NULL, E_P E_F);
	radius = orb_radius(path, ang);
	*cart = v3new(radius * cos(ang->ta), radius * sin(ang->ta), 0);
}

void	orb_cart_pos(t_kep_path *path, t_kep_ang *ang, t_orb_cart *cart)
{
	ft_asrt(path == NULL || ang == NULL || cart == NULL, E_P E_F);
	cart->ref = OCRF_ORF;
	orb_pos(path, ang, &cart->pos);
}
