/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fl_state_rules_up.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:18:45 by kmordaun          #+#    #+#             */
/*   Updated: 2024/04/18 19:18:49 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "state.h"
#include "five_light.h"

int	fl_skip_up_empty_state(t_game *game, int index)
{
	while (index > 0 && game->five_light.state[index] >= 1 \
		&& game->five_light.state[index] <= 3)
		index--;
	return (index);
}

void	fl_up_state_set_green(t_game *game, int index)
{
	index--;
	index = fl_skip_up_empty_state(game, index);
	if (game->five_light.state[index] >= 4 \
		&& game->five_light.state[index] <= 6)
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

void	fl_up_state_set_redgreen(t_game *game, int index)
{
	if (game->five_light.state[index] >= 4 \
		&& game->five_light.state[index] <= 6)
	{
		game->five_light.state[index] = 7;
		game->five_light.broken = true;
	}
	else if (game->five_light.state[index] == 0 && index--)
	{
		index = fl_skip_up_empty_state(game, index);
		if (game->five_light.state[index] >= 4 \
			&& game->five_light.state[index] <= 6)
		{
			game->five_light.state[index] = 7;
			game->five_light.broken = true;
		}
		else if (game->five_light.state[index] != 0)
			return (fl_reset_game(game));
		else
		{
			game->five_light.state[index] = 4;
			game->five_light.g_light_count++;
		}
	}
}

void	fl_gather_up_state(t_game *game, int index)
{
	index--;
	index = fl_skip_up_empty_state(game, index);
	if (index == 0)
		return (fl_reset_game(game));
	if (game->five_light.state[index] >= 4 \
		&& game->five_light.state[index] <= 6)
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
		return ;
	}
}
