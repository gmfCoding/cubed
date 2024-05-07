/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_func_alert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 20:47:31 by kmordaun          #+#    #+#             */
/*   Updated: 2024/05/03 21:04:52 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "vectorconv.h"
#include "modifier_data.h"

/*
 * NAME,TARGET,IMAGE_INDEX,XPOS,YPOS
 */
t_err	mod_gen_pi(char *content, int index, t_world *world, t_map *map)
{
	t_mod_placeimg_data	mod;
	const int		found = ft_sescanf(content, "%N%s,%s,%u,%u,%u\v",
			sizeof(mod.name), &mod.name, &mod.target, &mod.img_i,
			&mod.pos.x, &mod.pos.y);

	(void)index;
	if (found != 6 || mod.pos.x >= map->width \
					|| mod.pos.y >= map->height)
		return (1);
	world->ent_2[world->ent_count] = (t_entity_2){0};
	ft_strlcpy(world->ent_2[world->ent_count].name, mod.name, NAME_SIZE);
	world->ent_2[world->ent_count].target_names[0] = ft_strdup(mod.target);
	world->ent_2[world->ent_count].pos = v2itov2(mod.pos);
	world->ent_2[world->ent_count].value = mod.img_i;
	world->ent_2[world->ent_count].handle = &target_handle_image_place;
	world->ent_2[world->ent_count].state_3 = true;
	world->ent_count++;
	return (0);
}
/*
t_err	mod_gen_al(char *content, int index, t_world *world, t_map *map)
{
	int	i;
	char	**al;
	int	x;
	int	y;

	i = -1;
	al = ft_split(content, ',');
	x = ft_atoi(al[3]) - 1;
	y = ft_atoi(al[4]);
	while (al[0][++i] && i < NAME_SIZE)
		world->ent_2[world->ent_count].name[i] = al[0][i];
	world->ent_2[world->ent_count].target = NULL;
	if (ft_strcmp(al[1], "NULL") != 0)
		world->ent_2[world->ent_count].target =	mod_search_name(world, al[1]);
	ft_strlcpy(map->mods[index].content, content, MOD_CONTENT_MAX);
	world->ent_2[world->ent_count].pos = v2new(x, y);
	world->ent_2[world->ent_count].ref_tile = 
	&map->tiles[y * (map->width + x) - 1];
		world->ent_2[world->ent_count].speed = ft_atoi(al[5]);
	if (al[2][0] == 'H')
		world->ent_2[world->ent_count].type = ET_ALERT_HIGH;
	if (al[2][0] == 'O')
		world->ent_2[world->ent_count].type = ET_ALERT_OFF;
	if (al[2][0] == 'M')
		world->ent_2[world->ent_count].type = ET_ALERT_MEDIUM;
	world->ent_count++;
	free_str_array(al);
	return (0);
}
*/
