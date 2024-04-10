#include "five_light.h"
#include "state.h"

void	fl_images_ass(t_game *game, int difficulty)
{
	int	width;
	int	height;

	if (difficulty == 1)
		game->five_light.assistance_img[0] = mlx_xpm_file_to_image(game->app.mlx, "assets/five_lights/fl2_on_ass.xpm", &width, &height);
	if (difficulty == 1)
		game->five_light.assistance_img[1] = mlx_xpm_file_to_image(game->app.mlx, "assets/five_lights/fl2_off_ass.xpm", &width, &height);
	if (difficulty == 2)
		game->five_light.assistance_img[0] = mlx_xpm_file_to_image(game->app.mlx, "assets/five_lights/fl3_on_ass.xpm", &width, &height);
	if (difficulty == 2)
		game->five_light.assistance_img[1] = mlx_xpm_file_to_image(game->app.mlx, "assets/five_lights/fl3_off_ass.xpm", &width, &height);
	if (difficulty == 3)
		game->five_light.assistance_img[0] = mlx_xpm_file_to_image(game->app.mlx, "assets/five_lights/fl4_on_ass_mid.xpm", &width, &height);
	if (difficulty == 3)
		game->five_light.assistance_img[1] = mlx_xpm_file_to_image(game->app.mlx, "assets/five_lights/fl4_off_ass_mid.xpm", &width, &height);
	if (difficulty == 4)
		game->five_light.assistance_img[0] = mlx_xpm_file_to_image(game->app.mlx, "assets/five_lights/fl4_on_ass_hard.xpm", &width, &height);
	if (difficulty == 4)
		game->five_light.assistance_img[1] = mlx_xpm_file_to_image(game->app.mlx, "assets/five_lights/fl4_off_ass_hard.xpm", &width, &height);
	if (difficulty >= 5)
		game->five_light.assistance_img[0] = mlx_xpm_file_to_image(game->app.mlx, "assets/five_lights/fl5_on_ass.xpm", &width, &height);
	if (difficulty >= 5)
		game->five_light.assistance_img[1] = mlx_xpm_file_to_image(game->app.mlx, "assets/five_lights/fl5_off_ass.xpm", &width, &height);
}

void	fl_images(t_game *game, int difficulty)
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
	fl_images_ass(game, difficulty);
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

void	destroy_five_lights_images(void *mlx, t_mgame *five_light)
{
	int	i;

	i = -1;

	while(++i <= 7)
		mlx_destroy_image(mlx, five_light->switch_s_img[i]);
	i = -1;
	while(++i <= 1)
		mlx_destroy_image(mlx, five_light->assistance_img[i]);
	i = -1;
	while(++i <= 4)
		mlx_destroy_image(mlx, five_light->lights_img[i]);
	mlx_destroy_image(mlx, five_light->win_img[0]);
	mlx_destroy_image(mlx, five_light->win_img[1]);
	mlx_destroy_image(mlx, five_light->back_img);
	mlx_destroy_image(mlx, five_light->reset_img);
	mlx_destroy_image(mlx, five_light->power_img);
}

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

void	five_lights_setup(t_game *game, int difficulty)
{
	int	i;

	i = -1;
	game->five_light.difficulty = difficulty;
	fl_images(game, difficulty);
	game->five_light.run_setup = true;
//	game->five_light.run_game = true;// check here if game should be run could do this in game??
	game->five_light.enabled = true;
	game->five_light.broken = false;
	game->five_light.finished = false;
	game->five_light.show_assistance = true;
	game->five_light.g_light_count = 0;
	game->five_light.pos_y = PANEL_POS_Y + 80;
	while (++i < 10)
	{
		game->five_light.state[i] = 0;
		game->five_light.pos_x[i] = (PANEL_POS_X + 43) + (i * 69);
	}
	fl_click_points(game);
}


