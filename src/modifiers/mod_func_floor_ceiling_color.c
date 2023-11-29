/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_func_floor_ceiling_color.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:22:55 by kmordaun          #+#    #+#             */
/*   Updated: 2023/11/29 16:47:17 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	mod_gen_f(char *content, int mod_pos, t_world *world, t_map *map)
{
	(void)world;
	map->mods[mod_pos].type = FLOOR_COLOR;
	map->mods[mod_pos].content = content;
}

void	mod_gen_c(char *content, int mod_pos, t_world *world, t_map *map)
{
	(void)world;
	map->mods[mod_pos].type = CEILING_COLOR;
	map->mods[mod_pos].content = content;
}

