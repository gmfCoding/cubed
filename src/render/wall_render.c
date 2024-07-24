/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 01:41:22 by clovell           #+#    #+#             */
/*   Updated: 2024/03/27 00:08:42 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* *************** */
/*  prior: loop.c: */
/* *************** */
#include <pthread.h>
#include "internal/wall.h"
#include "state.h"
#include "vector2.h"
#include "vector2i.h"
#include "ray.h"

#define RENDERTHREAD_COUNT 1

typedef struct s_wallthread
{
	t_game *game;
	int start;
	int end;
} t_wallthread;

void *render_wall_threaded(void *t_wallthread_arg)
{
	t_wallthread *const thread = t_wallthread_arg;
	t_game *const	game = thread->game;
	t_vert			vert;

	vert.x = thread->start;
	while (++vert.x < thread->end)
	{
		game->ray = vert.x;
		vert.camera_x = 2 * vert.x / (double)R_WIDTH - 1;
		vert.dir = v2add(game->player.dir, \
		v2muls(game->player.plane, vert.camera_x));
		vert.ray = raycast(game, game->player.pos, vert.dir, RAY_MASK_ALL);
		if (vert.x == R_HEIGHT / 2)
			game->half = vert.ray;
		render_vertical(game, vert);
	}
	return NULL;
}

void *render_wall_threaded(void *thread);

void	render_wall(t_game *game)
{
	pthread_t threads[RENDERTHREAD_COUNT];
	t_wallthread contexts[RENDERTHREAD_COUNT];
	int row_width = R_WIDTH / RENDERTHREAD_COUNT;
	int i;

	i = -1;
	while (++i < RENDERTHREAD_COUNT)
	{
			contexts[i] = (t_wallthread){.game = game, .start = (i * row_width) + 2, .end = (i + 1) * row_width };
			pthread_create(&threads[i], NULL, render_wall_threaded, &contexts[i]);
	}
	i = -1;
	while (++i < RENDERTHREAD_COUNT)
		pthread_join(threads[i], NULL);
}
