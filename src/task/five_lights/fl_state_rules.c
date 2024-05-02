/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fl_state_rules.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:18:28 by kmordaun          #+#    #+#             */
/*   Updated: 2024/04/18 19:18:30 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "state.h"
#include "five_light.h"

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

	index = click_state % 10;
	if (game->five_light.state[index] >= 1 \
		&& game->five_light.state[index] <= 3)
		return ;
	if (click_state == 10 || click_state == 29 \
		|| click_state == 11 || click_state == 28)
	{
		fl_reset_game(game);
		return ;
	}
	if (game->five_light.state[index] >= 4 \
		&& game->five_light.state[index] <= 6)
	{
		fl_reset_game(game);
		return ;
	}
	if (game->five_light.state[index] == 0)
		fl_change_state(game, click_state, index);
}

void	five_lights_hardmode(t_game *game, t_mgame *five_lights)
{
	bool	used[10] = {false};
	int 	r;
	int		i;

	i = -1;
	while (++i < 10)
	{
		do
			r = mrand(&game->rand) % 10;
		while (used[r]);
		game->five_light.state[r] = 0;
		game->five_light.pos_x[r] = (PANEL_POS_X + 43) + (i * 69);
		game->five_light.click_spot[r][0] = (PANEL_POS_X + 43) + (i * 71);
		game->five_light.click_spot[r][1] = (PANEL_POS_X + 112) + (i * 71);
		game->five_light.click_spot[r][2] = PANEL_POS_Y + 157;
		game->five_light.click_spot[r][3] = PANEL_POS_Y + 232;
		game->five_light.click_spot[r][4] = PANEL_POS_Y + 234;
		game->five_light.click_spot[r][5] = PANEL_POS_Y + 304;
		printf("%d\n", r);
		used[r] = true;
    }
}