/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 19:53:53 by clovell           #+#    #+#             */
/*   Updated: 2024/02/04 19:54:02 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cubed.h"
#include "vectorconv.h"
#include "orbit.h"

t_vec3	orb_to_ndc(t_kep_path *path, t_vec3 cart, t_vec3 offset, t_vecd scale)
{
	t_vec3	dev;

	dev = v3divs(cart, KM_AU);
	dev = v3muls(dev, scale);
	dev = v3add(dev, offset);
	return (dev);
}

static double	orb_time_at_ang(t_kep_path *path, t_kep_ang *ang, double mean)
{
	return ((mean - ang->s_0.mna0) / kep_mean_rate(path));
}

static double	orb_ea_to_ma(double ea, double ecc)
{
	return (ea - ecc * sin(ea));
}

void	orbit_path_render(t_kep_path *path, t_texture *rt)
{
	double		a;
	t_kep_ang	ang;
	t_vec3		pos[2];
	int			i;

	i = 0;
	a = 0;
	ang = (t_kep_ang){0};
	while (a < (2.0 * M_PI))
	{
		kep_ang_set(path, &ang, \
		orb_time_at_ang(path, &ang, orb_ea_to_ma(a, path->ecc)) / 86400);
		orb_pos(path, &ang, &pos);
		pos[0].x = orb_transform_x(path, pos[0].x, pos[0].y);
		pos[0].y = orb_transform_y(path, pos[0].x, pos[0].y);
		pos[0].z = orb_transform_z(path, pos[0].x, pos[0].y);
		pos[0] = orb_to_ndc(path, pos[0], v3new(200, 200, 0), 100);
		if (a != 0)
			texture_draw_line(*rt, v3tov2(pos[1]), \
			v3tov2(pos[0]), R_RED | R_ALPHA);
		pos[1] = pos[0];
		a += (2 * PI) / 50.0;
	}
}

void	orbit_obj_render(t_kep_path *path, t_kep_ang *ang, t_texture *rt)
{
	t_vec3		pos;

	orb_pos(path, ang, &pos);
	pos.x = orb_transform_x(path, pos.x, pos.y);
	pos.y = orb_transform_y(path, pos.x, pos.y);
	pos.z = orb_transform_z(path, pos.x, pos.y);
	pos = orb_to_ndc(path, pos, v3new(200, 200, 0), 100);
	pixel_set_s(*rt, pos.x, pos.y, R_ALPHA | R_GREEN);
}
