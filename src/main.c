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

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_game	game;
	
	game = (t_game){0};
	game.mlx = mlx_init();
	game.rt0 = texture_create(game.mlx, SCR_WIDTH, SCR_HEIGHT);
	game.rt1 = texture_get_debug_view(&game, 1);
	game.win = mlx_new_window(game.mlx, SCR_WIDTH, SCR_HEIGHT, "cub3d");

	game.player.pos = v2new(2, 2);
	game.player.dir = v2new(1, 0);
	game.player.plane = v2new(0, 0.66);
	game.player.moveSpeed = 1 / R_TFR * 5.0; // the constant value is in squares/second
	game.player.rotSpeed = 1 / R_TFR * 3.0;  // the constant value is in radians/second

	mlx_loop_hook(game.mlx, (void *)render, &game);
	mlx_hook(game.win, 6, (1L<<6), (void *)on_mouse_move, &game);
	mlx_hook(game.win, 2, (1L<<0), (void *)on_key_press, &game);
	mlx_do_key_autorepeaton(game.mlx); // change to off when we implement the input system

	mlx_mouse_hook(game.win, (void *)on_mouse, &game);
	mlx_loop(game.mlx);
}