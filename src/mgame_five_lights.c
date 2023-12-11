#include <mlx.h>
#include "state.h"
#include "stdio.h"

#define SCR_WIDTH  960
#define SCR_HEIGHT 960
#define PANEL_SIZE_X 768
#define PANEL_SIZE_Y 512
#define PANEL_POS_X SCR_WIDTH/2 - PANEL_SIZE_X/2
#define PANEL_POS_Y SCR_HEIGHT/2 - PANEL_SIZE_Y/2


void	fl_images(t_game *game)
{
	int	width;
	int	height;

	game->five_light.back_img = mlx_xpm_file_to_image(game->app.mlx, "assets/five_lights/fl_backing.xpm", &width, &height);
	game->five_light.switch_s_img[0] = mlx_xpm_file_to_image(game->app.mlx, "assets/five_lights/fl_s_default.xpm", &width, &height);
	game->five_light.switch_s_img[1] = mlx_xpm_file_to_image(game->app.mlx, "assets/five_lights/fl_s_off_mid.xpm", &width, &height);
	game->five_light.switch_s_img[2] = mlx_xpm_file_to_image(game->app.mlx, "assets/five_lights/fl_s_off_up.xpm", &width, &height);
	game->five_light.switch_s_img[3] = mlx_xpm_file_to_image(game->app.mlx, "assets/five_lights/fl_s_off_down.xpm", &width, &height);
	game->five_light.switch_s_img[4] = mlx_xpm_file_to_image(game->app.mlx, "assets/five_lights/fl_s_green_mid.xpm", &width, &height);
	game->five_light.switch_s_img[5] = mlx_xpm_file_to_image(game->app.mlx, "assets/five_lights/fl_s_green_up.xpm", &width, &height);
	game->five_light.switch_s_img[6] = mlx_xpm_file_to_image(game->app.mlx, "assets/five_lights/fl_s_green_down.xpm", &width, &height);
	game->five_light.switch_s_img[7] = mlx_xpm_file_to_image(game->app.mlx, "assets/five_lights/fl_s_broken.xpm", &width, &height);
	game->five_light.assistance_img[0] = mlx_xpm_file_to_image(game->app.mlx, "assets/five_lights/fl_assistance.xpm", &width, &height);
	game->five_light.assistance_img[1] = mlx_xpm_file_to_image(game->app.mlx, "assets/five_lights/fl_assistance_cd.xpm", &width, &height);
	game->five_light.assistance_img[2] = mlx_xpm_file_to_image(game->app.mlx, "assets/five_lights/fl_assistance_cl.xpm", &width, &height);
	game->five_light.win_img[0] = mlx_xpm_file_to_image(game->app.mlx, "assets/five_lights/fl_win_l.xpm", &width, &height);
	game->five_light.win_img[1] = mlx_xpm_file_to_image(game->app.mlx, "assets/five_lights/fl_win_d.xpm", &width, &height);
	game->five_light.reset_img = mlx_xpm_file_to_image(game->app.mlx, "assets/five_lights/fl_reset.xpm", &width, &height);
	game->five_light.power_img = mlx_xpm_file_to_image(game->app.mlx, "assets/five_lights/fl_power.xpm", &width, &height);
	game->five_light.lights_img[0]= mlx_xpm_file_to_image(game->app.mlx, "assets/five_lights/fl_nolight.xpm", &width, &height);
	game->five_light.lights_img[1]= mlx_xpm_file_to_image(game->app.mlx, "assets/five_lights/fl_redlight.xpm", &width, &height);
	game->five_light.lights_img[2]= mlx_xpm_file_to_image(game->app.mlx, "assets/five_lights/fl_greenlight.xpm", &width, &height);
	game->five_light.lights_img[3]= mlx_xpm_file_to_image(game->app.mlx, "assets/five_lights/fl_yellowlight.xpm", &width, &height);
	game->five_light.lights_img[4]= mlx_xpm_file_to_image(game->app.mlx, "assets/five_lights/fl_brokenlight.xpm", &width, &height);
}


