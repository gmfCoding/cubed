/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cart_to_kep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 18:46:18 by clovell           #+#    #+#             */
/*   Updated: 2024/02/01 20:18:48 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "orbit.h"
#include <stddef.h>

static inline void	wrap_angle(int cond, double *value)
{
	if (cond)
		*value = (2 * M_PI - *value);
}

// Seed with direction first?
// void	orb_cart_to_kep(t_orb_cart *cart, t_kep_path *path, t_kep_ang *ang)
// {
// 	const t_vec3	vel = cart->vel;
// 	const t_vec3	h = v3cross(cart->pos, cart->vel);
// 	const t_vec3	n = v3new(-h.y, h.x, 0);
// 	t_vec3			ev;
// 	double			e;

// 	ev = v3sub(v3divs(v3cross(vel, h), path->sgp_u), v3norm(cart->pos));
// 	e = v3mag(ev);
// 	ang->ta = acos(v3dot(ev, cart->pos) / v3mag(ev) * v3mag(cart->pos));
// 	wrap_angle(v3dot(cart->pos, vel) < 0, &ang->ta);
// 	path->inc = acos(h.z / v3mag(h));
// 	path->ecc = e;
// 	ang->ea = 2 * atan(tan(ang->ta / 2) / sqrt((1 + e) / (1 - e)));
// 	path->lan = acos(n.x / v3mag(n));
// 	wrap_angle(n.y < 0, &path->lan);
// 	path->aop = acos(v3dot(n, ev) / (v3mag(n) * v3mag(ev)));
// 	wrap_angle(ev.z < 0, &path->aop);
// 	ang->mna = ang->ea - e * sin(ang->ea);
// 	path->sma = 1 / (2 / v3mag(cart->pos) - v3mag(vel) \
// 	* v3mag(vel) / path->sgp_u);
// }


double	v3cosa(t_vec3 a, t_vec3 b)
{
	return (v3dot(a, b) / sqrt(v3sqrmag(a) * v3sqrmag(b)));
}


void	orb_cart_to_kep(t_orb_cart *cart, t_kep_path *path, t_kep_ang *ang)
{
	t_vec3	h;
	t_vec3	n;
	t_vec3	e;

	h = v3cross(cart->pos, cart->vel);
	n = v3new(-h.y, h.x, 0);
	e = v3sub(v3divs(v3cross(cart->vel, h), path->sgp_u), v3norm(cart->pos));
	path->ecc = v3mag(e);
	ang->ta = facos(v3cosa(e, cart->pos));
	wrap_angle(v3dot(cart->pos, cart->vel) < 0, &ang->ta);
	path->inc = facos(h.z / v3mag(h));
	ang->ea = atan(tan(ang->ta / 2) / sqrt((1 + path->ecc) / (1 - path->ecc)));
	ang->ea = ang->ea * 2;
	path->lan = facos(n.x / v3mag(n));
	wrap_angle(n.y < 0, &path->lan);
	path->aop = facos(v3cosa(n, e));
	wrap_angle(e.z < 0, &path->aop);
	path->sma = fabs(1.0 / (2.0 / v3mag(cart->pos) - v3sqrmag(cart->vel) / path->sgp_u));
	kep_clamp(path, ang);
}
