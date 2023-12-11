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

/*
 * include for mouse movement
 *
#include <X11/X.h>
#include <X11/Xlib.h>

int handle_mouse_move(int x, int y, void *param)
{
    printf("mousemoved to: (%d, %d)\n", x, y);
    return 0;
}mlx_hook(game.app.win, MotionNotify, PointerMotionMask, &handle_mouse_move, NULL);	
	




*/
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


void	world_preset(int argc, char **argv, t_game *game)
{

	five_lights_Setup(game);
	game->world.map = map_parse(argc, argv, game);
	
}





int	main(int argc, char **argv)
{
	t_game	game;

	(void)argc;
	(void)argv;

	printf("%s  %s  %f  %f  %d  %d\n", game.world.ent->keys[0].name, game.world.ent->keys[0].doorname, game.world.ent->keys[0].pos.x, \
		       	game.world.ent->keys[0].pos.y, game.world.ent->keys[0].auto_open, game.world.ent->keys[0].collected);
	map_print(&game.world.map);

	free_content(&game);

			

	game = (t_game){0};
	game.app.mlx = mlx_init();

	world_preset(argc, argv, &game);

	game.rt0 = texture_create(game.app.mlx, SCR_WIDTH, SCR_HEIGHT);
	game.rt1 = texture_get_debug_view(&game, 1);
	game.app.win = mlx_new_window(game.app.mlx, SCR_WIDTH, SCR_HEIGHT, "cub3d");

	game.player.pos = v2new(2, 2);
	game.player.dir = v2new(1, 0);
	game.player.plane = v2new(0, 0.66);
	game.player.moveSpeed = 1 / R_TFR * 2.0; // the constant value is in squares/second
	game.player.rotSpeed = 1 / R_TFR * 2.0;  // the constant value is in radians/second
	
	if (game.five_light.run_game == true)
		mlx_mouse_hook(game.app.win, fl_mouse_hook, &game);
	else
		input_setup(game.app.mlx, game.app.win, &game.input);
	mlx_loop_hook(game.app.mlx, (void *)render, &game);
	mlx_loop(game.app.mlx);

}
