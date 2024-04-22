/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fl_state_modes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:18:23 by kmordaun          #+#    #+#             */
/*   Updated: 2024/04/18 19:18:25 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "state.h"
#include "five_light.h"

void	fl_reset_game(t_game *game)
{
	int	i;

	i = -1;
	game->five_light.g_light_count = 0;
	while (++i < 10)
		game->five_light.state[i] = 0;
	game->five_light.broken = false;
}

void	fl_show_help_menu(t_game *game)
{
	game->five_light.show_assistance = true;
	game->five_light.enabled = false;
}

void	fl_leave_mgame(t_game *game)
{
	play_sound(game->app.sfx, SFX_HEARTBEAT, STOP);
	fl_reset_game(game);
	game->five_light.run_game = false;
	game->five_light.run_setup = false;
	game->player.state = DONE_TASK;
	destroy_five_lights_images(game->app.mlx, &game->five_light);
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


