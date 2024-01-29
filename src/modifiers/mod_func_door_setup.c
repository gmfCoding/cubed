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



char    *ft_strcpy(char *s1, char *s2)
{
	int i;
 
	i = -1;
	while (s2[++i])
		s1[i] = s2[i];
	s1[i] = s2[i];
	return (s1);
}

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
//	map->mods[index].type = DOOR;
	dr = ft_split(content, ',');
	while (dr[0][++i] && i < NAME_SIZE)
		world->ent->doors[dr_count].name[i] = dr[0][i];
	map->mods[index].content = ft_strdup(dr[1]);
	world->ent->doors[dr_count].pos.x = ft_atoi(dr[2]);
	world->ent->doors[dr_count].pos.y = ft_atoi(dr[3]);
	world->ent->doors[dr_count].speed = ft_atoi(dr[4]);
	world->ent->doors[dr_count].closed = (dr[5][0] == 'C') ? true : false;
	world->ent->doors[dr_count].locked = (dr[6][0] == 'L') ? true : false;



	map->tiles[ft_atoi(dr[3]) * map->width + ft_atoi(dr[2]) -1].type = DOOR;
	map->tiles[ft_atoi(dr[3]) * map->width + ft_atoi(dr[2]) -1].vis = 1;
	map->tiles[ft_atoi(dr[3]) * map->width + ft_atoi(dr[2]) -1].tex = 6;

//new entity_2 stuff
	i = -1;
	int	x;
	int	y;

	x = ft_atoi(dr[2]) - 1;
	y = ft_atoi(dr[3]);
	while (dr[0][++i] && i < NAME_SIZE)
		world->ent_2[world->ent_count].name[i] = dr[0][i];
	ft_strcpy(world->ent_2[world->ent_count].ui_display_1, "PRESS 'E' TO INTERACT");
	ft_strcpy(world->ent_2[world->ent_count].ui_display_2, "LOCKED");
	world->ent_2[world->ent_count].pos[0].x = x;
	world->ent_2[world->ent_count].pos[0].y = y;
	world->ent_2[world->ent_count].pos[1].x = x + 1;
	world->ent_2[world->ent_count].pos[1].y = y;
	world->ent_2[world->ent_count].pos[2].x = x + 1;
	world->ent_2[world->ent_count].pos[2].y = y + 1;
	world->ent_2[world->ent_count].pos[3].x = x;
	world->ent_2[world->ent_count].pos[3].y = y + 1;
	world->ent_2[world->ent_count].pos[4].x = x - 1;
	world->ent_2[world->ent_count].pos[4].y = y + 1;
	world->ent_2[world->ent_count].pos[5].x = x - 1;
	world->ent_2[world->ent_count].pos[5].y = y;
	world->ent_2[world->ent_count].pos[6].x = x - 1;
	world->ent_2[world->ent_count].pos[6].y = y - 1;
	world->ent_2[world->ent_count].pos[7].x = x;
	world->ent_2[world->ent_count].pos[7].y = y - 1;
	world->ent_2[world->ent_count].pos[8].x = x + 1;
	world->ent_2[world->ent_count].pos[8].y = y - 1;
	world->ent_2[world->ent_count].ref_tile = &map->tiles[y * (map->width + x) - 1];
	world->ent_2[world->ent_count].target = NULL;
	world->ent_2[world->ent_count].speed = ft_atoi(dr[4]);
	world->ent_2[world->ent_count].state_1 = (dr[5][0] == 'C') ? true : false;
	world->ent_2[world->ent_count].state_2 = (dr[6][0] == 'L') ? true : false;
	world->ent_2[world->ent_count].state_3 = false;
	if (dr[5][0] == 'C' && dr[6][0] == 'L')
		world->ent_2[world->ent_count].type = DOOR_LOCKED;
	if (dr[5][0] == 'C' && dr[6][0] != 'L')
		world->ent_2[world->ent_count].type = DOOR_UNLOCKED;
	if (dr[5][0] != 'C')
		world->ent_2[world->ent_count].type = DOOR_OPEN;
	world->ent_count++;
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
