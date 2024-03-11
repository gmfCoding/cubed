/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   body.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 00:00:36 by clovell           #+#    #+#             */
/*   Updated: 2024/02/13 00:33:36 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "orbit.h"

t_orb_body	orb_body_create_rd(double radius, double density)
{
	t_orb_body	body;

	body.density = density;
	body.radius = radius;
	body.mass = 4.0 / 3.0 * M_PI * radius * radius * radius * density;
	body.u = body.mass * KM_G;
	return (body);
}

t_orb_body	orb_body_create_rm(double radius, double mass)
{
	t_orb_body		body;
	const double	vol = 4.0 / 3.0 * M_PI * radius * radius * radius;

	body.density = mass / vol;
	body.radius = radius;
	body.mass = mass;
	body.u = body.mass * KM_G;
	return (body);
}
