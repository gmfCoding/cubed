/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_opacity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 18:29:39 by clovell           #+#    #+#             */
/*   Updated: 2023/12/13 17:24:34 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <mlx.h>
#include "state.h"
#include "texture.h"
#include "render.h"
#include "task.h"

#define NAME "opacity test"

typedef struct s_test_task
{
	t_game		game;
}				t_test_task;

static void	update(t_test_task *test)
{
	t_game *const	game = &test->game;
	const t_vec2	mouse = v2new(game->input.mouse.x, game->input.mouse.y);
	static int		selected_task = 0;
	if (input_keydown(&game->input, KEY_LARROW))
		selected_task--;
	if (input_keydown(&game->input, KEY_RARROW))
		selected_task = (selected_task + 1) % TASK_LEN;
	if (selected_task < 0)
		selected_task = TASK_LEN - 1;
	printf("selected_task:%d\n", selected_task);
	g_tasks[selected_task]->func(&test->game, g_tasks[selected_task]);
	input_process(&game->input);
}

int	main(void)
{
	t_test_task	test;
	t_game *const	game = &test.game;
	int				i;

	test = (t_test_task){0};
	*game = (t_game){0};
	game->app.mlx = mlx_init();
	game->rt0 = texture_create(game->app.mlx, R_WIDTH, R_HEIGHT);
	game->app.win = mlx_new_window(game->app.mlx, R_WIDTH, R_HEIGHT, NAME);
	input_setup(game->app.mlx, game->app.win, &game->input);
	mlx_loop_hook(game->app.mlx, (void *)update, &test);
	i = -1;
	while (++i < TASK_LEN)
		g_tasks[i]->setup(game, g_tasks[i]);
	mlx_loop(game->app.mlx);
}
