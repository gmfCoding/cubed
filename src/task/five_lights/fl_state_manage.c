
#include "state.h"
#include "five_light.h"

int	fl_win_mode(t_game *game, int difficulty)
{
	if (difficulty == 1 && game->five_light.g_light_count == 2 \
		&& game->five_light.state[0] == 4 && game->five_light.state[9] == 4)
		return (1);
	if (difficulty == 2 && game->five_light.g_light_count == 3 \
		&& game->five_light.state[0] == 4 && game->five_light.state[1] == 4 \
		&& game->five_light.state[2] == 4)
		return (1);
	if (difficulty == 3 && game->five_light.g_light_count == 4 \
		&& game->five_light.state[3] == 4 && game->five_light.state[4] == 4 \
		&& game->five_light.state[5] == 4 && game->five_light.state[6] == 4)
		return (1);
	if (difficulty == 4 && game->five_light.g_light_count == 4 \
		&& game->five_light.state[1] == 4 && game->five_light.state[3] == 4 \
		&& game->five_light.state[6] == 4 && game->five_light.state[7] == 4)
		return (1);
	if (difficulty >= 5 && game->five_light.g_light_count == 5)
		return (1);
	return (0);
}

void	fl_input_interact(t_game *game)
{
	int		click_state;

	click_state = fl_we_clicked(game, game->input.mouse.x, game->input.mouse.y);
	if (click_state == 66)
		return ;
	fl_assign_state(game, click_state);
	if (fl_win_mode(game, game->five_light.difficulty))
	{
		game->five_light.finished = true;
		game->five_light.enabled = false;
		game->five_light.difficulty++;
	}
}

void	fl_input(t_game *game)
{
	if (input_keyup(&game->input, MB_LEFT))
	{
		if (game->five_light.show_assistance == true)
		{
			game->five_light.show_assistance = false;
			game->five_light.enabled = true;
		}
		else if (game->five_light.enabled == true)
			fl_input_interact(game);
		else if (game->five_light.finished == true)
		{
			//game->five_light.finished = false;
			fl_leave_mgame(game);
		}
	}
}

void    fl_animation(t_game *game)
{
	bool flick = (game->fpsc / 30) % 2 == 0;

	if (game->five_light.show_assistance == true)//	show_assistance
	{
		if (flick == true)
			mlx_put_image_to_window(game->app.mlx, game->app.win, game->five_light.assistance_img[0], PANEL_POS_X, PANEL_POS_Y);
		else
			mlx_put_image_to_window(game->app.mlx, game->app.win, game->five_light.assistance_img[1], PANEL_POS_X, PANEL_POS_Y);
	}
	if (game->five_light.finished == true)//	show_win
	{
		if (flick == true)
			mlx_put_image_to_window(game->app.mlx, game->app.win, game->five_light.win_img[0], PANEL_POS_X, PANEL_POS_Y);
		else
			mlx_put_image_to_window(game->app.mlx, game->app.win, game->five_light.win_img[1], PANEL_POS_X, PANEL_POS_Y);
	}
}

void    five_lights(t_game *game)
{
	int	i;

	i = -1;
	if (game->five_light.run_game == false)
		return ;
	if (game->five_light.run_setup == false)
		five_lights_Setup(game, game->five_light.difficulty);
	mlx_put_image_to_window(game->app.mlx, game->app.win, game->five_light.back_img, PANEL_POS_X, PANEL_POS_Y);
	while(++i <10)
		mlx_put_image_to_window(game->app.mlx, game->app.win, \
			game->five_light.switch_s_img[game->five_light.state[i]], \
			game->five_light.pos_x[i], game->five_light.pos_y);
	if (game->five_light.broken == true)
	{
		mlx_put_image_to_window(game->app.mlx, game->app.win, game->five_light.lights_img[3], PANEL_POS_X + 150, PANEL_POS_Y + 350);
		mlx_put_image_to_window(game->app.mlx, game->app.win, game->five_light.lights_img[1], PANEL_POS_X + 150, PANEL_POS_Y + 413);
	}
	fl_animation(game);
	fl_input(game);
}

