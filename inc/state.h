/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 19:43:57 by clovell           #+#    #+#             */
/*   Updated: 2024/03/11 21:12:22 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATE_H
# define STATE_H
# include "input.h"
# include "texture.h"
# include "ray.h"
# include "app.h"
# include "task.h"
# include "random.h"
# include "player.h"
# include "enemy.h"
# include "mini_map.h"

// FORWARD DECLARE
typedef struct s_task t_task;
typedef struct s_game t_game;

#define MAX_DEBUG_VIEWS 10
typedef struct s_debug_texture t_debug_texture;
struct s_debug_texture
{
	void *win;
	t_texture rt;
};

typedef struct s_inputctx t_inputctx;

typedef struct s_world t_world;
typedef struct s_mmap t_mmap;

# define TEX_WALLN 0
# define TEX_WALLS 1
# define TEX_WALLW 2
# define TEX_WALLE 3
# define TEX_WALL 4
# define TEX_WINDOW 5
# define TEX_DOOR 6
# define TEX_FLOOR 7
# define TEX_CEILING 8
# define TEX_ENEMY_1 9
# define TEX_ENEMY_2 10
# define TEX_ENEMY_3 11
# define TEX_ENEMY_4 12
# define TEX_ENEMY_5 13
# define TEX_ENEMY_6 14
# define TEX_ENEMY_7 15
# define TEX_ENEMY_8 16
# define TEX_ENEMY_9 17
# define TEX_ENEMY_10 18
# define TEX_ENEMY_11 19
# define TEX_ENEMY_12 20
# define TEX_ENEMY_13 21
# define TEX_ENEMY_14 22
# define TEX_ENEMY_15 23
# define TEX_ENEMY_16 24
# define TEX_ENEMY_17 25
# define TEX_ENEMY_18 26
# define TEX_ENEMY_19 27
# define TEX_ENEMY_20 28
# define TEX_ENEMY_21 29
# define TEX_ENEMY_22 30
# define TEX_ENEMY_23 31
# define TEX_ENEMY_24 32
# define TEX_ENEMY_25 33
# define TEX_ENEMY_26 34

# define TEX_SKYBOX 35
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
	t_texture		textures[36];
	t_world			*world;
	t_mmap			mmap;
	t_entity_2		*events_active[9];
	bool			events_on;
	bool			display_ui;
	t_inputctx		input;
	t_rayinfo		half;
	t_task			*tasks[TASK_LEN];
	t_rand			task_rand; // TODO: Use t_game::rand instead ?
	t_rand			rand;
	unsigned int	fpsc;
};

void		texture_debug_view_blit(t_game *game, int view, 
				t_texture tex, t_vec2 pos);
void		texture_draw_debug_view(t_game *game, int view);
t_texture	texture_get_debug_view(t_game *game, int view);
void		control_process(t_game *game);
#endif
