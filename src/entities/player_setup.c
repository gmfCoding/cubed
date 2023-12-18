/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:55:52 by kmordaun          #+#    #+#             */
/*   Updated: 2023/11/29 13:57:10 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	player_rot_setup(char rot, t_player *player)
{
	if (rot == 'N')
	{
		player->dir.x = 0;
		player->dir.y = 1;
	}
	else if (rot == 'S')
	{
		player->dir.x = 0;
		player->dir.y = -1;
	}
	else if (rot == 'E')
	{
		player->dir.x = 1;
		player->dir.y = 0;
	}
	else if (rot == 'W')
	{
		player->dir.x = -1;
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
				player->pos.x = x;
				player->pos.y = y;
			}
		}
		y++;
		curr = curr->next;
	}
}

t_player	player_setup(t_list *curr, t_world *world)
{
	t_player	player;

	player_pos_setup(curr, &player);
	player.dir = v2new(-1, 0);
	player.plane = v2new(0, 0.5);
	player.moveSpeed = 1 / R_TFR * 2.0;
	player.rotSpeed = 1 / R_TFR * 2.0;
	return (player);
}
