/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 21:31:00 by clovell           #+#    #+#             */
/*   Updated: 2024/05/06 22:12:09 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <math.h>
#include "mlx.h"
#include "state.h"
#include "player.h"
#include "destroy.h"
#include "clmath.h"
#include "tasks/task_orbit.h"

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
