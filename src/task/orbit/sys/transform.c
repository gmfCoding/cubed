/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 22:11:31 by clovell           #+#    #+#             */
/*   Updated: 2024/02/05 01:47:14 by clovell          ###   ########.fr       */
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
	tx = cos(p->aop) * sin(p->lan) + sin(p->aop) * cos(p->inc) * cos(p->lan);
	ty = cos(p->aop) * cos(p->inc) * cos(p->lan) - sin(p->aop) * sin(p->lan);
	return (x * tx + y * ty);
}

double	orb_transform_z(t_kep_path *p, double x, double y)
{
	double	tx;
	double	ty;

	ft_asrt(p == NULL, E_P E_F);
	tx = sin(p->aop) * sin(p->inc);
	ty = cos(p->aop) * sin(p->inc);
	return (x * tx + y * ty);
}

void	orb_transform_cart(t_kep_path *path, t_orb_cart *cart)
{
	t_vec3	pos;
	t_vec3	vel;

	ft_asrt(path == NULL || cart == NULL, E_P E_F);
	if (cart->ref == OCRF_IRF)
		return ;
	cart->ref = OCRF_IRF;
	pos = cart->pos;
	vel = cart->vel;
	cart->pos.x = orb_transform_x(path, pos.x, pos.y);
	cart->pos.y = orb_transform_y(path, pos.x, pos.y);
	cart->pos.z = orb_transform_z(path, pos.x, pos.y);
	cart->vel.x = orb_transform_x(path, vel.x, vel.y);
	cart->vel.y = orb_transform_y(path, vel.x, vel.y);
	cart->vel.z = orb_transform_z(path, vel.x, vel.y);
}
