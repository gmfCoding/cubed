/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 21:31:00 by clovell           #+#    #+#             */
/*   Updated: 2024/05/03 21:56:52 by kmordaun         ###   ########.fr       */
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

void	player_step_sound(t_game *game)
{
	int					step_type;
	t_inputctx *const	i = &game->input;

	step_type = -1;
	if (input_keydown(i, KEY_W) || input_keydown(i, KEY_S) \
		|| input_keydown(i, KEY_A) || input_keydown(i, KEY_D))
	{
		step_type = SFX_PSTEP01 + (mrand(&game->rand) % 3);
		play_sound(game->app.sfx, step_type, PLAY);
	}
	if (input_keyheld(i, KEY_W) || input_keyheld(i, KEY_S) \
		|| input_keyheld(i, KEY_A) || input_keyheld(i, KEY_D))
	{
		if (game->fpsc % (int)35 * game->player.move_speed == 0)
		{
			step_type = SFX_PSTEP01 + (mrand(&game->rand) % 3);
			play_sound(game->app.sfx, step_type, PLAY);
		}
	}
}

static void	move_player(t_map *map, t_player *pl, t_vec2 dir)
{
	const t_vec2	vel = v2muls(dir, pl->move_speed);
	t_tile			*horz;
	t_tile			*vert;

	horz = map_get_tile_ref(map, (int)(pl->pos.x + vel.x), (int)pl->pos.y);
	vert = map_get_tile_ref(map, (int)pl->pos.x, (int)(pl->pos.y + vel.y));
	if (horz->vis == -1)
		pl->pos.x += vel.x;
	if (vert->vis == -1)
		pl->pos.y += vel.y;
}

int	can_move_player(t_game *game, t_player *pl)
{
	static double	store;

	if (pl->state == START_TASK)
	{
		store = game->mouse_angle;
		pl->state = CANT_MOVE;
	}
	if (pl->state == DONE_TASK)
	{
		pl->angle_offset += game->mouse_angle - store;
		pl->state = CAN_MOVE;
	}
	if (pl->state == CANT_MOVE)
		return (0);
	return (1);
}
/*
int	can_move_player(t_game *game, t_player *pl)
{
	static double	store;

	if (pl->state == START_TASK)
	{
		// Trigger once, start
		//printf("enter angle: %f - %f, %f\n", game->mouse_angle, \
		//game->angle_offset, (game->mouse_angle) - game->angle_offset);
		// Store the angle of when we enter the task.
		store = game->mouse_angle;
		pl->state = CANT_MOVE;
	}
	if (pl->state == DONE_TASK)
	{
		// Trigger once, end
		//printf("task %f\n", game->angle_offset);
		// Subtract the change in angle since we started the task.
		pl->angle_offset += game->mouse_angle - store;
		//printf("leave angle: %f - %f, %f\n", \
		//game->mouse_angle, game->angle_offset, \
		//(game->mouse_angle) - game->angle_offset);
		//game->angle_offset -= (game->mouse_angle - store);
		pl->state = CAN_MOVE;
	}
	if (pl->state == CANT_MOVE)
	{
		// Trigger every frame
		return (0) ;
	}
	// Resume normal controls
	return (1);
}
*/

void	control_player_process(t_game *game)
{
	t_player *const		pl = &game->player;
	t_inputctx *const	i = &game->input;

	game->mouse_angle = window_angle(i->mouse.x) * MOUSE_SENSITIVITY;
	if (!(can_move_player(game, pl)))
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
			game->player.angle_offset -= pl->rot_speed;
		if (input_keyheld(i, KEY_LARROW))
			game->player.angle_offset += pl->rot_speed;
	}
	player_step_sound(game);
	pl->angle = (game->mouse_angle) - game->player.angle_offset;
	rotate_player(pl, pl->angle);
}

// TODO: Debug remove.
void	control_core_process(t_game *game)
{
	t_task	*task;

	if (input_keyheld(&game->input, KEY_ESC))
		game_destroy(game);
	if (input_keydown(&game->input, KEY_T))
	{
		task = task_find(game, "task_orbit");
		if (task)
			task->show = true;
		else
		{
			task = task_create_or_find(game, "task_orbit");
			task->show = true;
		}
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

// Make sure we're facing the correct direction 
// no matter where the mouse cursor starts.
//mouse_bounds_check(&game->app, &game->input);
void	control_process(t_game *game)
{
	if (!game->mouse_first_time)
	{
		game->mouse_first_time = true;
		mouse_get_pos(&game->app, &game->input.mouse.x, &game->input.mouse.y);
		game->player.angle_offset \
			+= window_angle(game->input.mouse.x) * MOUSE_SENSITIVITY;
	}
	control_core_process(game);
	control_player_process(game);
}
