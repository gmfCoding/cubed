#ifndef TITLE_H
# define TITLE_H


typedef enum	e_menu_state
{
	TITLE,
	SELECT_START,
	LOAD_MAP,
	SELECT_OPTIONS,
	OPTIONS,
	SELECT_QUIT,
	RUN_GAME,
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






void	title_screen(t_game *game);


#endif
