/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:55:52 by kmordaun          #+#    #+#             */
/*   Updated: 2024/03/30 21:24:06 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "state.h"

void	player_rot_setup(char rot, t_player *player)
{
	// TODO: Broke after new mouse look system, impl angle offsets instead.
	if (rot == 'N')
	{
		player->dir.x = 0;
		player->dir.y = -1;
	}
	else if (rot == 'S')
	{
		player->dir.x = 0;
		player->dir.y = 1;
	}
	else if (rot == 'E')
	{
		player->dir.x = -1;
		player->dir.y = 0;
	}
	else if (rot == 'W')
	{
		player->dir.x = 1;
		player->dir.y = 0;
	}
}

void	player_pos_setup(t_list *curr, t_player *player)
{
	char	*str;
	int		x;
	int		y;

	y = 0;
	while (curr != NULL && curr->content != NULL)
	{
		str = (char *)curr->content;
		x = -1;
		while (str[++x] != '\n' && str[x] != '\0')
		{
			if (str[x] == 'N' || str[x] == 'S' \
				|| str[x] == 'E' || str[x] == 'W')
			{
				player_rot_setup(str[x], player);
				player->pos.x = x + 0.5;
				player->pos.y = y + 0.5;
			}
		}
		y++;
		curr = curr->next;
	}
}

/*
 * the function is called within the map_setup.c
 */
/*
t_player	player_setup(t_list *curr)
{
	t_player	player;

	player_pos_setup(curr, &player);
	player.plane = v2new(0.5,0);
	player.moveSpeed = 1.0 / R_TFR * 2.0;
	player.rotSpeed =  1.0 / R_TFR * 2.0;
	return (player);
}
*/
void	player_setup(t_list *curr, t_game *game)
{
//	_player	player;

	player_pos_setup(curr, &game->player);
	game->player.state = DONE_TASK;
	game->player.oldp_x = game->player.pos.x;
	game->player.oldp_y = game->player.pos.y;
	game->player.plane = v2new(0.5,0);
	game->player.moveSpeed = (1.0 / R_TFR) * 2.0;
	game->player.rotSpeed =  (1.0 / R_TFR) * 2.0;
//	return (player);
}
