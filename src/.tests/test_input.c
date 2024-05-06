/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 19:41:09 by clovell           #+#    #+#             */
/*   Updated: 2023/12/13 17:24:34 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include <mlx.h>
#include <stdio.h>
#include "state.h"
#include "cubed.h"

int input_on_render(t_game *game)
{
	static int frame = -1;
	frame++;
	if (input_keydown(game, KEY_A))
		printf("%d:input_keydown A\n", frame);

	if (input_keyheld(game, KEY_A))
		printf("%d:input_keyheld A\n", frame);

	if (input_keyup(game, KEY_A))
		printf("%d:input_keyup A\n", frame);
	usleep(100000);
	input_process(game);
	return 0;
}

int main(void)
{
	t_game	game;
	
	game = (t_game){0};
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, R_WIDTH, R_HEIGHT, "cub3d");
	game.input = (t_inputctx){0};

	input_setup(&game);
	mlx_loop_hook(game.mlx, (void *)input_on_render, &game);
	mlx_loop(game.mlx);
}
