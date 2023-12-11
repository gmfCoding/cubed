/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 19:43:57 by clovell           #+#    #+#             */
/*   Updated: 2023/11/29 16:59:50 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATE_H
# define STATE_H

#include "input.h"
#include "texture.h"
#include "map.h"
typedef struct s_world t_world;
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

//typedef struct s_world t_world;
typedef struct s_mgame
{
	bool	run_game;
	bool	enabled;
	bool	broken;
	bool	finished;
	bool	show_assistance;
	void	*assistance_img[3];
	void	*win_img[2];
	void	*back_img;
	void	*switch_s_img[8];
	void	*lights_img[5];
	void	*lever_up_anim[5];
	void	*lever_down_anim[5];
	void	*power_img;
	void	*reset_img;
	void	*power_light;
	int	state[10];
	int	pos_x[10];
	int	pos_y;
	int	click_spot[10][6];
	int	clickables[3][4];

	int	g_light_count;

}	t_mgame;

struct s_game
{
	t_app	app;
	t_texture rt0;
	t_texture rt1;

	t_vec2 mouse;
	t_vec2 pos;
//	t_world	world;
	t_debug_texture views[MAX_DEBUG_VIEWS];
	int view_count;
	t_world		world;
	t_mgame 	five_light;
	t_player	player;

	t_inputctx input;
};

void texture_debug_view_blit(t_game *game, int view, t_texture tex, t_vec2 pos);
void texture_draw_debug_view(t_game *game, int view);
t_texture texture_get_debug_view(t_game *game, int view);
void    five_lights(t_game *game);

#endif
