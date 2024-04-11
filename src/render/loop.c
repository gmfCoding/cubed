/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 19:42:59 by clovell           #+#    #+#             */
/*   Updated: 2024/04/08 00:59:35 by clovell          ###   ########.fr       */
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
#include "vectorconv.h"
#include "render.h"
#include "libft.h"
#include "internal/wall.h"
#include "cubed.h"

void	measure_frame_rate(t_app app)
{
	static int64_t	timeprev = 0;
	static char		*fps = NULL;
	// TODO: Remove from mandatory
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
		ft_strfmt("type:(%d)", map_get_tile(&game->world->map, game->half.depths[0].x, game->half.depths[0].y).type),
		ft_strfmt("vis:(%d)", map_get_tile(&game->world->map, game->half.depths[0].x, game->half.depths[0].y).vis),
	};
	int					i;
	if (input_keydown( &game->input, KEY_H))
	{
		printf("Pausing!");
	}
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
	event_player(game, false);
	control_process(game);
	if (game->events_on == true)
		event_interact(game);
	mmap_input(game, &game->mmap);
}

#define D_SCALE ((float)SCR_WIDTH / (float)game->world->map.width)


void draw_debug_view_world_state(t_game *game)
{
	const t_texture    tex = texture_get_debug_view(game, 2);

	t_sprite        *curr;
	int             i;

	texture_clear(tex, 0 | R_ALPHA);
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
			else if (tile->type == DOOR)
				texture_draw_line(tex, v2muls(v2new(x + 0.4, y+ 0.4), D_SCALE), v2muls(v2new(x + 0.4, y + 0.5), D_SCALE), R_RED | R_GREEN | R_ALPHA);
			if (tile->type == EMPTY)
			{
				texture_draw_line(tex, v2muls(v2new(x, y), D_SCALE), v2muls(v2new(x + 1, y + 1), D_SCALE), 0xFFAA77 | R_ALPHA);
			}
			if (tile->vis == 0)
				texture_draw_line(tex, v2muls(v2new(x + 0.1, y+ 0.1), D_SCALE), v2muls(v2new(x + 0.1, y + 0.2), D_SCALE), R_RED | R_ALPHA);
			if (tile->vis == 1)
				texture_draw_line(tex, v2muls(v2new(x + 0.1, y+ 0.1), D_SCALE), v2muls(v2new(x + 0.1, y + 0.2), D_SCALE), R_BLUE | R_ALPHA);
			if (tile->vis == -1)
				texture_draw_line(tex, v2muls(v2new(x + 0.1, y + 0.1), D_SCALE), v2muls(v2new(x + 0.1, y + 0.2), D_SCALE), R_GREEN | R_ALPHA);
			if (tile->sp_count > 0)
			{
				texture_draw_line(tex, v2muls(v2new(x, y), D_SCALE), v2muls(v2new(x + 1, y + 1), D_SCALE), 0x00DDDDDD | R_ALPHA);
			}
		}
	}
	i = -1;
	while (++i < game->world->sp_amount)
	{
		curr = &game->world->sprite[i];
		texture_draw_line(tex, v2muls(curr->s1, D_SCALE), v2muls(curr->s2, D_SCALE), R_RED | R_ALPHA);
		texture_draw_line(tex, v2muls(curr->vs1, D_SCALE), v2muls(curr->vs2, D_SCALE), R_GREEN | R_ALPHA);
		texture_draw_circle(&tex, v2tov2i(v2muls(curr->pos, D_SCALE)), 2, 0xFFFF33 | R_ALPHA);
		texture_draw_circle(&tex, v2tov2i(v2muls(curr->vs1, D_SCALE)), 2, 0x55FFFF | R_ALPHA);
		texture_draw_circle(&tex, v2tov2i(v2muls(curr->vs2, D_SCALE)), 2, 0xFF13FF | R_ALPHA);
	}
	t_list *ent_next = game->world->entities;
	while (ent_next != NULL)
	{
		t_entity *entity = ent_next->content;
		texture_draw_circle(&tex, v2tov2i(v2muls(entity->pos, D_SCALE)), 2, R_GREEN | R_ALPHA);
		ent_next = ent_next->next;
	}
	if (game->world->enemy)
	{
		t_vec2 *path;
		t_vec2 prev;
		path = game->world->enemy->path;
		for (size_t i = 0; path && (int)path->x != -1 && (int)path->y != -1; i++)
		{
			if (i > 0)
				texture_draw_line(tex, v2muls(*path, D_SCALE), v2muls(prev, D_SCALE), R_GREEN | R_ALPHA);
			prev = *path;
			path++;
		}
	}

	static float dir = 0;
	if (input_keyheld(&game->input, KEY_J))
		dir -= 0.01;
	if (input_keyheld(&game->input, KEY_K))
		dir += 0.01;
	if (game->input.mouse.x > 0 && game->input.mouse.x < SCR_WIDTH)
	{
		if (game->input.mouse.y > 0 && game->input.mouse.y < SCR_HEIGHT)
		{
			t_vec2 start = v2new(game->input.mousef.x / D_SCALE, game->input.mousef.y / D_SCALE);
			t_vec2 vdir = v2new(cos(dir), sin(dir));
			t_rayinfo info = raycast(game, start, vdir, RAY_MASK_WALL);
			t_vec2 hit = ray_gethit(&info, 0);
			hit = v2muls(hit, D_SCALE);
			texture_draw_line(tex, game->input.mousef, hit, R_GREEN | R_ALPHA);
		}
	}
	//texture_clear(tex, R_RED | R_ALPHA);
}

void	render(t_game *game)
{
//	const t_texture    tex = texture_get_debug_view(game, 2);
//	texture_clear(tex, 0 | R_ALPHA);
	//mlx_mouse_hide(game->app.mlx, game->app.win);
	entity_update(game);
	enemy_routine(game, game->world->enemy);
	sprite_order_distance(game->player.pos, game->world->sprite, game->world->indices, game->world->sp_amount);
	sprite_update_all(game->world);
	player_loop(game);
	render_skybox(game->player.dir, game->textures[TEX_SKYBOX], game->rt1);
	render_floor(game);
	render_wall(game);
	texture_blit_s(game->rt1, game->rt0, v2new(0, 0), R_SCALE);
	mmap_draw(game);
	if (game->tasks[0] && game->tasks[0]->show)
		task_orbit_render(game, game->tasks[0]);
	event_display_ui(game);
	texture_draw(game->app, game->rt0, v2new(0, 0));
	draw_debug_info(game);

	static bool show_debug = false;
	if (input_keydown(&game->input, KEY_TILDA))
	{
		show_debug = !show_debug;
		if (!show_debug && game->views[2].win)
		{
			texture_destroy(game->app.mlx, &game->views[2].rt, NULL, false);
			mlx_destroy_window(game->app.mlx, game->views[2].win);
		}
	}
	if (show_debug)
	{
		draw_debug_view_world_state(game);
		texture_draw_debug_view(game, 2);
	}
	five_lights(game);
	input_process(&game->input);
	game->fpsc++;
}