/*
typedef struct s_mgame
{i
	bool	run_game;
	bool	enabled;
	bool	broken;
	bool	show_assistance;
	void	*assistance_img;
	void	*back_img;
	void	*switch_s_img[8];
	void	*lights_img[5];
	void	*power;
	void	*reset;


	void	*power_light;
	void	*lever_up_anim[5];
	void	*lever_down_anim[5];
	int	state[10];
	int	pos_x[10];
	int	pos_y;
	int	click_spots[10][6];
	int	clickables[3][4];	

	int	g_light_count;

}	t_mgame;
*/



void	fl_click_points(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 10)
	{	
		game->five_light.click_spot[i][0] = (PANEL_POS_X + 43) + (i * 71);//x left
		game->five_light.click_spot[i][1] = (PANEL_POS_X + 112) + (i * 71);//x right
		game->five_light.click_spot[i][2] = PANEL_POS_Y + 157;//up click top y
		game->five_light.click_spot[i][3] = PANEL_POS_Y + 232;//up click bot y
		game->five_light.click_spot[i][4] = PANEL_POS_Y + 234;//up click top y
		game->five_light.click_spot[i][5] = PANEL_POS_Y + 304;//up click top y
	}
	game->five_light.clickables[0][0] = PANEL_POS_X + 83;//x left
	game->five_light.clickables[0][1] = PANEL_POS_X + 152;//x right
	game->five_light.clickables[0][2] = PANEL_POS_Y + 315;//y top
	game->five_light.clickables[0][3] = PANEL_POS_Y + 490;//y bot
	game->five_light.clickables[1][0] = PANEL_POS_X + 267;
	game->five_light.clickables[1][1] = PANEL_POS_X + 336;
	game->five_light.clickables[1][2] = PANEL_POS_Y + 316;
	game->five_light.clickables[1][3] = PANEL_POS_Y + 491;
	game->five_light.clickables[2][0] = PANEL_POS_X + 580;
	game->five_light.clickables[2][1] = PANEL_POS_X + 715;
	game->five_light.clickables[2][2] = PANEL_POS_Y + 323;
	game->five_light.clickables[2][3] = PANEL_POS_Y + 369;
}

//run from main
void	five_lights_Setup(t_game *game)
{
	int	i;

	i = -1;
	fl_images(game);
	game->five_light.run_game = true;// check here if game should be run could do this in game??
	game->five_light.enabled = true;
	game->five_light.broken = false;
	game->five_light.show_assistance = false;
	game->five_light.g_light_count = 0;
	game->five_light.pos_y = PANEL_POS_Y + 80;
	while (++i < 10)
	{
		game->five_light.state[i] = 0;
		game->five_light.pos_x[i] = (PANEL_POS_X + 43) + (i * 69);
	}
	fl_click_points(game);
}




//run animations and put images to screen;
void    five_lights(t_game *game)
{
	int	i;
	static int      anim_count = 0;
	static bool	flick = true;	

	i = -1;
	if (game->five_light.run_game == false)
		return ;
	mlx_put_image_to_window(game->app.mlx, game->app.win, game->five_light.back_img, PANEL_POS_X, PANEL_POS_Y);
	while(++i <10)
		mlx_put_image_to_window(game->app.mlx, game->app.win, game->five_light.switch_s_img[game->five_light.state[i]], game->five_light.pos_x[i], game->five_light.pos_y);
	if (game->five_light.broken == true)
	{
		mlx_put_image_to_window(game->app.mlx, game->app.win, game->five_light.lights_img[3], PANEL_POS_X + 150, PANEL_POS_Y + 350);
		mlx_put_image_to_window(game->app.mlx, game->app.win, game->five_light.lights_img[1], PANEL_POS_X + 150, PANEL_POS_Y + 413);
	}
	if (anim_count  % 30 == 0)
	{
		if (flick == true)
			flick = false;
		else
			flick = true;
	}
	if (game->five_light.show_assistance == true)//	show_assistance
	{
		if (flick == true)
			mlx_put_image_to_window(game->app.mlx, game->app.win, game->five_light.assistance_img[1], PANEL_POS_X, PANEL_POS_Y);
		else
			mlx_put_image_to_window(game->app.mlx, game->app.win, game->five_light.assistance_img[2], PANEL_POS_X, PANEL_POS_Y);
	}
	if (game->five_light.finished == true)//	show_win
	{
		if (flick == true)
			mlx_put_image_to_window(game->app.mlx, game->app.win, game->five_light.win_img[0], PANEL_POS_X, PANEL_POS_Y);
		else
			mlx_put_image_to_window(game->app.mlx, game->app.win, game->five_light.win_img[1], PANEL_POS_X, PANEL_POS_Y);
	}
	anim_count++;
}





