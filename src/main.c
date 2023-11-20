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
	game.win = mlx_new_window(game.mlx, SCR_WIDTH, SCR_HEIGHT, "cub3d");
	game.rt0 = texture_create(game.mlx, SCR_WIDTH, SCR_HEIGHT);

	game.tex = texture_load(game.mlx, "assets/overlay.xpm");
	//pixel_set(game.rt0, SCR_WIDTH/2, SCR_HEIGHT/2, 0xff0000);
	//texture_draw(&game, game.tex, v2new(0,0));
	//texture_draw(&game, texture_load(game.mlx, "assets/debug.xpm"), v2new(0,0));

	mlx_loop_hook(game.mlx, (void *)render, &game);
	mlx_hook(game.win, 6, (1L<<6), (void *)on_mouse_move, &game);
	mlx_hook(game.win, 2, (1L<<0), (void *)on_key_press, &game);

	mlx_mouse_hook(game.win, (void *)on_mouse, &game);
	mlx_loop(game.mlx);
}