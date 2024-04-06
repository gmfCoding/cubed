/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_func_fivelights.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:20:00 by kmordaun          #+#    #+#             */
/*   Updated: 2024/04/07 01:44:25 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "map.h"
#include "state.h"
#include "modifiers.h"
/*
 * NAME,TARGET,ACTIVE,XPOS,YPOS
 */
t_err	mod_gen_fl(char *content, int index, t_world *world, t_map *map)
{
	int	i;
	char	**fl;
	int	x;
	int	y;

	i = -1;
	fl = ft_split(content, ',');
	x = ft_atoi(fl[3]) - 1;
	y = ft_atoi(fl[4]);
	while (fl[0][++i] && i < NAME_SIZE)
		world->ent_2[world->ent_count].name[i] = fl[0][i];
	world->ent_2[world->ent_count].target = NULL;
	if (ft_strcmp(fl[1], "NULL") != 0)
		world->ent_2[world->ent_count].target =	mod_search_name(world, fl[1]);
	ft_strlcpy(map->mods[index].content, content, MOD_CONTENT_MAX);
	world->ent_2[world->ent_count].pos = v2new(x, y);
	*map_get_tile_ref(map, x, y) = (t_tile){ .type = WALL, .vis = 0,
	.tex = TEX_FIVE_LIGHTS};
	if (fl[2][0] == 'O')
		world->ent_2[world->ent_count].type = ET_FIVE_LIGHTS_OPEN;
	else
		world->ent_2[world->ent_count].type = ET_FIVE_LIGHTS_CLOSED;
	world->ent_count++;
	free_str_array(fl);
	return (0);
}