int	fl_we_clicked(t_game *game, int x, int y)
{
	int	i;

	i = -1;
	while (++i < 10)
	{
		if (x > game->five_light.click_spot[i][0] && x < game->five_light.click_spot[i][1])
		{
			if (y > game->five_light.click_spot[i][2] && y < game->five_light.click_spot[i][3])
				return (10 + i);
			if (y > game->five_light.click_spot[i][4] && y < game->five_light.click_spot[i][5])
				return (20 + i);
		}
	}
	i = -1;
	while (++i < 3)
	{
		if (x > game->five_light.clickables[i][0] && \
			x < game->five_light.clickables[i][1] && \
			y > game->five_light.clickables[i][2] && \
			y < game->five_light.clickables[i][3])
			return (40 + i);
	}
	return (66);
}

void	fl_reset_game(t_game *game)
{
	int	i;

	i = -1;
	game->five_light.g_light_count = 0;
	while (++i < 10)
		game->five_light.state[i] = 0;
	game->five_light.broken = false;
}


int	fl_skip_up_empty_state(t_game *game, int index)
{
	while (index > 0 && game->five_light.state[index] >= 1 && game->five_light.state[index] <= 3)
		index--;
	return (index);
}

void	fl_up_state_set_green(t_game *game, int index)
{
	index--;
	index = fl_skip_up_empty_state(game, index);
	if (game->five_light.state[index] >= 4 && game->five_light.state[index] <= 6)
	{
		game->five_light.state[index] = 7;
		game->five_light.broken = true;
		return ;
	}
	if (game->five_light.state[index] != 0)
		return(fl_reset_game(game));
	else
	{
		game->five_light.state[index] = 4; 
		game->five_light.g_light_count++;
		return ;
	}
}

void	fl_up_state_set_redgreen(t_game *game, int index)
{
	if (game->five_light.state[index] >= 4 && game->five_light.state[index] <= 6)
	{
		game->five_light.state[index] = 7;
		game->five_light.broken = true;
		return ;
	}
	if (game->five_light.state[index] == 0)
	{
		index--;
		index = fl_skip_up_empty_state(game, index);
		if (game->five_light.state[index] >= 4 && game->five_light.state[index] <= 6)
		{
			game->five_light.state[index] = 7;
			game->five_light.broken = true;
			return ;
		}
		if (game->five_light.state[index] != 0)
			return (fl_reset_game(game));
		else
		{
			game->five_light.state[index] = 4; 
			game->five_light.g_light_count++;
			return ;
		}
	}
}

void	fl_gather_up_state(t_game *game, int index)
{
	index--;
	index = fl_skip_up_empty_state(game, index);
	if (index == 0)
		return (fl_reset_game(game));
	if (game->five_light.state[index] >= 4 && game->five_light.state[index] <= 6)
	{
		fl_up_state_set_green(game, index);
		return ;
	}
	if (game->five_light.state[index] == 0)
	{
		index--;
		index = fl_skip_up_empty_state(game, index);
		if (index == 0)
			return (fl_reset_game(game));
		fl_up_state_set_redgreen(game, index);
		return;
	}
}







int	fl_skip_down_empty_state(t_game *game, int index)
{
	while (index < 9 && game->five_light.state[index] >= 1 && game->five_light.state[index] <= 3)
		index++;
	return (index);
}

void	fl_down_state_set_green(t_game *game, int index)
{
	index++;
	index = fl_skip_down_empty_state(game, index);
	if (game->five_light.state[index] >= 4 && game->five_light.state[index] <= 6)
	{
		game->five_light.state[index] = 7;
		game->five_light.broken = true;
		return ;
	}
	if (game->five_light.state[index] != 0)
		return(fl_reset_game(game));
	else
	{
		game->five_light.state[index] = 4;
		game->five_light.g_light_count++;
		return ;
	}
}

