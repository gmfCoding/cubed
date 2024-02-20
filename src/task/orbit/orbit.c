/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orbit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 01:18:06 by clovell           #+#    #+#             */
/*   Updated: 2024/02/19 19:43:52 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "task.h"
#include "tasks/task_orbit.h"
#include "render.h"
#include "orbit.h"

int	task_orbit_setup(t_game *game, t_task *base)
{
	static t_orb_gen	g_orbgen = {
		.sma = {0.5 * KM_AU, 1.25 * KM_AU}, .ecc = {0.0001, 0.8},
		.inc = {0.0001, 0.0001}, .aop = {0.0001, M_TAU}, .lan = {0.0001, 0.0001}
	};
	t_task_orbit *const	task = (t_task_orbit*)base;

	msrand(&task->rand, 51234);
	orb_generate(&task->target_path, &g_orbgen, &task->rand);
	task->sun = orb_body_create_rm(6.96340e8, 1.9891e30);
	task->target_path.sgp_u = task->sun.u;
	task->start_path = (t_kep_path){
		.sma = KM_AU, .ecc = 0.0001, .inc = 0.0001,
		.lan = 0.0001, .aop = 0.0001, .sgp_u = task->sun.u};
	task->start_ang = (t_kep_ang){0};
	task->maneuvers = 5;
	task->active_path = 0;
	ft_memsetf64(task->delta, 1.0, T_ORBIT_MAX_MAN);
	ft_memsetf64(task->mean, 0.0, T_ORBIT_MAX_MAN);
	kep_clamp(&task->start_path, &task->start_ang);
	kep_ang_set(&task->start_path, &task->start_ang, 90, ANG_TIME);
	update_paths(task);
	task->mui.ctx = task;
	mui_orbit_setup(&game->app, &task->mui);
	orbit_mui_control_action(&task->mui);
	return (0);
}

void	orbit_thrust_apply(t_kep_path *path,
t_kep_ang *node, double thrust)
{
	t_orb_cart	cart;
	t_vec3		ecv;

	cart = (t_orb_cart){0};
	orb_cart_pos(path, node, &cart);
	orb_cart_vel(path, node, &cart);
	cart.vel = v3muls(cart.vel, thrust);
	orb_transform_cart(path, &cart);
	orb_cart_to_kep(&cart, path, node);
}

void	update_paths(t_task_orbit *t)
{
	t_orb_cart	cart;
	int			i;

	i = -1;
	t->paths[0] = t->start_path;
	t->nodes[0] = t->start_ang;
	while (++i < t->maneuvers)
	{
		kep_ang_set(&t->paths[i], &t->nodes[i], t->mean[i], ANG_MEAN);
		orbit_thrust_apply(&t->paths[i], &t->nodes[i], t->delta[i]);
		if (i + 1 < t->maneuvers)
		{
			t->paths[i + 1] = t->paths[i];
			t->nodes[i + 1] = t->nodes[i];
		}
	}
}

void	render_paths(t_task_orbit *t, t_texture *rt, t_rect vis)
{
	t_kep_ang	ang;
	int			i;
	int			colour;

	colour = ORB_WHITE;
	if (orb_deviation(&t->target_path, &t->paths[t->maneuvers - 1]) < 0.05)
		colour = ORB_GREEN;
	orbit_path_render(&t->target_path, rt, vis, colour | R_ALPHA);
	orbit_path_render(&t->start_path, rt, vis, ORB_BLUE | R_ALPHA);
	i = -1;
	while (++i < t->maneuvers)
	{
		colour = ORB_RED | R_ALPHA;
		if (i != t->active_path)
			orbit_path_render(&t->paths[i], rt, vis, colour);
	}
	orbit_path_render(&t->paths[t->active_path], rt, vis, ORB_GREEN2 | R_ALPHA);
	i = -1;
	while (++i < t->maneuvers)
	{
		ang = (t_kep_ang){0};
		kep_ang_set(&t->paths[i], &ang, t->mean[i], ANG_MEAN);
		orbit_obj_render(&t->paths[i], &ang, vis, rt);
	}
}

int	task_orbit_render(t_game *game, t_task *base)
{
	t_task_orbit *const	task = (t_task_orbit*)base;
	t_texture *const	tex = def_tex_get(&game->app, "orb_mui_bg");
	t_texture *const	scr = def_tex_get(&game->app, "orb_mui_scr");
	static t_texture	rt;
	static bool			rtl = false;

	if (!rtl)
	{
		rt = texture_create(game->app.mlx, 400, 400);
		rtl = true;
	}
	//texture_blit_rect(&rt, scr, (t_rect){45, 37, 274, 266});
	texture_blit(*scr, rt, v2new(0, 0));
	render_paths(task, &rt, (t_rect){task->scr_offset, {task->zoom, 0}});
	texture_blit(*tex, rt, v2new(0, 0));
	mui_render(&task->mui, &rt);
	texture_blit_s(rt, game->rt0, v2new(90, 90), 2);
	orbit_mui_control_action(&task->mui);
	mui_process(&task->mui, &game->input);
	return (0);
}
