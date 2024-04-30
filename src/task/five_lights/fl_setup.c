/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fl_setup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:18:16 by kmordaun          #+#    #+#             */
/*   Updated: 2024/04/18 19:18:19 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "five_light.h"
#include "state.h"

void	fl_images_ass(t_game *game, int difficulty, void **i, void *x)
{
	int	w;
	int	h;

	if (difficulty == 1)
		i[0] = mlx_xpm_file_to_image(x, "assets/fl/fl2_ona.xpm", &w, &h);
	if (difficulty == 1)
		i[1] = mlx_xpm_file_to_image(x, "assets/fl/fl2_offa.xpm", &w, &h);
	if (difficulty == 2)
		i[0] = mlx_xpm_file_to_image(x, "assets/fl/fl3_ona.xpm", &w, &h);
	if (difficulty == 2)
		i[1] = mlx_xpm_file_to_image(x, "assets/fl/fl3_offa.xpm", &w, &h);
	if (difficulty == 3)
		i[0] = mlx_xpm_file_to_image(x, "assets/fl/fl4_onam.xpm", &w, &h);
	if (difficulty == 3)
		i[1] = mlx_xpm_file_to_image(x, "assets/fl/fl4_offam.xpm", &w, &h);
	if (difficulty == 4)
		i[0] = mlx_xpm_file_to_image(x, "assets/fl/fl4_onah.xpm", &w, &h);
	if (difficulty == 4)
		i[1] = mlx_xpm_file_to_image(x, "assets/fl/fl4_offah.xpm", &w, &h);
	if (difficulty >= 5)
		i[0] = mlx_xpm_file_to_image(x, "assets/fl/fl5_ona.xpm", &w, &h);
	if (difficulty >= 5)
		i[1] = mlx_xpm_file_to_image(x, "assets/fl/fl5_offa.xpm", &w, &h);
}

void	fl_images(t_game *game, int difficulty, t_mgame *l, void *x)
{
	int	w;
	int	h;

	l->back_img = mlx_xpm_file_to_image(x, "assets/fl/fl_backing.xpm", &w, &h);
	l->swit_img[0] = mlx_xpm_file_to_image(x, "assets/fl/fl_sd.xpm", &w, &h);
	l->swit_img[1] = mlx_xpm_file_to_image(x, "assets/fl/fl_som.xpm", &w, &h);
	l->swit_img[2] = mlx_xpm_file_to_image(x, "assets/fl/fl_sou.xpm", &w, &h);
	l->swit_img[3] = mlx_xpm_file_to_image(x, "assets/fl/fl_sod.xpm", &w, &h);
	l->swit_img[4] = mlx_xpm_file_to_image(x, "assets/fl/fl_sgm.xpm", &w, &h);
	l->swit_img[5] = mlx_xpm_file_to_image(x, "assets/fl/fl_sgu.xpm", &w, &h);
	l->swit_img[6] = mlx_xpm_file_to_image(x, "assets/fl/fl_sgd.xpm", &w, &h);
	l->swit_img[7] = mlx_xpm_file_to_image(x, "assets/fl/fl_b.xpm", &w, &h);
	fl_images_ass(game, difficulty, l->assistance_img, x);
	l->win_img[0] = mlx_xpm_file_to_image(x, "assets/fl/fl_win_l.xpm", &w, &h);
	l->win_img[1] = mlx_xpm_file_to_image(x, "assets/fl/fl_win_d.xpm", &w, &h);
	l->reset_img = mlx_xpm_file_to_image(x, "assets/fl/fl_reset.xpm", &w, &h);
	l->power_img = mlx_xpm_file_to_image(x, "assets/fl/fl_power.xpm", &w, &h);
	l->lights_img[0] = mlx_xpm_file_to_image(x, "assets/fl/fl_no.xpm", &w, &h);
	l->lights_img[1] = mlx_xpm_file_to_image(x, "assets/fl/fl_rl.xpm", &w, &h);
	l->lights_img[2] = mlx_xpm_file_to_image(x, "assets/fl/fl_gl.xpm", &w, &h);
	l->lights_img[3] = mlx_xpm_file_to_image(x, "assets/fl/fl_yl.xpm", &w, &h);
	l->lights_img[4] = mlx_xpm_file_to_image(x, "assets/fl/fl_bl.xpm", &w, &h);
}

void	destroy_five_lights_images(void *mlx, t_mgame *five_light)
{
	int	i;

	i = -1;
	while (++i <= 7)
		mlx_destroy_image(mlx, five_light->swit_img[i]);
	i = -1;
	while (++i <= 1)
		mlx_destroy_image(mlx, five_light->assistance_img[i]);
	i = -1;
	while (++i <= 4)
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
		game->five_light.click_spot[i][0] = (PANEL_POS_X + 43) + (i * 71);
		game->five_light.click_spot[i][1] = (PANEL_POS_X + 112) + (i * 71);
		game->five_light.click_spot[i][2] = PANEL_POS_Y + 157;
		game->five_light.click_spot[i][3] = PANEL_POS_Y + 232;
		game->five_light.click_spot[i][4] = PANEL_POS_Y + 234;
		game->five_light.click_spot[i][5] = PANEL_POS_Y + 304;
	}
	game->five_light.clickables[0][0] = PANEL_POS_X + 83;
	game->five_light.clickables[0][1] = PANEL_POS_X + 152;
	game->five_light.clickables[0][2] = PANEL_POS_Y + 315;
	game->five_light.clickables[0][3] = PANEL_POS_Y + 490;
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
	fl_images(game, difficulty, &game->five_light, game->app.mlx);
	game->five_light.run_setup = true;
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
