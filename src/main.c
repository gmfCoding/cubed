/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 19:40:29 by clovell           #+#    #+#             */
/*   Updated: 2023/11/29 17:00:58 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>

#include "texture.h"
#include "cubed.h"

// int	main(int argc, char **argv)
// {
// 	(void)argc;
// 	(void)argv;
// 	int width = 960;
// 	int height = 960;
// 	void *mlx = mlx_init();
// 	void *win = mlx_new_window(mlx, width, height, "SO_LONG");

// 	t_texture tex = texture_load(mlx, "assets/debug.xpm");
// 	unsigned char alpha = pixel_get(tex, 0, 0) >> 24 & 0xFF;
// 	printf("%x\n", alpha);
// 	mlx_put_image_to_window(mlx, win, tex.img, 0 ,0);
// 	mlx_loop(mlx);
// }


t_world	world_preset(int argc, char **argv, t_world *world)
{
	world->map = map_parse(argc, argv, world);
	return (*world);
}


int	main(int argc, char **argv)
{
	t_game	game;

	(void)argc;
	(void)argv;

	t_world	world;
	world = world_preset(argc, argv, &world);
	printf("%s  %s  %f  %f  %d  %d\n", world.ent->keys[0].name, world.ent->keys[0].doorname, world.ent->keys[0].pos.x, \
		       	world.ent->keys[0].pos.y, world.ent->keys[0].auto_open, world.ent->keys[0].collected);
	map_print(&world.map);

	free_content(&world);
/*
	game = (t_game){0};
	game.app.mlx = mlx_init();
	game.rt0 = texture_create(game.app.mlx, SCR_WIDTH, SCR_HEIGHT);
	game.rt1 = texture_get_debug_view(&game, 1);
	game.app.win = mlx_new_window(game.app.mlx, SCR_WIDTH, SCR_HEIGHT, "cub3d");

	game.player.pos = v2new(2, 2);
	game.player.dir = v2new(1, 0);
	game.player.plane = v2new(0, 0.66);
	game.player.moveSpeed = 1 / R_TFR * 2.0; // the constant value is in squares/second
	game.player.rotSpeed = 1 / R_TFR * 2.0;  // the constant value is in radians/second

	input_setup(game.app.mlx, game.app.win, &game.input);
	mlx_loop_hook(game.app.mlx, (void *)render, &game);
	mlx_loop(game.app.mlx);
*/
}
