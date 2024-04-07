/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 21:31:00 by clovell           #+#    #+#             */
/*   Updated: 2024/04/08 01:26:12 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <math.h>
#include "mlx.h"
#include "state.h"
#include "player.h"
#include "destroy.h"
#include "clmath.h"
#include "tasks/task_orbit.h"

static double	window_angle(int x)
{
	return (((double)x / SCR_WIDTH) * M_TAU);
}

static void	rotate_player(t_player *player, double angle)
{
	player->dir.x = cos(angle);
	player->dir.y = sin(angle);
	player->plane.x = -player->dir.y / 2.0;
	player->plane.y = player->dir.x / 2.0;
	player->plane_start = v2add(player->plane, player->pos);
	player->plane_end = v2add(v2rev(player->plane), player->pos);
}

static void	move_player(t_map *map, t_player *pl, t_vec2 dir)
{
	const t_vec2	vel = v2muls(dir, pl->moveSpeed);
	t_tile			*horz;
	t_tile			*vert;

	horz = map_get_tile_ref(map, (int)(pl->pos.x + vel.x), (int)pl->pos.y);
	vert = map_get_tile_ref(map, (int)pl->pos.x, (int)(pl->pos.y + vel.y));
	if (horz->vis == -1)
		pl->pos.x += vel.x;
	if (vert->vis == -1)
		pl->pos.y += vel.y;
}

int	can_move_player(t_game *game, t_player *pl, t_inputctx *i)
{
	static double	store;

	if (game->player.state == START_TASK)
	{
		// Trigger once, start
		//printf("enter angle: %f - %f, %f\n", game->mouse_angle, game->angle_offset, (game->mouse_angle) - game->angle_offset);
		// Store the angle of when we enter the task.
		store = game->mouse_angle;
		game->player.state = CANT_MOVE;
	}
	if (game->player.state == DONE_TASK)
	{
		// Trigger once, end
		//printf("task %f\n", game->angle_offset);
		// Subtract the change in angle since we started the task.
		game->player.angle_offset += game->mouse_angle - store;
		//printf("leave angle: %f - %f, %f\n", game->mouse_angle, game->angle_offset, (game->mouse_angle) - game->angle_offset);
		//game->angle_offset -= (game->mouse_angle - store);
		game->player.state = CAN_MOVE;
	}
	if (game->player.state == CANT_MOVE)
	{
		// Trigger every frame
		return (0) ;
	}
	// Resume normal controls
	return (1);
}

void	control_player_process(t_game *game)
{
	t_player *const		pl = &game->player;
	t_inputctx *const	i = &game->input;
	game->mouse_angle = window_angle(i->mouse.x);
	if (!(can_move_player(game, pl, i)))
		return ;
	if (input_keyheld(i, KEY_W))
		move_player(&game->world->map, pl, pl->dir);
	if (input_keyheld(i, KEY_S))
		move_player(&game->world->map, pl, v2rev(pl->dir));
	if (input_keyheld(i, KEY_A))
		move_player(&game->world->map, pl, v2new(pl->dir.y, -pl->dir.x));
	if (input_keyheld(i, KEY_D))
		move_player(&game->world->map, pl, v2new(-pl->dir.y, pl->dir.x));
	if (input_keyheld(i, KEY_RARROW) || input_keyheld(i, KEY_LARROW))
	{
		if (input_keyheld(i, KEY_RARROW))
			game->player.angle_offset -= pl->rotSpeed;
		if (input_keyheld(i, KEY_LARROW))
			game->player.angle_offset += pl->rotSpeed;
	}
	pl->angle = (game->mouse_angle * MOUSE_SENSITIVITY) - game->player.angle_offset;
	rotate_player(pl, pl->angle);
}

void	control_core_process(t_game *game)
{
	if (input_keyheld(&game->input, KEY_ESC))
		game_destroy(game);
	if(input_keydown(&game->input, KEY_T))
	{
		game->tasks[0] = malloc(sizeof(t_task_orbit));
		*game->tasks[0] = *g_tasks[0];
		task_orbit_setup(game, game->tasks[0]);
		game->tasks[0]->show = true;
	}
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
	static bool first_time = false;
	
	if (!first_time)
	{
		first_time = true;
		mlx_mouse_get_pos(game->app.mlx, game->app.win, &game->input.mouse.x, &game->input.mouse.y);
		// Make sure we're facing the correct direction no matter where the mouse cursor starts.
		game->player.angle_offset += window_angle(game->input.mouse.x) * MOUSE_SENSITIVITY;
	}
	//mouse_bounds_check(&game->app, &game->input);
	control_core_process(game);
	control_player_process(game);
}
