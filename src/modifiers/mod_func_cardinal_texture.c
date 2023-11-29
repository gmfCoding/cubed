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

#include "cubed.h"


void	mod_gen_no(char *content, int mod_pos, t_world *world, t_map *map)
{
	(void)world;
	map->mods[mod_pos].type = NORTH_TEXTURE;
	map->mods[mod_pos].content = content;
}

void	mod_gen_so(char *content, int mod_pos, t_world *world, t_map *map)
{
	(void)world;
	map->mods[mod_pos].type = SOUTH_TEXTURE;
	map->mods[mod_pos].content = content;
}

void	mod_gen_we(char *content, int mod_pos, t_world *world, t_map *map)
{
	(void)world;
	map->mods[mod_pos].type = WEST_TEXTURE;
	map->mods[mod_pos].content = content;
}

void	mod_gen_ea(char *content, int mod_pos, t_world *world, t_map *map)
{
	(void)world;
	map->mods[mod_pos].type = EAST_TEXTURE;
	map->mods[mod_pos].content = content;
}
