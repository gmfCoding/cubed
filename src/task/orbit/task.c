/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 19:06:51 by clovell           #+#    #+#             */
/*   Updated: 2024/02/04 19:54:38 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <mlx.h>
#include "orbit.h"
#include "tasks/task_orbit.h"
#include "cubed.h"
#include "vector2.h"
#include "vectorconv.h"
#include "rect.h"

// void	orbit_thrust_apply
// (t_kep_path *paths[2], t_kep_path *nodes[2], double thrust)
// {
// 	t_orb_cart cart;

// 	cart = (t_orb_cart){0};
// 	orb_cart_pos(paths[0], nodes[0], &cart);
// 	orb_cart_vel(paths[0], nodes[0], &cart);
// 	orb_transform_cart(paths[0], &cart);
// 	cart.vel = v3muls(cart.vel, thrust);
// 	orb_cart_to_kep(&cart, paths[1], nodes[1]);
// }

// void	orbit_thrust_apply(t_kep_path *path,
// t_kep_path *node, double thrust)
// {
// 	t_orb_cart	cart;

// 	cart = (t_orb_cart){0};
// 	orb_cart_pos(path, node, &cart);
// 	orb_cart_vel(path, node, &cart);
// 	orb_transform_cart(path, &cart);
// 	cart.vel = v3muls(cart.vel, thrust);
// 	orb_cart_to_kep(&cart, path, node);
// }

void	update_paths(t_sa_orbit_task *t)
{
	t_orb_cart	cart;
	int			i;

	i = -1;
	t->paths[0] = t->start_path;
	t->nodes[0] = t->start_ang;
	while (++i < t->maneuvers)
	{
		//S
		//A is S but d[A] applied
		//B is A but d[B] applied
		//C is B but d[C] applied
		//D is C but d[D] applied
		//E is D but d[E] applied

		// orbit_thrust_apply((t_kep_path[2]){ &t->paths[i], &t->paths[i + 1]}, \
		// (t_kep_path[2]){ &t->nodes[i], &t->nodes[i + 1]}, t->delta[i]);
		
		orbit_thrust_apply(&t->paths[i], &t->nodes[i], t->delta[i]);
		if (i + 1 < t->maneuvers)
		{
			t->paths[i + 1] = t->paths[i];
			t->nodes[i + 1] = t->nodes[i];
		}
	}
}

void	render_paths(t_sa_orbit_task *t)
{
	int	i;

	i = -1;
	while (++i < t->maneuvers)
	{
		orbit_obj_render(&t->paths[i + 1], &t->nodes[i + 1], &t->rt0);
	}
}

void	orbit_control_action(t_button *btn, t_ui_context *ctx)
{
	t_sa_orbit_task *const	task = ctx->parent;
	char *const				mode = btn->reference;
	t_orb_cart *const		cart = &task->obj0.cart;

	printf("Applying thrust: %s\n", mode);
	orb_cart_pos(&task->obj0.path, &task->obj0.ang, cart);
	orb_cart_vel(&task->obj0.path, &task->obj0.ang, cart);
	orb_transform_cart(&task->obj0.path, cart);
	printf("velocity: %f\n", v3mag(cart->vel));
	if (mode[0] == BS_THRUST[0])
		cart->vel = v3muls(cart->vel, 1.002);
	else if (mode[0] == BS_RTHRUST[0])
		cart->vel = v3muls(cart->vel, 1 / 1.002);
	else if (mode[0] == BS_TIME[0])
		kep_ang_set(&task->obj0.path, &task->obj0.ang, task->obj0.ang.time + 1);
	else if (mode[0] == BS_RTIME[0])
		kep_ang_set(&task->obj0.path, &task->obj0.ang, task->obj0.ang.time - 1);
	if (mode[0] == BS_THRUST[0] || mode[0] == BS_RTHRUST[0])
		orb_cart_to_kep(cart, &task->obj0.path, &task->obj0.ang);
}

t_rect	rect_getbounded(t_rect rect)
{
	t_rect result;
	result.pos = v2sub(rect.pos, v2divs(rect.size, 2));
	result.size = v2add(rect.pos, v2divs(rect.size, 2));
	return (result);
}

bool	rect_contains_v2(t_rect rect, t_vec2 pos)
{
	return (pos.x >= rect.min.x && pos.y >= rect.min.y \
	&& pos.x <= rect.max.x && pos.y <= rect.max.y);
}

void	ui_process_draw( t_ui_context *ctx, t_inputctx *in, t_texture target)
{
	t_button	*curr;
	t_rect		aabb;
	int			i;
	int			col;

	i = -1;
	while (++i < (int)(sizeof(ctx->buttons) / sizeof(t_button)))
	{
		curr = &ctx->buttons[i];
		col = curr->colour;
		aabb = curr->rect;
		if (rect_contains_v2(aabb, v2itov2(in->mouse)))
		{
			col = R_GREEN | R_ALPHA;
			if (input_keyheld(in, MB_LEFT) && curr->callback != NULL)
				curr->callback(curr, ctx);
		}
		texture_draw_line(target, aabb.min, aabb.max, col);
		texture_draw_line(target, aabb.min, v2new(aabb.min.x, aabb.max.y), col);
		texture_draw_line(target, aabb.min, v2new(aabb.max.x, aabb.min.y), col);
		texture_draw_line(target, aabb.max, v2new(aabb.max.x, aabb.min.y), col);
		texture_draw_line(target, aabb.max, v2new(aabb.min.x, aabb.max.y), col);
	}
}

static void	l_draw_debug_info(t_sa_orbit_task *task)
{
	static int64_t	timeprev = 0;
	char *const		debugstr[] = {
		ft_strfmt("fps:%d", (int)(1.0 / ((time_get_ms() - timeprev) / 1000.0))),
	};
	int				i;

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
	texture_clear(task->rt0, 0);
	orbit_path_render(&task->obj0.path, &task->rt0);
	orbit_path_render(&task->obj_path, &task->rt0);
	orbit_obj_render(&task->obj0.path, &task->obj0.ang, &task->rt0);
	usleep(16666);
	ui_process_draw(&task->ui, &task->input, task->rt0);
	texture_draw(task->app, task->rt0, v2new(0,0));
	l_draw_debug_info(task);
	input_process(&task->input);
	return (0);
}

// void draw_element_controls(t_sa_orbit_task *task)
// {
// 	if (input_keydown())
// }

void apply_thrust_test(t_sa_orbit_task *task)
{
	t_orb_cart *const		cart = &task->obj0.cart;

	orb_cart_pos(&task->obj0.path, &task->obj0.ang, cart);
	orb_cart_vel(&task->obj0.path, &task->obj0.ang, cart);
	orb_transform_cart(&task->obj0.path, cart);
	cart->vel = v3muls(cart->vel, 1.05);
	orb_cart_to_kep(cart, &task->obj0.path, &task->obj0.ang);
}

int	main(void)
{
	t_sa_orbit_task	task;

	task.obj0 = (t_orb_obj){0};
	task.sun = orb_body_create_rm(6.96340e8, 1.9891e30);
	//task.earth = orb_body_create_rm(6378100, 5.9722E24);
	task.obj0.self = task.sun;
	task.obj0.path.sgp_u = task.sun.u;
	task.obj0.path.sma = 1 * KM_AU;
	task.obj0.path.ecc = 0.5;
	task.obj0.path.inc = 0.001;
	task.obj0.path.lan = 0.0001;
	task.obj0.path.aop = 0.0001;
	task.obj0.ang.s_0.mna0 = 0;
	task.obj0.ang.s_0.time0 = 0;
	task.obj0.ang.time = 0;
	kep_ang_set(&task.obj0.path, &task.obj0.ang, 0);
	kep_clamp(&task.obj0.path, &task.obj0.ang);
	task.obj_path = task.obj0.path;
	apply_thrust_test(&task);
	task.app.mlx = mlx_init();
	task.app.win = mlx_new_window(task.app.mlx, 400, 400, "ORBIT");
	task.rt0 = texture_create(task.app.mlx, 400, 400);
	input_setup(task.app.mlx, task.app.win, &task.input);
	ui_setup(&task.ui);
	task.ui.parent = &task;
	mlx_loop_hook(task.app.mlx, &sa_task_orbit_process, &task);
	mlx_loop(task.app.mlx);
	return (0);
}
