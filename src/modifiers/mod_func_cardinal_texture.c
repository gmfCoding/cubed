/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_func_cardinal_texture.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:00:14 by kmordaun          #+#    #+#             */
/*   Updated: 2023/11/29 16:45:52 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void	mod_gen_no(char *content, int index, t_world *world, t_map *map)
{
	(void)world;
	map->mods[index].type = NORTH_TEXTURE;
	map->mods[index].content = ft_strdup(content);
}

void	mod_gen_so(char *content, int index, t_world *world, t_map *map)
{
	(void)world;
	map->mods[index].type = SOUTH_TEXTURE;
	map->mods[index].content = ft_strdup(content);
}

void	mod_gen_we(char *content, int index, t_world *world, t_map *map)
{
	(void)world;
	map->mods[index].type = WEST_TEXTURE;
	map->mods[index].content = ft_strdup(content);
}

void	mod_gen_ea(char *content, int index, t_world *world, t_map *map)
{
	(void)world;
	map->mods[index].type = EAST_TEXTURE;
	map->mods[index].content = ft_strdup(content);
}
