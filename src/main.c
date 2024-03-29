/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 19:40:29 by clovell           #+#    #+#             */
/*   Updated: 2024/03/11 21:00:46 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>

#include "texture.h"
#include "state.h"
#include "mini_map.h"
#include "modifiers.h"
#include "a_star.h"
#include "enemy.h"
#include "destroy.h"

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
	map_parse(argc, argv, game);
	game->fpsc = 0;
	game->display_ui = false;
}

void generate_textures(t_game *game)
{
	t_mod *const north = mod_get_mod(&game->world->map, NORTH_TEXTURE, NULL);
	t_mod *const south = mod_get_mod(&game->world->map, SOUTH_TEXTURE, NULL);
	t_mod *const east = mod_get_mod(&game->world->map, EAST_TEXTURE, NULL);
	t_mod *const west = mod_get_mod(&game->world->map, WEST_TEXTURE, NULL);

	game->textures[TEX_WALL] = texture_load(game->app.mlx, "assets/wall.xpm");
	game->textures[TEX_WALLN] = game->textures[TEX_WALL];
	game->textures[TEX_WALLE] = texture_load(game->app.mlx, "assets/debug.xpm");
	game->textures[TEX_WALLS] = game->textures[TEX_WALL];
	game->textures[TEX_WALLW] = game->textures[TEX_WALL];
	game->textures[TEX_WINDOW] = texture_load(game->app.mlx, "assets/window.xpm");
	game->textures[TEX_DOOR] = game->textures[TEX_WINDOW];
	game->textures[TEX_FLOOR] = texture_load(game->app.mlx, "assets/metal_walkway_acg.xpm");
	game->textures[TEX_CEILING] = game->textures[TEX_FLOOR];
	printf("Loading: %s\n", north->content);
	if (north) 
		game->textures[TEX_WALLN] = texture_load(game->app.mlx, north->content);
	if (south)
		game->textures[TEX_WALLS] = texture_load(game->app.mlx, south->content);
	if (east) 
		game->textures[TEX_WALLE] = texture_load(game->app.mlx, east->content);
	if (west) 
		game->textures[TEX_WALLW] = texture_load(game->app.mlx, west->content);
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
	game.rt2 = texture_create(game.app.mlx, SCR_WIDTH, SCR_HEIGHT);
	game.app.win = mlx_new_window(game.app.mlx, SCR_WIDTH, SCR_HEIGHT, "cub3d");

//ill move this after vv
	if (mod_get_mod(&game.world->map, ENEMY, NULL) != NULL)
	{
		game.world->enemy.path = star_find_path(&game, game.world->enemy.sprite_ref->pos, game.player.pos);
		game.world->enemy.patrol_target.y = game.world->enemy.old_pos[0].y + 0.5;
		game.world->enemy.patrol_target.x = game.world->enemy.old_pos[0].x + 0.5;
	}
//ill move this after ^^
	generate_textures(&game);
	input_setup(game.app.mlx, game.app.win, &game.input);
	shutdown_input_setup(&game);
	mlx_loop_hook(game.app.mlx, (void *)render, &game);
	mlx_loop(game.app.mlx);
}
