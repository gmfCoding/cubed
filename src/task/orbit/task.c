/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 19:06:51 by clovell           #+#    #+#             */
/*   Updated: 2024/02/14 17:02:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <mlx.h>
#include "orbit.h"
#include "tasks/task_orbit.h"
#include "cubed.h"
#include "vector2.h"
#include "vectorconv.h"
#include "rect.h"

void	render_paths(t_sa_orbit_task *t, t_texture *rt)
{
	t_kep_ang	ang;
	int			i;
	int			colour;

	colour = R_RED | R_GREEN | R_BLUE;
	if (orb_deviation(&t->target_path, &t->paths[t->maneuvers - 1]) < 0.05)
		colour = R_GREEN;
	orbit_path_render(&t->target_path, rt, colour | R_ALPHA);
	orbit_path_render(&t->start_path, rt, R_BLUE | R_ALPHA);
	i = -1;
	while (++i < t->maneuvers)
	{
		colour = R_RED | R_ALPHA;
		if (i == t->active_path)
			colour = R_GREEN & 0x7F7F | R_ALPHA;
		orbit_path_render(&t->paths[i], rt, colour);
	}
	i = -1;
	while (++i < t->maneuvers)
	{
		ang = (t_kep_ang){0};
		kep_ang_set(&t->paths[i], &ang, t->mean[i], ANG_MEAN);
		orbit_obj_render(&t->paths[i], &ang, rt);
	}
}

static void	l_draw_debug_info_active(t_sa_orbit_task *task, char **str)
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

static void	l_draw_debug_info(t_sa_orbit_task *task)
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

int	sa_task_orbit_process(t_sa_orbit_task *task)
{
	t_texture *const		tex = def_tex_get(&task->app, "orb_mui_bg");

	texture_clear(task->rt0, 0);
	texture_blit(*tex, task->rt0, v2new(0, 0));
	mui_render(&task->mui, &task->rt0);
	orbit_mui_control_action(&task->mui);
	mui_process(&task->mui, &task->input);
	input_process(&task->input);
	render_paths(task, &task->rt0);
	texture_draw(task->app, task->rt0, v2new(0, 0));
	l_draw_debug_info(task);
	usleep(16666); // Forbidden
	return (0);
}

const t_orb_gen	g_orbgen = {
	.sma = {0.5 * KM_AU, 1.25 * KM_AU},	
	.ecc = {KEP_MIN_EPSILON, 0.8},	
	.inc = {KEP_MIN_EPSILON, KEP_MIN_EPSILON},	
	.aop = {KEP_MIN_EPSILON, M_TAU},	
	.lan = {KEP_MIN_EPSILON, KEP_MIN_EPSILON},	
};

void	ui_setup(t_ui_context *ctx);

int	main(void)
{
	t_sa_orbit_task	task;

	msrand(&task.rand, 51234);
	orb_generate(&task.target_path, &g_orbgen, &task.rand);
	task.sun = orb_body_create_rm(6.96340e8, 1.9891e30);
	task.target_path.sgp_u = task.sun.u;
	task.start_path.sgp_u = task.sun.u;
	task.start_path.sma = 1 * KM_AU;
	task.start_path.ecc = 0.0001;
	task.start_path.inc = 0.0001;
	task.start_path.lan = 0.0001;
	task.start_path.aop = 0.0001;
	task.start_ang.s_0.mna0 = 0;
	task.start_ang.s_0.time0 = 0;
	task.start_ang.time = 0;
	task.maneuvers = 5;
	task.active_path = 0;
	task.delta[0] = 1.0;
	task.delta[1] = 1.0;
	task.delta[2] = 1.0;
	task.delta[3] = 1.0;
	task.delta[4] = 1.0;
	task.mean[0] = 0;
	task.mean[1] = 0;
	task.mean[2] = 0;
	task.mean[3] = 0;
	task.mean[4] = 0;
	kep_clamp(&task.start_path, &task.start_ang);
	kep_ang_set(&task.start_path, &task.start_ang, 90, ANG_TIME);
	update_paths(&task);
	task.app.mlx = mlx_init();
	task.app.win = mlx_new_window(task.app.mlx, 400, 400, "ORBIT");
	task.rt0 = texture_create(task.app.mlx, 400, 400);
	input_setup(task.app.mlx, task.app.win, &task.input);
	task.mui.ctx = &task;
	mui_orbit_setup(&task.app, &task.mui);
	mlx_loop_hook(task.app.mlx, &sa_task_orbit_process, &task);
	mlx_loop(task.app.mlx);
	return (0);
}
