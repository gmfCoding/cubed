/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sa_orbit_mui.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 20:18:42 by clovell           #+#    #+#             */
/*   Updated: 2024/02/08 03:06:41 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <mlx.h>
#include "texture.h"
#include "render.h"
#include "ui.h"
#include "tasks/mui.h"
#include "tasks/task_orbit.h"
#include "tasks/mui_orbit.h"
#include "input.h"
#include "app.h"

typedef struct	s_sa_orbit_mui
{
	t_app			app;
	t_texture		rt0;
	t_ui_context	ui;
	t_mui_ctx		mui;
	t_inputctx		input;
}	t_sa_orbit_mui;

void	sa_orbit_mui_process(void *ptr)
{
	t_sa_orbit_mui *const	mui = ptr;
	t_texture		*tex = def_tex_get(&mui->app, "orb_mui_background");

	texture_blit(*tex, mui->rt0, v2new(0, 0));
	mui_render(&mui->mui,  &mui->rt0);
	texture_draw(mui->app, mui->rt0, v2new(0, 0));
	mui_process(&mui->mui, &mui->input);
	input_process(&mui->input);
}

void	mui_def_cache(const t_app *app, t_mui_ctx *mui)
{
	t_mui_base	*base;
	int			i;

	i = -1;
	while (++i < mui->len_buttons)
	{
		base = &mui->buttons[i].base;
		base->def = def_tex_get_def(app, base->id);
	}
	i = -1;
	while (++i < mui->len_dials)
	{
		base = &mui->dials[i].base;
		base->def = def_tex_get_def(app, base->id);
	}
	i = -1;
	while (++i < mui->len_sliders)
	{
		base = &mui->sliders[i].base;
		base->def = def_tex_get_def(app, base->id);
	}
}

int	main(void)
{
	t_sa_orbit_mui	task;

	task.app.mlx = mlx_init();
	task.app.win = mlx_new_window(task.app.mlx, 400, 400, "ORBIT");
	task.rt0 = texture_create(task.app.mlx, 400, 400);
	input_setup(task.app.mlx, task.app.win, &task.input);
	mui_clone(&g_orbit_mui, &task.mui);
	def_tex_add(g_orb_textures, g_orb_textures_len);
	mui_def_cache(&task.app, &task.mui);
	task.ui.parent = &task;
	mlx_loop_hook(task.app.mlx, (void *)&sa_orbit_mui_process, &task);
	mlx_loop(task.app.mlx);
	return (0);
}
