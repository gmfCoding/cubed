/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fl_state_rules.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:18:28 by kmordaun          #+#    #+#             */
/*   Updated: 2024/05/08 14:28:35 by clovell          ###   ########.fr       */
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

static int	select_random_unactive(bool used[10], t_rand *rand)
{
	int	i;
	int	r;

	i = -1;
	while (++i < 1000)
	{
		r = mrand(rand) % 10;
		if (used[r] == false)
			return (r);
	}
	return (0);
}

void	five_lights_hardmode(t_game *game, t_mgame *five_lights)
{
	bool	used[10];
	int		r;
	int		i;

	i = -1;
	while (++i < 10)
		used[i] = false;
	i = -1;
	while (++i < 10)
	{
		r = select_random_unactive(used, &game->rand);
		five_lights->state[r] = 0;
		five_lights->pos_x[r] = (PANEL_POS_X + 43) + (i * 69);
		five_lights->click_spot[r][0] = (PANEL_POS_X + 43) + (i * 71);
		five_lights->click_spot[r][1] = (PANEL_POS_X + 112) + (i * 71);
		five_lights->click_spot[r][2] = PANEL_POS_Y + 157;
		five_lights->click_spot[r][3] = PANEL_POS_Y + 232;
		five_lights->click_spot[r][4] = PANEL_POS_Y + 234;
		five_lights->click_spot[r][5] = PANEL_POS_Y + 304;
		used[r] = true;
	}
}
