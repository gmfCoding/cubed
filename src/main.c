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
	game.win = mlx_new_window(game.mlx, RES_WIDTH, RES_HEIGHT, "cub3d");
	game.rt0 = texture_create(game.mlx, RES_WIDTH, RES_HEIGHT);\

	pixel_set(game.rt0, RES_WIDTH/2, RES_HEIGHT/2, 0xff0000);
	texture_draw(&game, game.rt0, v2new(0,0));
	mlx_loop(game.mlx);
}