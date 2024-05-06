/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:55:52 by kmordaun          #+#    #+#             */
/*   Updated: 2024/05/06 20:30:36 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "state.h"
#include "clmath.h"
#include "cubed.h"

void	player_rot_setup(char rot, t_player *player)
{
	player->angle_offset = 0;
	if (rot == 'N')
	{
		player->angle_offset += 90 * DEG2RAD;
	}
	else if (rot == 'S')
	{
		player->angle_offset += 270 * DEG2RAD;
	}
	else if (rot == 'E')
	{
		player->angle_offset += 0 * DEG2RAD;
	}
	else if (rot == 'W')
	{
		player->angle_offset += 180 * DEG2RAD;
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
	player_pos_setup(curr, &game->player);
	game->player.state = CAN_MOVE;
	game->player.oldp_x = game->player.pos.x;
	game->player.oldp_y = game->player.pos.y;
	game->player.plane = v2new(0.5, 0);
	game->player.move_speed = (1.0 / R_TFR) * 2.0;
	game->player.rot_speed = (1.0 / R_TFR) * 1.0;
}
