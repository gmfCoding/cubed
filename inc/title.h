/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   title.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 20:45:42 by kmordaun          #+#    #+#             */
/*   Updated: 2024/05/08 17:33:55 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TITLE_H
# define TITLE_H
# include "sound.h"

# define MAP_STR1 "map1.cub"
# define MAP_STR2 "map2.cub"
# define MAP_STR3 "map3.cub"
# define MAP_STR4 "map4.cub"
# define MAP_STR5 "map5.cub"
# define MAP_STR6 "map3.cub"

typedef enum e_menu_state
{
	TITLE,
	SELECT_START,
	LOAD_MAP,
	OPTIONS,
	LOAD_AND_RUN,
	RUNNING_GAME,
	LOSE_SCREEN,
	WIN_SCREEN,
	BACK_TO_TITLE,
	TO_TITLE,
	TO_GAME,
	TO_LOSE,
}				t_menu_state;

typedef struct s_title
{
	t_menu_state	state;
	int				anim_frame;
	int				anim_forward;
	bool			in_title;
	char			map_str[20][20];
	int				map_str_amount;
}		t_title;

void	title_animations(t_game *game);
void	title_show_load_map(t_game *game);
void	title_show_options(t_game *game);
void	title_load_and_run(t_game *game);
void	title_lose_screen(t_game *game, t_texture *t, t_title *title);
void	title_win_screen(t_game *game, t_texture *t, t_title *title);
void	title_back_to_title(t_game *game);
void	title_setup_screens(t_game *game);
void	game_screen_states(t_game *game);
void	title_display_maps(t_game *game);
#endif
