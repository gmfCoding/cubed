/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_extra.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 01:07:12 by clovell           #+#    #+#             */
/*   Updated: 2024/04/16 19:03:32 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "orbit.h"
#include "texture.h"

void	orbit_obj_render_at(t_kep_path *path, double mean,
			t_angt angt, t_texture *rt)
{
	t_kep_ang	ang;
	t_vec3		pos[2];

	ang = (t_kep_ang){0};
	kep_ang_set(path, &ang, mean, angt);
	orb_pos(path, &ang, &pos[0]);
	pos[1].x = orb_transform_x(path, pos[0].x, pos[0].y);
	pos[1].y = orb_transform_y(path, pos[0].x, pos[0].y);
	pos[1].z = orb_transform_z(path, pos[0].x, pos[0].y);
	pos[0] = orb_to_ndc(pos[1], v3new(200, 200, 0), 100);
	pixel_set_s(*rt, pos[0].x, pos[0].y, R_ALPHA | R_GREEN);
}
