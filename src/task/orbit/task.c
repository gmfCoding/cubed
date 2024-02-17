/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 19:06:51 by clovell           #+#    #+#             */
/*   Updated: 2024/02/17 21:21:46 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <mlx.h>
#include "orbit.h"
#include "tasks/task_orbit.h"
#include "cubed.h"
#include "vector2.h"
#include "vectorconv.h"
#include "rect.h"



static void	l_draw_debug_info_active(t_task_orbit *task, char **str)
{
	t_vec3		pos;
	t_vec3		vel;
	t_kep_path *const	path = &task->paths[task->active_path];

	// TODO: Remove?
	orb_pos(path, &task->nodes[task->active_path], &pos);
	orb_vel(path, &task->nodes[task->active_path], &vel);
	pos.x = orb_transform_x(path, pos.x, pos.y);
	pos.y = orb_transform_y(path, pos.x, pos.y);
	pos.z = orb_transform_z(path, pos.x, pos.y);
	pos = orb_to_ndc(&task->paths[task->active_path], pos, \
	v3new(200, 200, 0), 100);
	vel.x = orb_transform_x(path, vel.x, vel.y);
	vel.y = orb_transform_y(path, vel.x, vel.y);
	vel.z = orb_transform_z(path, vel.x, vel.y);
	*(&str[0]) = ft_strfmt("(%S)", v3toa(pos.v));
	*(&str[1]) = ft_strfmt("(%S)", v3toa(vel.v));
	*(&str[2]) = ft_strfmt("(%f, %f, %f, %f, %f, %f)", path->sma, \
	path->ecc, path->inc, path->lan, path->aop, task->mean[task->active_path]);
}

static void	l_draw_debug_info(t_task_orbit *task)
{
	static int64_t	timeprev = 0;
	char			*debugstr[4];
	int				i;

	debugstr[0] = ft_strfmt("fps:%d", \
	(int)(1.0 / ((time_get_ms() - timeprev) / 1000.0)));
	l_draw_debug_info_active(task, &debugstr[1]);
	i = -1;
	while (++i < (int)(sizeof(debugstr) / sizeof(*debugstr)))
	{
		mlx_string_put(task->app.mlx, task->app.win, 0, \
			i * 12 + 12, 0xFFFFFF, debugstr[i]);
		free(debugstr[i]);
	}
	timeprev = time_get_ms();
}

// void	orbit_crt(t_texture *dst, t_texture *src, t_rect area)
// {
// 	int	j;
// 	int	i;
// 	int max_j;
// 	int max_i;
// 	int col;

// 	max_j = fmin(area.max.y, fmin(src->height, dst->height));
// 	max_i = fmin(area.max.x, fmin(src->width, dst->width));
// 	j = fmin(0, area.min.y) - 1;
// 	while (++j < max_j)
// 	{
// 		i = fmin(0, area.min.x) - 1;
// 		while (++i < area.max.x)
// 		{
// 			col = colour_blend(pixel_get_s(*src, i, j), \
// 				pixel_get_s(*dst, i, j));
// 			pixel_set_s(*dst, i, j, col);
// 		}
// 	}
// }

int	sa_task_orbit_process(t_task_orbit *task)
{

	input_process(&task->input);
	l_draw_debug_info(task);
	usleep(16666); // Forbidden
	return (0);
}

