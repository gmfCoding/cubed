#include "texture.h"
#include "state.h"
#include "destroy.h"

#include <dirent.h>
#include <string.h>


void	title_end_screen(t_game *game)
{
	texture_blit(game->textures[TEX_TITLE_SPACE_BACK], game->rt0, v2new(0, 0));
	
//write credits here and a button to go back to title screen
	if(input_keydown(&game->input, KEY_ENTER))
		game->title.state = BACK_TO_TITLE;
}

void	title_back_to_title(t_game *game)
{
	int i;
	i = -1;
	free(game->world->enemy->path);
	while (game->mmap.tiles[++i].img != NULL)//i have to set the tiles back to null coz i use null to assign images
		game->mmap.tiles[i].img = NULL;
	free(game->world);
	game->world = malloc(sizeof(t_world));
	*game->world = (t_world){0};

	game->title.state = TITLE;
}

void	title_load_and_run(t_game *game)
{
	char path[50];
	char *argv[2];
	ft_strcpy(path, "maps/");
	ft_strcat(path, game->title.map_str[game->title.anim_forward]);
	argv[0] = "";
	argv[1] = path;
	printf("file load%s\n", argv[1]);
	
	setup_world(2, argv, game);
	game->title.state = RUNNING_GAME;
}
void	title_display_maps(t_game *game)
{
	int	y = 200;
	int	i;

	i = -1;
	while(++i < game->title.map_str_amount)
	{
		mlx_string_put(game->app.mlx, game->app.win, 400, y += 30, 0x333333, game->title.map_str[i]);
		if (i == game->title.anim_forward)
			mlx_string_put(game->app.mlx, game->app.win, 400, y, 0xffffff, game->title.map_str[i]);
	}
}

void	title_show_load_map(t_game *game)
{
	texture_blit(game->textures[TEX_TITLE_SPACE_BACK], game->rt0, v2new(0, 0));
	texture_blit(game->textures[TEX_TITLE_LOADMAP], game->rt0, v2new(270, 105));
	if(input_keydown(&game->input, KEY_BACKSPACE))
		game->title.state = SELECT_START;
	if(input_keydown(&game->input, KEY_UARROW) || input_keydown(&game->input, KEY_W))
		game->title.anim_forward--;
	if(input_keydown(&game->input, KEY_DARROW) || input_keydown(&game->input, KEY_S))
		game->title.anim_forward++;
	if(game->title.anim_forward < 0)
		game->title.anim_forward = game->title.map_str_amount - 1;
	if(game->title.anim_forward > game->title.map_str_amount - 1)
		game->title.anim_forward = 0;
	if(input_keydown(&game->input, KEY_ENTER))
		game->title.state = LOAD_AND_RUN;
}

void	title_show_options(t_game *game)
{
	texture_blit(game->textures[TEX_TITLE_SPACE_BACK], game->rt0, v2new(0, 0));
	texture_blit(game->textures[TEX_TITLE_OPTIONS_0], game->rt0, v2new(270, 105));
	if(input_keydown(&game->input, KEY_BACKSPACE))
		game->title.state = SELECT_OPTIONS;
//	if(input_keydown(&game->input, KEY_UARROW) || input_keydown(&game->input, KEY_W))
//		game->title.state = SELECT_QUIT;
}

void	title_show_select_quit(t_game *game)
{
	texture_blit(game->textures[TEX_TITLE_SPACE_BACK], game->rt0, v2new(0, 0));
	texture_blit(game->textures[TEX_TITLE_START_0], game->rt0, v2new(295, 105));
	texture_blit(game->textures[TEX_TITLE_OPTIONS_0], game->rt0, v2new(295, 305));
	texture_blit(game->textures[TEX_TITLE_QUIT_1], game->rt0, v2new(295, 505));
	if(input_keydown(&game->input, KEY_DARROW) || input_keydown(&game->input, KEY_S))
		game->title.state = SELECT_START;
	if(input_keydown(&game->input, KEY_UARROW) || input_keydown(&game->input, KEY_W))
		game->title.state = SELECT_OPTIONS;
	if(input_keydown(&game->input, KEY_ENTER))
		game_destroy(game);
}

