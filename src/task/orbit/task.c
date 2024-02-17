/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 19:06:51 by clovell           #+#    #+#             */
/*   Updated: 2024/02/17 20:06:14 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <mlx.h>
#include "orbit.h"
#include "tasks/task_orbit.h"
#include "cubed.h"
#include "vector2.h"
#include "vectorconv.h"
#include "rect.h"

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

void	update_paths(t_sa_orbit_task *t)
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

void	render_paths(t_sa_orbit_task *t, t_texture *rt)
{
	t_kep_ang	ang;
	int			i;
	int			colour;

	colour = ORB_WHITE;
	if (orb_deviation(&t->target_path, &t->paths[t->maneuvers - 1]) < 0.05)
		colour = ORB_GREEN;
	orbit_path_render(&t->target_path, rt, colour | R_ALPHA);
	orbit_path_render(&t->start_path, rt, ORB_BLUE | R_ALPHA);
	i = -1;
	while (++i < t->maneuvers)
	{
		colour = ORB_RED | R_ALPHA;
		if (i != t->active_path)
			orbit_path_render(&t->paths[i], rt, colour);
	}
	orbit_path_render(&t->paths[t->active_path], rt, ORB_GREEN2 | R_ALPHA);
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

/* Copies pixel data from one texture to another, minimally. */
void	texture_blit_rect(t_texture *dst, t_texture *src, t_rect area)
{
	int	j;
	int	i;
	int max_j;
	int max_i;

	max_j = fmin(area.max.y, fmin(src->height, dst->height));
	max_i = fmin(area.max.x, fmin(src->width, dst->width));
	j = fmin(0, area.min.y) - 1;
	while (++j < max_j)
	{
		i = fmin(0, area.min.x) - 1;
		while (++i < area.max.x)
		{
			pixel_set(*dst, i, j, pixel_get(*src, i, j));
		}
	}
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

int	sa_task_orbit_process(t_sa_orbit_task *task)
{
	t_texture *const		tex = def_tex_get(&task->app, "orb_mui_bg");
	t_texture *const		scr = def_tex_get(&task->app, "orb_mui_scr");

	texture_clear(task->rt0, 0);
	texture_blit_rect(&task->rt0, scr, (t_rect){45, 37, 274, 266});
	render_paths(task, &task->rt0);
	texture_blit(*tex, task->rt0, v2new(0, 0));
	mui_render(&task->mui, &task->rt0);
	texture_draw(task->app, task->rt0, v2new(0, 0));
	orbit_mui_control_action(&task->mui);
	mui_process(&task->mui, &task->input);
	input_process(&task->input);
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
