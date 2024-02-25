/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 19:42:59 by clovell           #+#    #+#             */
/*   Updated: 2024/02/26 01:50:33 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <mlx.h>

#include "mini_map.h"
#include "input.h"
#include "cubed.h"
#include "texture.h"
#include "vector2i.h"

#include "libft.h"

void	measure_frame_rate(t_app app)
{
	static int64_t	timeprev = 0;
	static char		*fps = NULL;

	fps = ft_strfmt("fps:%d", \
	(int)(1.0 / ((time_get_ms() - timeprev) / 1000.0)));
	mlx_string_put(app.mlx, app.win, 0, 10, 0x00FF00, fps);
	free(fps);
	// AUTO EXIT AFTER 4 SECONDS (used for GMON)
	// static int64_t time;
	// if (timeprev != 0)
	// 	time += time_get_ms() - timeprev;
	// if (time > 4 * 1000)
	// 	exit(0);
	timeprev = time_get_ms();
}

void	draw_debug_info(t_game *game)
{
	t_player *const	player = &game->player;
	static int64_t	timeprev = 0;
	const char		*debugstr[] = {
		ft_strfmt("fps:%d", (int)(1.0 / ((time_get_ms() - timeprev) / 1000.0))),
		ft_strfmt("pos:(%f,%f)", (double)player->pos.x, (double)player->pos.y),
		ft_strfmt("dir:(%f,%f)", (double)player->dir.x, (double)player->dir.y),
		ft_strfmt("plane:(%f,%f)", \
		(double)game->player.plane.x, (double)game->player.plane.y),
		ft_strfmt("hits:(%d)", game->half.hits),
	};
	int				i;

	i = -1;
	while (++i < sizeof(debugstr) / sizeof(*debugstr))
	{
		mlx_string_put(game->app.mlx, game->app.win, 0, \
			i * 12 + 12, 0xFFFFFF, debugstr[i]);
		free(debugstr[i]);
	}
	timeprev = time_get_ms();
}

// t_vec2	screen_to_map(t_vec2 mouse)
// {
// 	return ((t_vec2){mouse.x / R_WIDTH * MAP_WIDTH, \
// 	mouse.y / R_HEIGHT * MAP_HEIGHT});
// }

// t_vec2	map_to_screen(t_vec2 map)
// {
// 	return ((t_vec2){map.x * R_WIDTH / (float)MAP_WIDTH, \
// 	map.y * R_HEIGHT / (float)MAP_HEIGHT});
// }

void player_loop(t_game *game)
{
	t_player *const player = &game->player;
	double oldDirX;
	double oldPlaneX;

	oldDirX = player->dir.x;
	oldPlaneX = player->plane.x;
	event_player(game);
	control_process(game);
	if (game->events_on == true)
		event_interact(game);
	mmap_input(game, &game->mmap);
}

void	render(t_game *game)
{

	player_loop(game);
	input_process(&game->input);
	render_floor(game);
	render_wall(game);
	texture_blit_s(game->rt1, game->rt0, v2new(0, 0), R_SCALE);
	mmap_draw(game);
	texture_draw(game, game->rt0, v2new(0, 0));
	event_display_ui(game);
	draw_debug_info(game);
	game->fpsc++;
}