void	title_show_select_options(t_game *game)
{
	texture_blit(game->textures[TEX_TITLE_SPACE_BACK], game->rt0, v2new(0, 0));
	texture_blit(game->textures[TEX_TITLE_START_0], game->rt0, v2new(295, 105));
	texture_blit(game->textures[TEX_TITLE_OPTIONS_1], game->rt0, v2new(295, 305));
	texture_blit(game->textures[TEX_TITLE_QUIT_0], game->rt0, v2new(295, 505));
	if(input_keydown(&game->input, KEY_DARROW) || input_keydown(&game->input, KEY_S))
		game->title.state = SELECT_QUIT;
	if(input_keydown(&game->input, KEY_UARROW) || input_keydown(&game->input, KEY_W))
		game->title.state = SELECT_START;
	if(input_keydown(&game->input, KEY_ENTER))
		game->title.state = OPTIONS;
}

void	title_show_select_start(t_game *game)
{
	game->title.anim_forward = 0;
	texture_blit(game->textures[TEX_TITLE_SPACE_BACK], game->rt0, v2new(0, 0));
	texture_blit(game->textures[TEX_TITLE_START_1], game->rt0, v2new(295, 105));
	texture_blit(game->textures[TEX_TITLE_OPTIONS_0], game->rt0, v2new(295, 305));
	texture_blit(game->textures[TEX_TITLE_QUIT_0], game->rt0, v2new(295, 505));
	if(input_keydown(&game->input, KEY_DARROW) || input_keydown(&game->input, KEY_S))
		game->title.state = SELECT_OPTIONS;
	if(input_keydown(&game->input, KEY_UARROW) || input_keydown(&game->input, KEY_W))
		game->title.state = SELECT_QUIT;
	if(input_keydown(&game->input, KEY_ENTER))
		game->title.state = LOAD_MAP;
}

void	title_animations(t_game *game)
{
	if (game->fpsc % 35 == 0)
	{
		game->fpsc = 0;
		if (game->title.anim_forward)
		{
			game->title.anim_frame++;
			if (game->title.anim_frame > TEX_TITLE_ENTER_06)
			{
				game->title.anim_frame = TEX_TITLE_ENTER_06 - 1;
				game->title.anim_forward = 0;
			}
		}
		else
		{
			game->title.anim_frame--;
			if (game->title.anim_frame < TEX_TITLE_ENTER_00)
			{
				game->title.anim_frame = TEX_TITLE_ENTER_00 + 1;
				game->title.anim_forward = 1;
			}
		}
	}
	texture_blit(game->textures[TEX_TITLE_ENTER_06], game->rt0, v2new(295, 705));
	texture_blit(game->textures[game->title.anim_frame], game->rt0, v2new(300, 700));
}

void	title_show_title(t_game *game)
{
	texture_blit(game->textures[TEX_TITLE_BACKDROP], game->rt0, v2new(0, 0));
	title_animations(game);
	if(input_keyheld(&game->input, KEY_ENTER))
	{
		game->title.state = SELECT_START;
	}
}

void	game_screen_states(t_game *game)
{
	if (game->title.state == RUNNING_GAME)
		game_update(game);
	else
	{
		control_process(game);
		if (game->title.state == TITLE)
			title_show_title(game);
		else if (game->title.state == SELECT_START)
			title_show_select_start(game);
		else if (game->title.state == LOAD_MAP)
			title_show_load_map(game);
		else if (game->title.state == SELECT_OPTIONS)
			title_show_select_options(game);
		else if (game->title.state == OPTIONS)
			title_show_options(game);
		else if (game->title.state == SELECT_QUIT)
			title_show_select_quit(game);
		else if (game->title.state == LOAD_AND_RUN)
			title_load_and_run(game);
		else if (game->title.state == END_SCREEN)
			title_end_screen(game);
		else if (game->title.state == BACK_TO_TITLE)
			title_back_to_title(game);
		texture_draw(game->app, game->rt0, v2new(0, 0));
	}
}


