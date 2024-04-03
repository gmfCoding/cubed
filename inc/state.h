/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 19:43:57 by clovell           #+#    #+#             */
/*   Updated: 2024/03/18 22:15:00 by clovell          ###   ########.fr       */
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
# define TEX_ENEMY_START 9
# define TEX_ENEMY_END 584

# define TEX_SKYBOX 585
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
	t_texture		textures[586];
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
	unsigned int	ray;
};

void		texture_debug_view_blit(t_game *game, int view, 
				t_texture tex, t_vec2 pos);
void		texture_draw_debug_view(t_game *game, int view);
t_texture	texture_get_debug_view(t_game *game, int view);
void		control_process(t_game *game);
#endif
