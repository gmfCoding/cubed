// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   orbit_task.c                                       :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/01/10 19:06:51 by clovell           #+#    #+#             */
// /*   Updated: 2024/02/12 18:09:47 by clovell          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */
// #include <mlx.h>
// #include "orbit.h"
// #include "tasks/task_orbit.h"
// #include "cubed.h"
// #include "vector2.h"
// #include "vectorconv.h"
// #include "rect.h"

// void	orbit_thrust_apply(t_kep_path *path,
// t_kep_ang *node, double thrust)
// {
// 	t_orb_cart	cart;

// 	cart = (t_orb_cart){0};
// 	orb_cart_pos(path, node, &cart);
// 	orb_cart_vel(path, node, &cart);
// 	cart.vel = v3muls(cart.vel, thrust);
// 	orb_transform_cart(path, &cart);
// 	orb_cart_to_kep(&cart, path, node);
// }

// void	update_paths(t_sa_orbit_task *t)
// {
// 	t_orb_cart	cart;
// 	int			i;

// 	i = -1;
// 	t->paths[0] = t->start_path;
// 	t->nodes[0] = t->start_ang;
// 	while (++i < t->maneuvers)
// 	{
// 		kep_ang_set(&t->paths[i], &t->nodes[i], t->mean[i], ANG_MEAN);
// 		orbit_thrust_apply(&t->paths[i], &t->nodes[i], t->delta[i]);
// 		if (i + 1 < t->maneuvers)
// 		{
// 			t->paths[i + 1] = t->paths[i];
// 			t->nodes[i + 1] = t->nodes[i];
// 		}
// 	}
// }

// void	render_paths(t_sa_orbit_task *t)
// {
// 	int			i;
// 	int			colour;

// 	colour = R_RED | R_GREEN | R_BLUE;
// 	if (orb_deviation(&t->target_path, &t->paths[t->maneuvers - 1]) < 0.05)
// 		colour = R_GREEN;
// 	orbit_path_render(&t->target_path, &t->rt0, colour | R_ALPHA);
// 	orbit_path_render(&t->start_path, &t->rt0, R_BLUE | R_ALPHA);
// 	i = -1;
// 	while (++i < t->maneuvers)
// 	{
// 		colour = R_RED | R_ALPHA;
// 		if (i == t->active_path)
// 			colour = R_GREEN & 0x7F7F | R_ALPHA;
// 		orbit_path_render(&t->paths[i], &t->rt0, colour);
// 	}
// 	orbit_obj_render_at(&t->paths_all[t->active_path], t->mean[t->active_path], ANG_MEAN, &t->rt0);
// }



// void	orbit_control_action(t_button *btn, t_ui_context *ctx)
// {
// 	t_sa_orbit_task *const	task = ctx->parent;
// 	char *const				mode = btn->reference;

// 	if (mode[0] == BS_PNODE[0])
// 		task->active_path++;
// 	if (mode[0] == BS_NNODE[0])
// 		task->active_path--;
// 	if (task->active_path < 0)
// 		task->active_path = 0;
// 	if (task->active_path >= task->maneuvers)
// 		task->active_path = task->maneuvers - 1;
// 	if (mode[0] == BS_THRUST[0])
// 		task->delta[task->active_path] += 0.01;
// 	else if (mode[0] == BS_RTHRUST[0])
// 		task->delta[task->active_path] -= 0.01;
// 	else if (mode[0] == BS_TIME[0])
// 		task->mean[task->active_path] += M_PI / 100.0;
// 	else if (mode[0] == BS_RTIME[0])
// 		task->mean[task->active_path] -= M_PI / 100.0;
// 	printf("delta:%f\n", task->delta[task->active_path]);
// 	printf("mean:%f\n", task->mean[task->active_path]);
// 	// if (mode[0] == BS_THRUST[0] || mode[0] == BS_RTHRUST[0])
// 	// 	orb_cart_to_kep(cart, &task->obj0.path, &task->obj0.ang);
// 	// printf("Applying thrust: %s\n", mode);
// 	// orb_cart_pos(&task->obj0.path, &task->obj0.ang, cart);
// 	// orb_cart_vel(&task->obj0.path, &task->obj0.ang, cart);
// 	// orb_transform_cart(&task->obj0.path, cart);
// 	// printf("velocity: %f\n", v3mag(cart->vel));
// 	// if (mode[0] == BS_THRUST[0])
// 	// 	cart->vel = v3muls(cart->vel, 1.002);
// 	// else if (mode[0] == BS_RTHRUST[0])
// 	// 	cart->vel = v3muls(cart->vel, 1 / 1.002);
// 	// // else if (mode[0] == BS_TIME[0])
// 	// // 	kep_ang_set(&task->obj0.path, &task->obj0.ang, task->obj0.ang.time + 1);
// 	// // else if (mode[0] == BS_RTIME[0])
// 	// // 	kep_ang_set(&task->obj0.path, &task->obj0.ang, task->obj0.ang.time - 1);
// 	// // if (mode[0] == BS_THRUST[0] || mode[0] == BS_RTHRUST[0])
// 	// // 	orb_cart_to_kep(cart, &task->obj0.path, &task->obj0.ang);
// 	update_paths(task);
// }

