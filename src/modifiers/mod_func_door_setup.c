/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_func_door_setup.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 18:56:18 by kmordaun          #+#    #+#             */
/*   Updated: 2024/01/17 18:35:52 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

/*
 * NAME,TEXTURE,XPOS,YPOS,SPEED,CLOSED,LOCKED
 */
void	mod_gen_dr(char *content, int index, t_world *world, t_map *map)
{
	static int	dr_count = 0;
	int	i;
	char	**dr;
	char	*texture;

	i = -1;
	map->mods[index].type = DOOR;
	dr = ft_split(content, ',');
	while (dr[0][++i] && i < NAME_SIZE)
		world->ent->doors[dr_count].name[i] = dr[0][i];
	map->mods[index].content = ft_strdup(dr[1]);
	world->ent->doors[dr_count].pos.x = ft_atoi(dr[2]);
	world->ent->doors[dr_count].pos.y = ft_atoi(dr[3]);
	world->ent->doors[dr_count].speed = ft_atoi(dr[4]);
	world->ent->doors[dr_count].closed = (dr[5][0] == 'C') ? true : false;
	world->ent->doors[dr_count].locked = (dr[6][0] == 'L') ? true : false;
	map->tiles[ft_atoi(dr[3]) * map->width + ft_atoi(dr[2]) -1].type = MODIFIED;
	map->tiles[ft_atoi(dr[3]) * map->width + ft_atoi(dr[2]) -1].vis = 1;
	map->tiles[ft_atoi(dr[3]) * map->width + ft_atoi(dr[2]) -1].tex = 6;
	free_str_array(dr);
}

/*
 * NAME,TEXTURE,ACCESSDOORNAMED,XPOS,YPOS,AUTOUNLOCKOPEN,GRABBEDBYPLAYER 
 */
void	mod_gen_ke(char *content, int index, t_world *world, t_map *map)
{
	static int	ke_count = 0;
	int	i;
	char	**ke;
	char	*texture;

	i = -1;
	ke = ft_split(content, ',');
	while (ke[0][++i] && i < NAME_SIZE)
		world->ent->keys[ke_count].name[i] = ke[0][i];
	map->mods[index].content = ft_strdup(ke[1]);
	i = -1;
	while (ke[2][++i] && i < NAME_SIZE)
		world->ent->keys[ke_count].doorname[i] = ke[2][i];
	world->ent->keys[ke_count].pos.x = ft_atoi(ke[3]);
	world->ent->keys[ke_count].pos.y = ft_atoi(ke[4]);
	world->ent->keys[ke_count].auto_open = (ke[5][0] == 'A') ? true : false;
	world->ent->keys[ke_count].collected = (ke[6][0] == 'C') ? true : false;
	free_str_array(ke);
}