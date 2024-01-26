/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 22:11:31 by clovell           #+#    #+#             */
/*   Updated: 2024/01/27 01:13:38 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "orbit.h"
#include "cerror.h"
#include <stddef.h>

double	orb_transform_x(t_kep_path *p, double x, double y)
{
	double	tx;
	double	ty;

	ft_asrt(p == NULL, E_P E_F);
	tx = cos(p->aop) * cos(p->lan) - sin(p->aop) * cos(p->inc) * sin(p->lan);
	ty = sin(p->aop) * cos(p->lan) + cos(p->aop) * cos(p->inc) * sin(p->lan);
	return (x * tx - y * ty);
}

double	orb_transform_y(t_kep_path *p, double x, double y)
{
	double	tx;
	double	ty;

	ft_asrt(p == NULL, E_P E_F);
	tx = cos(p->aop) * sin(p->lan) - sin(p->aop) * cos(p->inc) * cos(p->lan);
	ty = cos(p->aop) * cos(p->inc) * cos(p->lan) - sin(p->aop) * sin(p->lan);
	return (x * tx - y * ty);
}

double	orb_transform_z(t_kep_path *p, double x, double y)
{
	double	tx;
	double	ty;

	ft_asrt(p == NULL, E_P E_F);
	tx = sin(p->aop) * sin(p->inc);
	ty = cos(p->aop) * sin(p->inc);
	return (x * tx - y * ty);
}

void	orb_transform_cart(t_kep_path *path, t_orb_cart *cart)
{
	ft_asrt(path == NULL || cart == NULL, E_P E_F);
	if (cart->ref == OCRF_IRF)
		return ;
	cart->pos.x = orb_transform_x(path, cart->pos.x, cart->pos.y);
	cart->pos.y = orb_transform_y(path, cart->pos.x, cart->pos.y);
	cart->pos.z = orb_transform_z(path, cart->pos.x, cart->pos.y);
	cart->vel.x = orb_transform_x(path, cart->vel.x, cart->vel.y);
	cart->vel.y = orb_transform_y(path, cart->vel.x, cart->vel.y);
	cart->vel.z = orb_transform_z(path, cart->vel.x, cart->vel.y);
}
