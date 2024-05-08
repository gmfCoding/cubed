/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 21:31:00 by clovell           #+#    #+#             */
/*   Updated: 2024/05/08 17:01:16 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <math.h>
#include "mlx.h"
#include "state.h"
#include "player.h"
#include "destroy.h"
#include "clmath.h"
#include "tasks/task_orbit.h"

double	window_angle(int x)
{
	return (((double)x / SCR_WIDTH) * M_TAU);
}

// // TODO: Debug remove.
// if (input_keydown(&game->input, KEY_T))
// {
// 	task = task_find(game, "task_orbit");
// 	if (task)
// 		task->show = true;
// 	else
// 	{
// 		task = task_create_or_find(game, "task_orbit");
// 		task->show = true;
// 	}
// }

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

// Make sure we're facing the correct direction 
// no matter where the mouse cursor starts.
//mouse_bounds_check(&game->app, &game->input);
void	control_process(t_game *game)
{
	if (game->menu_reloaded)
	{
		mouse_get_pos(&game->app, &game->input.mouse.x, &game->input.mouse.y);
		game->player.angle_offset \
			+= window_angle(game->input.mouse.x) * MOUSE_SENSITIVITY;
	}
	control_core_process(game);
	game->mouse_angle = window_angle(game->input.mouse.x) * MOUSE_SENSITIVITY;
	if (can_move_player(game, &game->player))
		control_player_process(game);
}