void	fl_down_state_set_redgreen(t_game *game, int index)
{
	if (game->five_light.state[index] >= 4 && game->five_light.state[index] <= 6)
	{
		game->five_light.state[index] = 7;
		game->five_light.broken = true;
		return ;
	}
	if (game->five_light.state[index] == 0)
	{
		index++;
		index = fl_skip_down_empty_state(game, index);
		if (game->five_light.state[index] >= 4 && game->five_light.state[index] <= 6)
		{
			game->five_light.state[index] = 7;
			game->five_light.broken = true;
			return ;
		}
		if (game->five_light.state[index] != 0)
			return (fl_reset_game(game));
		else
		{
			game->five_light.state[index] = 4; 
			game->five_light.g_light_count++;
			return ;
		}
	}
}

void	fl_gather_down_state(t_game *game, int index)
{
	index++;
	index = fl_skip_down_empty_state(game, index);
	if (index == 9)
		return (fl_reset_game(game));
	if (game->five_light.state[index] >= 4 && game->five_light.state[index] <= 6)
	{
		fl_down_state_set_green(game, index);
		return ;
	}
	if (game->five_light.state[index] == 0)
	{
		index++;
		index = fl_skip_down_empty_state(game, index);
		if (index == 9)
			return (fl_reset_game(game));
		fl_down_state_set_redgreen(game, index);
		return ;
	}
}



void	fl_change_state(t_game *game, int click_state, int index)
{
	if (click_state < 20)
	{
		game->five_light.state[index] = 2;
		fl_gather_up_state(game, index);
	}
	else
	{
		game->five_light.state[index] = 3;
		fl_gather_down_state(game, index);
	}
}

void	fl_pass_state_rules(t_game *game, int click_state)
{
	int	index;

	index = click_state%10;
	if (game->five_light.state[index] >= 1 && game->five_light.state[index] <= 3)
		return ;
	if (click_state == 10 || click_state == 29 || click_state == 11 || click_state == 28 || click_state == 12 || click_state == 27)
	{
		fl_reset_game(game);
		return ;
	}
	if (game->five_light.state[index] >= 4 && game->five_light.state[index] <= 6)
	{
		fl_reset_game(game);
		return ;
	}
	if (game->five_light.state[index] == 0)
	{
		fl_change_state(game, click_state, index);
	}
}

void	fl_show_help_menu(t_game *game)
{
	game->five_light.show_assistance = true;
	game->five_light.enabled = false;
}

void	fl_leave_mgame(t_game *game)
{
	fl_reset_game(game);
	game->five_light.run_game = false;
	//gonna have to free all images here or can do it when game ends
}

void	fl_assign_state(t_game *game, int click_state)
{
	int	i;

	i = -1;
	if (click_state == 40)
	{
		fl_leave_mgame(game);
		return ;
	}
	else if (click_state == 41)
	{
		fl_reset_game(game);
		return ;
	}
	else if (click_state == 42)
	{
		fl_show_help_menu(game);
		return ;
	}
	else
	{
		while (++i < 10)
			if (game->five_light.state[i] == 7)
				return ;
		fl_pass_state_rules(game, click_state);
	}
}

int fl_mouse_hook(int button, int x, int y, t_game *game)
{
	int	click_state;

//	printf("Mouse click - Button: %d, X: %d, Y: %d\n", button, x, y);
//	printf("enabled = %d and show assisatnce = %d\n", game->five_light.enabled, game->five_light.show_assistance);
	if (game->five_light.enabled == true && button == 1)
	{
		click_state = fl_we_clicked(game, x, y);
		if (click_state == 66)
			return (0);
		fl_assign_state(game, click_state);
		if (game->five_light.g_light_count == 5)
		{
			game->five_light.finished = true;
			game->five_light.enabled = false;

		}	
		printf("clickstate = %d\n", click_state);
	}
	else if (button == 1 && game->five_light.show_assistance == true)
	{
		game->five_light.show_assistance = false;
		game->five_light.enabled = true;
	}
	else if (button == 1 && game->five_light.finished == true)
	{
		game->five_light.finished = false;
		fl_leave_mgame(game);
	}
}
