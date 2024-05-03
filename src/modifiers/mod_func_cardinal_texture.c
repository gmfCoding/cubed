/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_func_cardinal_texture.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:00:14 by kmordaun          #+#    #+#             */
/*   Updated: 2024/05/03 21:03:16 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

t_err	mod_gen_no(char *content, int index, t_world *world, t_map *map)
{
	(void)world;
	map->mods[index].type = MT_NORTH_TEXTURE;
	ft_strlcpy(map->mods[index].content, content, MOD_CONTENT_MAX);
	return (0);
}

t_err	mod_gen_so(char *content, int index, t_world *world, t_map *map)
{
	(void)world;
	map->mods[index].type = MT_SOUTH_TEXTURE;
	ft_strlcpy(map->mods[index].content, content, MOD_CONTENT_MAX);
	return (0);
}

t_err	mod_gen_we(char *content, int index, t_world *world, t_map *map)
{
	(void)world;
	map->mods[index].type = MT_WEST_TEXTURE;
	ft_strlcpy(map->mods[index].content, content, MOD_CONTENT_MAX);
	return (0);
}

t_err	mod_gen_ea(char *content, int index, t_world *world, t_map *map)
{
	(void)world;
	map->mods[index].type = MT_EAST_TEXTURE;
	ft_strlcpy(map->mods[index].content, content, MOD_CONTENT_MAX);
	return (0);
}
