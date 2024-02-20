/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 19:53:53 by clovell           #+#    #+#             */
/*   Updated: 2024/02/17 20:34:47 by clovell          ###   ########.fr       */
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

void	orbit_path_render(t_kep_path *path, t_texture *rt,
	t_rect trans, int col)
{
	double		a;
	t_kep_ang	ang;
	t_vec3		pos[3];
	int			i;

	i = 0;
	a = 0;
	ang = (t_kep_ang){0};
	while (a < (2.0 * M_PI))
	{
		kep_ang_set(path, &ang, a, ANG_ECCA);
		orb_pos(path, &ang, &pos[0]);
		pos[2].x = orb_transform_x(path, pos[0].x, pos[0].y);
		pos[2].y = orb_transform_y(path, pos[0].x, pos[0].y);
		pos[2].z = orb_transform_z(path, pos[0].x, pos[0].y);
		pos[0] = orb_to_ndc(path, pos[2], v2tov3(trans.pos), trans.size.x);
		if (a != 0)
			texture_draw_line(*rt, v3tov2(pos[1]), \
			v3tov2(pos[0]), col & M_COL | R_ALPHA);
		pos[1] = pos[0];
		a += (2 * PI) / 50.0;
	}
}

void	orbit_obj_render(t_kep_path *path, t_kep_ang *ang,
			t_rect trans, t_texture *rt)
{
	t_vec3		pos[2];

	orb_pos(path, ang, &pos[0]);
	pos[1].x = orb_transform_x(path, pos[0].x, pos[0].y);
	pos[1].y = orb_transform_y(path, pos[0].x, pos[0].y);
	pos[1].z = orb_transform_z(path, pos[0].x, pos[0].y);
	pos[0] = orb_to_ndc(path, pos[1], v2tov3(trans.pos), trans.size.x);
	pixel_set_s(*rt, pos[0].x, pos[0].y, R_ALPHA | R_GREEN);
}
