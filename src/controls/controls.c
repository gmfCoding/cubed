#include <math.h>
#include "mlx.h"
#include "cubed.h"
#include "player.h"
#include "destroy.h"
#include <math.h>

static void	rotate_player(t_player *player, double angle)
{
	player->dir.x = cos(angle);
	player->dir.y = sin(angle);
	player->plane.x = -player->dir.y / 2.0;
	player->plane.y = player->dir.x / 2.0;
}

static void	move_player(t_map *map, t_player *pl, t_vec2 dir)
{
	t_tile *horz;
	t_tile *vert;
	const t_vec2 vel = v2muls(dir, pl->moveSpeed);

	horz = map_get_tile_ref(map, (int)(pl->pos.x + vel.x), (int)pl->pos.y);
	vert = map_get_tile_ref(map, (int)pl->pos.x, (int)(pl->pos.y + vel.y));
	if (horz->vis == -1)
		pl->pos.x += vel.x;
	if (vert->vis == -1)
		pl->pos.y += vel.y;
}

void	control_player_process(t_game *game)
{
	t_player *const		pl = &game->player;
	t_inputctx *const 	i = &game->input;

	if (input_keyheld(i, KEY_W))
		move_player(&game->world->map, pl, pl->dir);
	if (input_keyheld(i, KEY_S))
		move_player(&game->world->map, pl, v2inv(pl->dir));
	if (input_keyheld(i, KEY_A))
		move_player(&game->world->map, pl, v2new(pl->dir.y, -pl->dir.x));
	if (input_keyheld(i, KEY_D))
		move_player(&game->world->map, pl, v2new(-pl->dir.y, pl->dir.x));
	if (input_keyheld(i, KEY_RARROW) || input_keyheld(i, KEY_LARROW))
	{
		if (input_keyheld(i, KEY_RARROW))
			pl->key_angle -= pl->rotSpeed;
		if (input_keyheld(i, KEY_LARROW))
			pl->key_angle += pl->rotSpeed;
	}
	else
		pl->angle = ((double)i->mouse.x / SCR_WIDTH) * 3.14159 * 2; // TODO: Use M_TAU
	rotate_player(pl, ((pl->angle * 2) - pl->key_angle) );
}

void	control_core_process(t_game *game)
{
	if (input_keyheld(&game->input, KEY_ESC))
		game_destroy(game);
}

// Doesn't work on wslg
// void	mouse_bounds_check(t_app *app, t_inputctx *ctx)
// {
// 	printf("%d\n", ctx->mouse.x);
// 	if (ctx->mouse.x < 2 || ctx->mouse.x >= SCR_WIDTH - 2)
// 		mlx_mouse_move(app->mlx, app->win, SCR_WIDTH / 2, ctx->mouse.y);
// 	if (ctx->mouse.y < 2 || ctx->mouse.y >= SCR_WIDTH - 2)
// 		mlx_mouse_move(app->mlx, app->win, ctx->mouse.x, SCR_HEIGHT / 2);
// 	mlx_mouse_move(app->mlx, app->win, 10, 10);
// }

void	control_process(t_game *game)
{
	//mouse_bounds_check(&game->app, &game->input);
	control_core_process(game);
	control_player_process(game);
}