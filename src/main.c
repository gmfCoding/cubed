#include <mlx.h>
#include <stdio.h>

#include "texture.h"
#include "cubed.h"

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_game	game;
	game = (t_game){0};
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, SCR_WIDTH, SCR_HEIGHT, "cub3d");
	game.rt0 = texture_create(game.mlx, SCR_WIDTH, SCR_HEIGHT);\

	pixel_set(game.rt0, SCR_WIDTH/2, SCR_HEIGHT/2, 0xff0000);
	texture_draw(&game, game.rt0, v2new(0,0));
	mlx_loop_hook(game.mlx, (void *)render, &game);
	mlx_hook(game.win, 6, (1L<<6), (void *)on_mouse_move, &game);

	mlx_mouse_hook(game.win, (void *)on_mouse, &game);
	mlx_loop(game.mlx);
}