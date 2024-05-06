/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_func_minimap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 20:47:56 by kmordaun          #+#    #+#             */
/*   Updated: 2024/05/03 20:38:42 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

/*
 * NAME,LOCATION,MMAP_FOG
 */
//	printf("%s\n",map->mods[index].content);
//TODO add toggle map postion
t_err	mod_gen_mm(char *content, int index, t_world *world, t_map *map)
{
	(void)world;
	map->mods[index].type = MT_MINI_MAP;
	ft_strlcpy(map->mods[index].content, content, MOD_CONTENT_MAX);
	return (0);
}