// static void l_draw_debug_info_active(t_sa_orbit_task *task, char **str)
// {
// 	t_vec3		pos;
// 	t_vec3		vel;
// 	t_kep_path	*path = &task->paths[task->active_path];

// 	orb_pos(path, &task->nodes[task->active_path], &pos);
// 	orb_vel(path, &task->nodes[task->active_path], &vel);
// 	pos.x = orb_transform_x(path, pos.x, pos.y);
// 	pos.y = orb_transform_y(path, pos.x, pos.y);
// 	pos.z = orb_transform_z(path, pos.x, pos.y);
// 	pos = orb_to_ndc(&task->paths[task->active_path], pos, v3new(200, 200, 0), 100);
// 	vel.x = orb_transform_x(path, vel.x, vel.y);
// 	vel.y = orb_transform_y(path, vel.x, vel.y);
// 	vel.z = orb_transform_z(path, vel.x, vel.y);
// 	*(&str[0]) = ft_strfmt("(%S)", v3toa(pos.v));
// 	*(&str[1]) = ft_strfmt("(%S)", v3toa(vel.v));
// 	*(&str[2]) = ft_strfmt("(%f, %f, %f, %f, %f, %f)", path->sma, path->ecc, path->inc, path->lan, path->aop, task->mean[task->active_path]);
// }

// static void	l_draw_debug_info(t_sa_orbit_task *task)
// {
// 	static int64_t	timeprev = 0;
// 	char			*debugstr[4];
// 	int				i;

// 	debugstr[0] = ft_strfmt("fps:%d", \
// 	(int)(1.0 / ((time_get_ms() - timeprev) / 1000.0)));
// 	l_draw_debug_info_active(task, &debugstr[1]);
// 	i = -1;
// 	while (++i < (int)(sizeof(debugstr) / sizeof(*debugstr)))
// 	{
// 		mlx_string_put(task->app.mlx, task->app.win, 0, \
// 			i * 12 + 12, 0xFFFFFF, debugstr[i]);
// 		free(debugstr[i]);
// 	}
// 	timeprev = time_get_ms();
// }

// int	sa_task_orbit_process(t_sa_orbit_task *task)
// {
// 	texture_clear(task->rt0, 0);
// 	render_paths(task);
// 	usleep(16666);
// 	ui_process_draw(&task->ui, &task->input, task->rt0);
// 	texture_draw(task->app, task->rt0, v2new(0, 0));
// 	l_draw_debug_info(task);
// 	input_process(&task->input);
// 	return (0);
// }

// // void draw_element_controls(t_sa_orbit_task *task)
// // {
// // 	if (input_keydown())
// // }

// const t_orb_gen	g_orbgen = {
// 	.sma = {0.5 * KM_AU, 1.25 * KM_AU},	
// 	.ecc = {KEP_MIN_EPSILON, 0.8},	
// 	.inc = {KEP_MIN_EPSILON, KEP_MIN_EPSILON},	
// 	.aop = {KEP_MIN_EPSILON, M_TAU},	
// 	.lan = {KEP_MIN_EPSILON, KEP_MIN_EPSILON},	
// };

// void	ui_setup(t_ui_context *ctx);

// int	main(void)
// {
// 	t_sa_orbit_task	task;

// 	msrand(&task.rand, 51234);
// 	orb_generate(&task.target_path, &g_orbgen, &task.rand);
// 	task.sun = orb_body_create_rm(6.96340e8, 1.9891e30);
// 	task.target_path.sgp_u = task.sun.u;
// 	task.start_path.sgp_u = task.sun.u;
// 	task.start_path.sma = 1 * KM_AU;
// 	task.start_path.ecc = 0.0001;
// 	task.start_path.inc = 0.0001;
// 	task.start_path.lan = 0.0001;
// 	task.start_path.aop = 0.0001;
// 	task.start_ang.s_0.mna0 = 0;
// 	task.start_ang.s_0.time0 = 0;
// 	task.start_ang.time = 0;
// 	task.maneuvers = 3;
// 	task.active_path = 0;
// 	task.delta[0] = 1.0;
// 	task.delta[1] = 1.0;
// 	task.delta[2] = 1.0;
// 	task.mean[0] = 0;
// 	task.mean[1] = 0;
// 	task.mean[2] = 0;
// 	//task.mean[0] = 58.0915542285;
// 	//update_paths(&task);
// 	kep_clamp(&task.start_path, &task.start_ang);
// 	kep_ang_set(&task.start_path, &task.start_ang, 90, ANG_TIME);
// 	update_paths(&task);
// 	task.app.mlx = mlx_init();
// 	task.app.win = mlx_new_window(task.app.mlx, 400, 400, "ORBIT");
// 	task.rt0 = texture_create(task.app.mlx, 400, 400);
// 	input_setup(task.app.mlx, task.app.win, &task.input);
// 	ui_setup(&task.ui);
// 	task.ui.parent = &task;
// 	mlx_loop_hook(task.app.mlx, &sa_task_orbit_process, &task);
// 	mlx_loop(task.app.mlx);
// 	return (0);
// }
