#include "texture.h"
#include "state.h"














void generate_textures(t_game *game)
{
	enemy_load_directory(game, "assets/enemy_sprites/");

	game->textures[TEX_WALL] = texture_load(game->app.mlx, "assets/wall.xpm");
	game->textures[TEX_WALLN] = game->textures[TEX_WALL];
	game->textures[TEX_WALLE] = texture_load(game->app.mlx, "assets/debug.xpm");
	game->textures[TEX_WALLS] = game->textures[TEX_WALL];
	game->textures[TEX_WALLW] = game->textures[TEX_WALL];
	game->textures[TEX_WINDOW] = texture_load(game->app.mlx, "assets/window.xpm");
	game->textures[TEX_DOOR] = game->textures[TEX_WINDOW];
	game->textures[TEX_FLOOR] = texture_load(game->app.mlx, "assets/metal_walkway_acg.xpm");
	game->textures[TEX_CEILING] = game->textures[TEX_FLOOR];
	game->textures[TEX_SKYBOX] = texture_load(game->app.mlx, "assets/skybox.xpm");
	game->textures[TEX_FIVE_LIGHTS] = texture_load(game->app.mlx, "assets/five_lights_wall.xpm");

	game->textures[TEX_UI_CONTROLS] = texture_load(game->app.mlx, "assets/ui/controls.xpm");
	game->textures[TEX_UI_INTERACT_BRIGHT] = texture_load(game->app.mlx, "assets/ui/interact_bright.xpm");
	game->textures[TEX_UI_INTERACT_DUL] = texture_load(game->app.mlx, "assets/ui/interact_dal.xpm");
	game->textures[TEX_UI_DOOR_LOCKED] = texture_load(game->app.mlx, "assets/ui/promt_door_locked.xpm");
	game->textures[TEX_UI_TASK_INACTIVE] = texture_load(game->app.mlx, "assets/ui/inactive_task.xpm");

}
