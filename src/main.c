/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 19:40:29 by clovell           #+#    #+#             */
/*   Updated: 2024/04/09 16:34:17 by kmordaun         ###   ########.fr       */
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
	


	game.rt1 = texture_create(game.app.mlx, R_WIDTH, R_WIDTH);
	game.rt0 = texture_create(game.app.mlx, SCR_WIDTH, SCR_HEIGHT);
	game.rt2 = texture_create(game.app.mlx, SCR_WIDTH, SCR_HEIGHT);
	

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


t_err	world_preset(int argc, char **argv, t_game *game)
{
	game->five_light.difficulty = 1;
	game->five_light.run_game = false;
	game->world->ent_count = 0;
	game->world->sp_amount = 0;
	game->fpsc = 0;
	game->display_ui = false;
	printf("how do you do sir\n");
	return (map_parse(argc, argv, game));
}

void	nsew_textures(t_game *game)
{
	t_mod *const north = mod_get_mod(&game->world->map, MT_NORTH_TEXTURE, NULL);
	t_mod *const south = mod_get_mod(&game->world->map, MT_SOUTH_TEXTURE, NULL);
	t_mod *const east = mod_get_mod(&game->world->map, MT_EAST_TEXTURE, NULL);
	t_mod *const west = mod_get_mod(&game->world->map, MT_WEST_TEXTURE, NULL);

	if (north) 
		game->textures[TEX_WALLN] = texture_load(game->app.mlx, north->content);
	if (south)
		game->textures[TEX_WALLS] = texture_load(game->app.mlx, south->content);
	if (east) 
		game->textures[TEX_WALLE] = texture_load(game->app.mlx, east->content);
	if (west) 
		game->textures[TEX_WALLW] = texture_load(game->app.mlx, west->content);
}
/*
void	title_imgs_load_all(t_game *game)
{
	game->textures[TEX_TITLE_MISSION_COMPLETED] = texture_load(game->app.mlx, "assets/menu/mission_competed.xpm");
	game->textures[TEX_TITLE_MISSION_FAILED] = texture_load(game->app.mlx, "assets/menu/mission_failed.xpm");
	game->textures[TEX_TITLE_NEXT_LEVEL_0] = texture_load(game->app.mlx, "assets/menu/next_level_0.xpm");
	game->textures[TEX_TITLE_NEXT_LEVEL_1] = texture_load(game->app.mlx, "assets/menu/next_level_1.xpm");
	game->textures[TEX_TITLE_RETRY_0] = texture_load(game->app.mlx, "assets/menu/retry_0.xpm");
	game->textures[TEX_TITLE_RETRY_1] = texture_load(game->app.mlx, "assets/menu/retry_1.xpm");
	game->textures[TEX_TITLE_CREATED_CHRIS_KYLE] = texture_load(game->app.mlx, "assets/menu/created_chris_kyle.xpm");
	game->textures[TEX_TITLE_MAIN_MENU_0] = texture_load(game->app.mlx, "assets/menu/main_menu_0.xpm");
	game->textures[TEX_TITLE_MAIN_MENU_1] = texture_load(game->app.mlx, "assets/menu/main_menu_1.xpm");
}


void	generate_all_textures(t_game *game)
{
	enemy_load_directory(game, "assets/enemy_sprites/");
	game->textures[TEX_WINDOW] = texture_load(game->app.mlx, "assets/window.xpm");
	game->textures[TEX_DOOR] = game->textures[TEX_WINDOW];
	game->textures[TEX_FLOOR] = texture_load(game->app.mlx, "assets/metal_walkway_acg.xpm");
	game->textures[TEX_CEILING] = game->textures[TEX_FLOOR];
	game->textures[TEX_FIVE_LIGHTS] = texture_load(game->app.mlx, "assets/five_lights_wall.xpm");
	game->textures[TEX_UI_CONTROLS] = texture_load(game->app.mlx, "assets/ui/controls.xpm");
	game->textures[TEX_UI_INTERACT_BRIGHT] = texture_load(game->app.mlx, "assets/ui/interact_bright.xpm");
	game->textures[TEX_UI_INTERACT_DUL] = texture_load(game->app.mlx, "assets/ui/interact_dal.xpm");
	game->textures[TEX_UI_DOOR_LOCKED] = texture_load(game->app.mlx, "assets/ui/promt_door_locked.xpm");
	game->textures[TEX_UI_TASK_INACTIVE] = texture_load(game->app.mlx, "assets/ui/inactive_task.xpm");
	game->loaded_index[0] = TEX_ARRAY_SIZE;
	title_imgs_load_all(game);
	nsew_textures(game);

//	printf("Loading: %s\n", north->content);
}

*/
void generate_textures(t_game *game)
{
	game->textures[TEX_SKYBOX] = texture_load(game->app.mlx, "assets/skybox.xpm");
	game->textures[TEX_WALL] = texture_load(game->app.mlx, "assets/wall.xpm");
	game->textures[TEX_WALLN] = game->textures[TEX_WALL];
	game->textures[TEX_WALLE] = texture_load(game->app.mlx, "assets/debug.xpm");
	game->textures[TEX_WALLS] = game->textures[TEX_WALL];
	game->textures[TEX_WALLW] = game->textures[TEX_WALL];
}

void	setup_world(int argc, char **argv, t_game *game)
{
	game->title.state = RUNNING_GAME;
	if (world_preset(argc, argv, game))
	{
		free(game->world);
		return ;
	}
	map_print(&game->world->map);
	modifier_after(game);
	if (mod_get_mod(&game->world->map, MT_ENEMY, NULL) != NULL)
	{
		game->world->enemy->path = star_find_path(game, game->world->enemy->sprite_ref->pos, game->player.pos);
		game->world->enemy->patrol_target.y = game->world->enemy->old_pos[0].y + 0.5;
		game->world->enemy->patrol_target.x = game->world->enemy->old_pos[0].x + 0.5;
	}
	event_player(game, true);
	nsew_textures(game);
}



int	main(int argc, char **argv)
{
	t_game	game;
	
	game = (t_game){0};
	game.world = malloc(sizeof(t_world));
	*game.world = (t_world){0};
	game.app.mlx = mlx_init();
	title_screen(&game);
	game.loaded_index[0] = 0;
	game.loaded_index[1] = 1;
	game.loaded_index[2] = 0;
	game.title.state = TITLE;
	game.five_light.difficulty = 1;
	game.five_light.run_game = false;
	game.world->ent_count = 0;
	game.world->sp_amount = 0;
	game.fpsc = 0;
	game.display_ui = false;
	generate_textures(&game);
	if (argc == 2)
	{
	//	generate_all_textures(&game);
		setup_world(argc, argv, &game);
	}
	game.rt1 = texture_create(game.app.mlx, R_WIDTH, R_WIDTH);
	game.rt0 = texture_create(game.app.mlx, SCR_WIDTH, SCR_HEIGHT);
	game.rt2 = texture_create(game.app.mlx, SCR_WIDTH, SCR_HEIGHT);
	game.app.win = mlx_new_window(game.app.mlx, SCR_WIDTH, SCR_HEIGHT, "cub3d");
	input_setup(game.app.mlx, game.app.win, &game.input);
	shutdown_input_setup(&game);
	mlx_loop_hook(game.app.mlx, (void *)render, &game);
	mlx_loop(game.app.mlx);
}
