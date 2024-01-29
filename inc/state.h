/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 19:43:57 by clovell           #+#    #+#             */
/*   Updated: 2023/12/13 17:35:38 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATE_H
# define STATE_H

#include "player.h"
#include "input.h"
#include "texture.h"
#include "ray.h"
#include "mini_map.h"

//typedef struct s_entity_2 t_entity_2;
typedef struct s_game t_game;

#define MAX_DEBUG_VIEWS 10
typedef struct s_debug_texture t_debug_texture;
struct s_debug_texture
{
	void *win;
	t_texture rt;
};

typedef struct s_inputctx t_inputctx;
typedef struct s_app t_app;
struct s_app
{
	void *mlx;
	void *win;
};

typedef struct s_world t_world;
typedef struct s_mmap t_mmap;


struct s_game
{
	t_app			app;
	t_texture		rt0;
	t_texture		rt1;
	t_texture		rt2;

	t_vec2			mouse;
	t_vec2			pos;

	t_debug_texture	views[MAX_DEBUG_VIEWS];
	int				view_count;

	t_player		player;
	t_texture		textures[8];
	t_world			*world;
	t_mmap			mmap;
	t_entity_2		*events_active[9];
	bool			events_on;
	bool			display_ui;
	t_inputctx		input;
	t_rayinfo		half;
	unsigned int		fpsc;
};

void texture_debug_view_blit(t_game *game, int view, t_texture tex, t_vec2 pos);
void texture_draw_debug_view(t_game *game, int view);
t_texture texture_get_debug_view(t_game *game, int view);

#endif