/*
void	render_title(t_game *game)
{
//	control_process(game);
	game_screen_state(game);


//	texture_draw(game->app, game->rt0, v2new(0, 0));
	if (game->title.state == LOAD_MAP)
		title_display_maps(game);
//	input_process(&game->input);
//	game->fpsc++;//ill use this to help load textures
}
*/
void	title_imgs_load(t_game *game)
{
	game->textures[TEX_TITLE_BACKDROP] = texture_load(game->app.mlx, "assets/menu/backdrop.xpm");
	game->textures[TEX_TITLE_ENTER_00] = texture_load(game->app.mlx, "assets/menu/enter_00.xpm");
	game->textures[TEX_TITLE_ENTER_01] = texture_load(game->app.mlx, "assets/menu/enter_01.xpm");
	game->textures[TEX_TITLE_ENTER_02] = texture_load(game->app.mlx, "assets/menu/enter_02.xpm");
	game->textures[TEX_TITLE_ENTER_03] = texture_load(game->app.mlx, "assets/menu/enter_03.xpm");
	game->textures[TEX_TITLE_ENTER_04] = texture_load(game->app.mlx, "assets/menu/enter_04.xpm");
	game->textures[TEX_TITLE_ENTER_05] = texture_load(game->app.mlx, "assets/menu/enter_05.xpm");
	game->textures[TEX_TITLE_ENTER_06] = texture_load(game->app.mlx, "assets/menu/enter_06.xpm");
	game->textures[TEX_TITLE_LOADMAP] = texture_load(game->app.mlx, "assets/menu/loadmap.xpm");
	game->textures[TEX_TITLE_OPTIONS_0] = texture_load(game->app.mlx, "assets/menu/options_0.xpm");
	game->textures[TEX_TITLE_OPTIONS_1] = texture_load(game->app.mlx, "assets/menu/options_1.xpm");
	game->textures[TEX_TITLE_QUIT_0] = texture_load(game->app.mlx, "assets/menu/quit_0.xpm");
	game->textures[TEX_TITLE_QUIT_1] = texture_load(game->app.mlx, "assets/menu/quit_1.xpm");
	game->textures[TEX_TITLE_SPACE_BACK] = texture_load(game->app.mlx, "assets/menu/space_back.xpm");
	game->textures[TEX_TITLE_START_0] = texture_load(game->app.mlx, "assets/menu/start_0.xpm");
	game->textures[TEX_TITLE_START_1] = texture_load(game->app.mlx, "assets/menu/start_1.xpm");
}

void	load_map_str(t_game *game)
{
	DIR		*dir;
	struct dirent	*ent;
	char		*folder_path;
	

	folder_path = "./maps/";
	if ((dir = opendir(folder_path)) != NULL)
	{
		while ((ent = readdir(dir)) != NULL)
		{
			if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
				continue;
			ft_strcpy(game->title.map_str[game->title.map_str_amount++], ent->d_name);
		}
		closedir(dir);
	}
	else
		printf("Error\n failed to opening map directory\n");
}

void	title_variable_assign(t_game *game)
{
	game->title.anim_frame = 0;
	game->title.anim_forward = 0;
	game->title.map_str_amount = 0;

	load_map_str(game);
}






void	title_screen(t_game *game)
{
	//load tite textures and set title state and init variables
	title_imgs_load(game);
	//set up window
//	game->rt0 = texture_create(game->app.mlx, SCR_WIDTH, SCR_HEIGHT);
//	game->app.win = mlx_new_window(game->app.mlx, SCR_WIDTH, SCR_HEIGHT, "cub3d");
	title_variable_assign(game);

	//assign variables
	//input setup
//	input_setup(game->app.mlx, game->app.win, &game->input);
	//title screen loop
//	mlx_loop_hook(game->app.mlx, (void *)render_title, game);
}
