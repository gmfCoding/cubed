/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 19:42:59 by clovell           #+#    #+#             */
/*   Updated: 2024/03/11 21:33:27 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <mlx.h>

#include "mini_map.h"
#include "input.h"
#include "state.h"
#include "texture.h"
#include "vector2i.h"

#include "libft.h"
#include "internal/wall.h"

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
	t_player *const		player = &game->player;
	static int64_t		timeprev = 0;
	char		*const	debugstr[] = {
		ft_strfmt("fps:%d", (int)(1.0 / ((time_get_ms() - timeprev) / 1000.0))),
		ft_strfmt("pos:(%f,%f)", (double)player->pos.x, (double)player->pos.y),
		ft_strfmt("dir:(%f,%f)", (double)player->dir.x, (double)player->dir.y),
		ft_strfmt("plane:(%f,%f)", \
		(double)game->player.plane.x, (double)game->player.plane.y),
		ft_strfmt("hits:(%d)", game->half.hits),
	};
	int					i;

	i = -1;
	while (++i < (int)(sizeof(debugstr) / sizeof(*debugstr)))
	{
		mlx_string_put(game->app.mlx, game->app.win, 0, \
			i * 12 + 12, 0xFFFFFF, debugstr[i]);
		free(debugstr[i]);
	}
	timeprev = time_get_ms();
}

void	player_loop(t_game *game)
{
	event_player(game);
	control_process(game);
	if (game->events_on == true)
		event_interact(game);
	mmap_input(game, &game->mmap);
}

void	update_segments(t_game *game)
{
	t_sprite	*curr;
	t_vec2		dir;
	t_vecd		temp;
	int i;

	i = -1;
	while (++i < game->world->sp_amount)
	{
		curr = &game->world->sprite[i];
		//dir = v2norm(v2sub(game->player.pos, curr->pos));
		dir = game->player.dir;
		temp = dir.x;
		dir.x = dir.y;
		dir.y = -temp;
		curr->s1 = v2add(curr->pos, v2muls(dir, 0.5));
		curr->s2 = v2add(curr->pos, v2muls(dir, -0.5));
	//	curr->s1 = v2add(curr->pos, v2muls(dir, 1.25));
	//	curr->s2 = v2add(curr->pos, v2muls(dir, -1.25));
	}
}
/*
#define D_SCALE 25


void draw_debug_view_world_state(t_game *game)
{
    const t_texture    tex = texture_get_debug_view(game, 2);

    t_sprite        *curr;
    int             i;
    i = -1;

    while (++i < game->world->sp_amount)
    {
        curr = &game->world->sprite[i];
        texture_draw_line(tex, v2muls(curr->s1, D_SCALE), v2muls(curr->s2, D_SCALE), R_RED | R_ALPHA);
    }
    texture_draw_line(tex, v2muls(game->player.pos, D_SCALE), v2muls(v2add(game->player.pos, game->player.dir), D_SCALE), R_BLUE | R_ALPHA);
    texture_draw_line(tex, v2muls(game->player.pos, D_SCALE), v2muls(v2add(game->player.pos, game->player.plane), D_SCALE), R_BLUE | R_ALPHA);
    pixel_set(tex, game->player.pos.x * D_SCALE, game->player.pos.y * D_SCALE, R_GREEN | R_ALPHA);

    for (int y = 0; y < game->world->map.height; y++)
    {
        for (int x = 0; x < game->world->map.width; x++)
        {
            texture_draw_line(tex, v2muls(v2new(x, y), D_SCALE), v2muls(v2new(x + 1, y), D_SCALE), 0x00222222 | R_ALPHA);
            texture_draw_line(tex, v2muls(v2new(x, y), D_SCALE), v2muls(v2new(x, y + 1), D_SCALE), 0x00222222 | R_ALPHA);
        }
    }
    for (int y = 0; y < game->world->map.height; y++)
    {
        for (int x = 0; x < game->world->map.width; x++)
        {
            t_tile *tile = map_get_tile_ref(&game->world->map, x, y); 
            if (tile->type == WALL)
            {
                texture_draw_line(tex, v2muls(v2new(x, y), D_SCALE), v2muls(v2new(x + 1, y), D_SCALE), 0x00AAAAAA | R_ALPHA);
                texture_draw_line(tex, v2muls(v2new(x, y), D_SCALE), v2muls(v2new(x, y + 1), D_SCALE), 0x00AAAAAA | R_ALPHA);
                texture_draw_line(tex, v2muls(v2new(x + 1, y), D_SCALE), v2muls(v2new(x + 1, y + 1), D_SCALE), 0x00AAAAAA | R_ALPHA);
                texture_draw_line(tex, v2muls(v2new(x + 1, y + 1), D_SCALE), v2muls(v2new(x, y + 1), D_SCALE), 0x00AAAAAA | R_ALPHA);
            }
            if (tile->sp_count > 0)
            {
                texture_draw_line(tex, v2muls(v2new(x, y), D_SCALE), v2muls(v2new(x + 1, y + 1), D_SCALE), 0x00DDDDDD | R_ALPHA);
            }
        }
    }
  //  texture_clear(tex, R_RED | R_ALPHA);
}
*/

void	render(t_game *game)
{
	int x;
//	const t_texture    tex = texture_get_debug_view(game, 2);
//	texture_clear(tex, 0 | R_ALPHA);
	//mlx_mouse_hide(game->app.mlx, game->app.win);
	enemy_routine(game, &game->world->enemy);
	update_segments(game);
	player_loop(game);

	x = v2x2ang(game->player.dir) / 6.28 * 3840;
	texture_blit(game->textures[TEX_SKYBOX], game->rt1, v2new(-x, 0));
	render_floor(game);
	render_wall(game);
	texture_blit_s(game->rt1, game->rt0, v2new(0, 0), R_SCALE);
	mmap_draw(game);
	if (game->tasks[0] && game->tasks[0]->show)
		task_orbit_render(game, game->tasks[0]);
	input_process(&game->input);
	texture_draw(game->app, game->rt0, v2new(0, 0));
	event_display_ui(game);
	draw_debug_info(game);
//	texture_draw_debug_view(game, 2);
	game->fpsc++;
}
