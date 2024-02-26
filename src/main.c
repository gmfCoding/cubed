/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 19:40:29 by clovell           #+#    #+#             */
/*   Updated: 2024/01/31 18:00:39 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>

#include "texture.h"
#include "cubed.h"
#include "mini_map.h"
#include "modifiers.h"
#include "a_star.h"

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
	game->world->ent_count = 0;
	game->world->sp_amount = 0;
	if (argc - 1 >= 1)
		map_parse(argc, argv, game);
	else
		map_default_map_init(game);
	game->fpsc = 0;
	game->display_ui = false;
}

void generate_textures(t_game *game)
{
	 game->textures[0] = texture_create(game->app.mlx, WALL_TEX_SIZE, WALL_TEX_SIZE);
	// game->textures[1] = texture_create(game->app.mlx, WALL_TEX_SIZE, WALL_TEX_SIZE);
	// game->textures[2] = texture_create(game->app.mlx, WALL_TEX_SIZE, WALL_TEX_SIZE);
	// game->textures[3] = texture_create(game->app.mlx, WALL_TEX_SIZE, WALL_TEX_SIZE);
	// game->textures[4] = texture_create(game->app.mlx, WALL_TEX_SIZE, WALL_TEX_SIZE);
	// game->textures[5] = texture_create(game->app.mlx, WALL_TEX_SIZE, WALL_TEX_SIZE);
	// game->textures[6] = texture_create(game->app.mlx, WALL_TEX_SIZE, WALL_TEX_SIZE);
	// game->textures[7] = texture_create(game->app.mlx, WALL_TEX_SIZE, WALL_TEX_SIZE);
	// // generate some textures
	// for (int x = 0; x < WALL_TEX_SIZE; x++)
	// {
	// 	for (int y = 0; y < WALL_TEX_SIZE; y++)
	// 	{
	// 		int xorcolor = (x * 256 / WALL_TEX_SIZE) ^ (y * 256 / WALL_TEX_SIZE);
	// 		// int xcolor = x * 256 / texWidth;
	// 		int ycolor = y * 256 / WALL_TEX_SIZE;
	// 		int xycolor = y * 128 / WALL_TEX_SIZE + x * 128 / WALL_TEX_SIZE;
	// 		pixel_set(game->textures[0], x, y, 65536 * 254 * (x != y && x != WALL_TEX_SIZE - y));  // flat red texture with black cross
	// 		pixel_set(game->textures[1], x, y, xycolor + 256 * xycolor + 65536 * xycolor);	  // sloped greyscale
	// 		pixel_set(game->textures[2], x, y, 256 * xycolor + 65536 * xycolor);			  // sloped yellow gradient
	// 		pixel_set(game->textures[3], x, y, xorcolor + 256 * xorcolor + 65536 * xorcolor); // xor greyscale
	// 		pixel_set(game->textures[4], x, y, 256 * xorcolor);								  // xor green
	// 		// pixel_set(game->textures[5], x, y, 65536 * 192 * (x % 16 && y % 16)); //red bricks
	// 		pixel_set(game->textures[5], x, y, (int)(x / 64.0 * 255) << 8 | (int)(y / 64.0 * 255) << 16);
	// 		pixel_set(game->textures[6], x, y, 65536 * ycolor);				   // red gradient
	// 		pixel_set(game->textures[7], x, y, 128 + 256 * 128 + 65536 * 128); // flat grey texture
	// 	}
	// }
	
	game->textures[0] = texture_load(game->app.mlx, "assets/wall.xpm");
	game->textures[1] = texture_load(game->app.mlx, "assets/wall.xpm");
	game->textures[2] = texture_load(game->app.mlx, "assets/wall.xpm");
	game->textures[3] = texture_load(game->app.mlx, "assets/wall.xpm");
	game->textures[4] = texture_load(game->app.mlx, "assets/metal_walkway_acg.xpm");
	game->textures[5] = texture_load(game->app.mlx, "assets/wall.xpm");
	game->textures[6] = texture_load(game->app.mlx, "assets/window.xpm");
	game->textures[7] = texture_load(game->app.mlx, "assets/debug.xpm");
}


int	main(int argc, char **argv)
{
	t_game	game;

//	printf("%s  %s  %f  %f  %d  %d\n", game.world.ent->keys[0].name, game.world.ent->keys[0].doorname, game.world.ent->keys[0].pos.x, \
		       	game.world.ent->keys[0].pos.y, game.world.ent->keys[0].auto_open, game.world.ent->keys[0].collected);
//	free_content(&game);

	game = (t_game){0};
	game.world = malloc(sizeof(t_world));
	*game.world = (t_world){0};
	game.app.mlx = mlx_init();
	world_preset(argc, argv, &game);
	map_print(&game.world->map);

	game.app.mlx = mlx_init();

//	game.world->sp_count = 0;
//	game.world->sprite[0] = (t_sprite){.tex = 7, .pos = v2new(26.5, 9.5)};
//	game.world->map.tiles[26 + 9 * game.world->map.width].sp_count = 1;
//	game.world->map.tiles[26 + 9 * game.world->map.width].sprite[0] = 0;

	modifier_after(&game);

//	print_vector_path(&game);	
	game.rt1 = texture_create(game.app.mlx, R_WIDTH, R_WIDTH);
	game.rt0 = texture_create(game.app.mlx, SCR_WIDTH, SCR_HEIGHT);
//	game.rt2 = texture_get_debug_view(&game, 1);
	game.app.win = mlx_new_window(game.app.mlx, SCR_WIDTH, SCR_HEIGHT, "cub3d");

	generate_textures(&game);

	input_setup(game.app.mlx, game.app.win, &game.input);

	mlx_loop_hook(game.app.mlx, (void *)render, &game);
	mlx_loop(game.app.mlx);

}
