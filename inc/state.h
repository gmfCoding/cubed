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
#include "input.h"
#include "texture.h"
#include "ray.h"

typedef struct s_game t_game;

#define MAX_DEBUG_VIEWS 10
typedef struct s_debug_texture t_debug_texture;
struct s_debug_texture
{
	void *win;
	t_texture rt;
};

typedef struct s_player t_player;

struct s_player
{
	t_vec2 pos;
	t_vec2 dir;
	t_vec2 plane;

	double moveSpeed;
	double rotSpeed;
};

typedef struct s_inputctx t_inputctx;

typedef struct s_app t_app;
struct s_app
{
	void *mlx;
	void *win;
};

typedef struct s_world t_world;

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

	t_inputctx		input;
	t_rayinfo		half;
};

void texture_debug_view_blit(t_game *game, int view, t_texture tex, t_vec2 pos);
void texture_draw_debug_view(t_game *game, int view);
t_texture texture_get_debug_view(t_game *game, int view);

#endif
