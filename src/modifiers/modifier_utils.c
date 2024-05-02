/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifier_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:55:52 by kmordaun          #+#    #+#             */
/*   Updated: 2024/04/29 14:51:49 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

t_vec2	mod_dir_to_vec2(char dir)
{
	if (dir == 'N')
		return (v2new(0, -1));
	else if (dir == 'E')
		return (v2new(1, 0));
	else if (dir == 'S')
		return (v2new(0, 1));
	else
		return (v2new(-1, 0));
}

t_mod	*mod_get_mod(t_map *map, t_modtype type, int *index)
{
	size_t	i;

	i = 0;
	while (i < sizeof(map->mods) / sizeof(t_mod) && map->mods[i].type != type)
		i++;
	if (index != NULL)
		*index = i;
	if (i < sizeof(map->mods) / sizeof(*map->mods))
		return (&map->mods[i]);
	return (NULL);
}

t_entity_2	*mod_search_name(t_world *world, char *str)
{
	int	i;

	i = -1;
	while ((size_t)++i < world->ent_count)
	{
		if (ft_strcmp(world->ent_2[i].name, str) == 0)
			return (&world->ent_2[i]);
	}
	return (NULL);
}
