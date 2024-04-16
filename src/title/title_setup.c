#include "texture.h"
#include "state.h"
#include "destroy.h"

#include <dirent.h>

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

#ifndef BONUS
void	load_map_str(t_game *game)
{
	ft_strcpy(game->title.map_str[0], "./maps/map1.cub");
	ft_strcpy(game->title.map_str[1], "./maps/map1.cub");
	ft_strcpy(game->title.map_str[2], "./maps/map1.cub");
	ft_strcpy(game->title.map_str[3], "./maps/map1.cub");
	ft_strcpy(game->title.map_str[4], "./maps/map1.cub");
	ft_strcpy(game->title.map_str[5], "./maps/map1.cub");
	ft_strcpy(game->title.map_str[6], "./maps/map1.cub");
}
#endif

#ifdef BONUS
//using forbidden functions here
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
			if (ft_strcmp(ent->d_name, ".") == 0 || ft_strcmp(ent->d_name, "..") == 0)
				continue ;
			ft_strcpy(game->title.map_str[game->title.map_str_amount++], ent->d_name);
		}
		closedir(dir);
	}
	else
		printf("Error\n failed to opening map directory\n");
}
#endif

//TODO change name to title_Setup
void	title_setup_screens(t_game *game)
{
	title_imgs_load(game);
	game->title.anim_frame = 0;
	game->title.anim_forward = 0;
	game->title.map_str_amount = 0;
	load_map_str(game);
}
