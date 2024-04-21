#ifndef TITLE_H
# define TITLE_H
#include "sound.h"

typedef enum	e_menu_state
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
}		t_menu_state;


typedef struct	s_title
{
	t_menu_state	state;
	int		anim_frame;
	int		anim_forward;
	bool		in_title;
	char		map_str[20][20];
	int		map_str_amount;
}		t_title;




void	title_show_load_map(t_game *game);
void	title_show_options(t_game *game);
void	title_load_and_run(t_game *game);
void	title_lose_screen(t_game *game);
void	title_win_screen(t_game *game);
void	title_back_to_title(t_game *game);
void	title_setup_screens(t_game *game);
void	game_screen_states(t_game *game);
void	title_display_maps(t_game *game);
#endif
