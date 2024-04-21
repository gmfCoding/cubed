/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 19:43:57 by clovell           #+#    #+#             */
/*   Updated: 2024/04/08 01:10:30 by clovell          ###   ########.fr       */
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
# include "five_light.h"
# include "title.h"


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
# define TEX_SKYBOX 9
# define TEX_TITLE_ENTER_00 10
# define TEX_TITLE_ENTER_01 11
# define TEX_TITLE_ENTER_02 12
# define TEX_TITLE_ENTER_03 13
# define TEX_TITLE_ENTER_04 14
# define TEX_TITLE_ENTER_05 15
# define TEX_TITLE_ENTER_06 16
# define TEX_TITLE_LOADMAP 17
# define TEX_TITLE_OPTIONS_0 18
# define TEX_TITLE_OPTIONS_1 19
# define TEX_TITLE_QUIT_0 20
# define TEX_TITLE_QUIT_1 21
# define TEX_TITLE_SPACE_BACK 22
# define TEX_TITLE_START_0 23
# define TEX_TITLE_START_1 24
# define TEX_TITLE_BACKDROP 25



# define TEX_TITLE_MISSION_COMPLETED 26
# define TEX_TITLE_MISSION_FAILED 27
# define TEX_TITLE_NEXT_LEVEL_0 28
# define TEX_TITLE_NEXT_LEVEL_1 29
# define TEX_TITLE_RETRY_0 30
# define TEX_TITLE_RETRY_1 31
# define TEX_TITLE_CREATED_CHRIS_KYLE 32
# define TEX_TITLE_MAIN_MENU_0 33
# define TEX_TITLE_MAIN_MENU_1 34
# define TEX_FIVE_LIGHTS 35
# define TEX_UI_CONTROLS 36
# define TEX_UI_INTERACT_BRIGHT 37
# define TEX_UI_INTERACT_DUL 38
# define TEX_UI_DOOR_LOCKED 39
# define TEX_UI_TASK_INACTIVE 40

# define TEX_ENEMY_START 41
# define TEX_ENEMY_END 616

# define TEX_ARRAY_SIZE 617



typedef enum e_ui_state
{
	UI_NONE,
	UI_INTERACT,
	UI_LOCKED_DOOR,
	UI_INACTIVE_TASK,
}				t_ui_state;

struct s_game
{
	t_app			app;
	t_texture		rt0;
	t_texture		rt1;
	t_texture		rt2;

	t_title		title;
	int		loaded_index[3];
	t_mgame 	five_light;
	bool		run_fl;
	t_vec2i		stored_mouse;
	double			mouse_angle;
//	t_vec2			pos;

	t_debug_texture	views[MAX_DEBUG_VIEWS];
	int				view_count;
	t_player		player;
	t_texture		textures[TEX_ARRAY_SIZE];
	t_world			*world;
	t_mmap			mmap;
	t_entity_2		*events_active[9];
	bool			events_on;
	t_ui_state			display_ui;
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
void	control_core_process(t_game *game);
#endif
