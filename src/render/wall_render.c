/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 01:41:22 by clovell           #+#    #+#             */
/*   Updated: 2024/03/11 21:09:29 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* *************** */
/*  prior: loop.c: */
/* *************** */
#include "internal/wall.h"
#include "state.h"
#include "vector2.h"
#include "vector2i.h"
#include "ray.h"

void	render_wall(t_game *game)
{
	t_vert	vert;

	vert.x = -1;
	while (++vert.x < R_WIDTH)
	{
		vert.camera_x = 2 * vert.x / (double)R_WIDTH - 1;
		vert.dir = v2add(game->player.dir, \
		v2muls(game->player.plane, vert.camera_x));
		vert.ray = raycast(game, game->player.pos, vert.dir);
		if (vert.x == R_HEIGHT / 2)
			game->half = vert.ray;
		render_vertical(game, vert);
	}
}
