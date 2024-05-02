/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_func_minimap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 20:47:56 by kmordaun          #+#    #+#             */
/*   Updated: 2024/04/30 20:47:59 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

/*
 * NAME,LOCATION,MMAP_FOG
 */
t_err	mod_gen_mm(char *content, int index, t_world *world, t_map *map)
{
//TODO add toggle map postion
	(void)world;
	map->mods[index].type = MT_MINI_MAP;
	ft_strlcpy(map->mods[index].content, content, MOD_CONTENT_MAX);
	return (0);
//	printf("%s\n",map->mods[index].content);
}



