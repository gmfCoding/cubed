#ifndef FIVE_LIGHT_H
# define FIVE_LIGHT_H
# include <mlx.h>
# include <stdio.h>
# include <stdbool.h>

# define SCR_WIDTH  960
# define SCR_HEIGHT 960
# define PANEL_SIZE_X 768
# define PANEL_SIZE_Y 512
# define PANEL_POS_X SCR_WIDTH/2 - PANEL_SIZE_X/2
# define PANEL_POS_Y SCR_HEIGHT/2 - PANEL_SIZE_Y/2

typedef struct s_game t_game;

typedef struct s_mgame
{
	bool	run_game;
	bool	run_setup;
	bool	enabled;
	bool	broken;
	bool	finished;
	bool	show_assistance;
	void	*assistance_img[2];
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
	int	difficulty;
	int	pos_y;
	int	click_spot[10][6];
	int	clickables[3][4];
	int	g_light_count;
}	t_mgame;

void    five_lights(t_game *game);
void	destroy_five_lights_images(void *mlx, t_mgame *five_light);
void	fl_gather_down_state(t_game *game, int index);
void	fl_change_state(t_game *game, int click_state, int index);
void	fl_gather_up_state(t_game *game, int index);
void	fl_pass_state_rules(t_game *game, int click_state);
int	fl_we_clicked(t_game *game, int x, int y);
void	fl_reset_game(t_game *game);
void	fl_leave_mgame(t_game *game);
void	fl_assign_state(t_game *game, int click_state);
void	five_lights_Setup(t_game *game, int difficulty);

#endif
