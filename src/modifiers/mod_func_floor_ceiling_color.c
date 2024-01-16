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

#include "map.h"

/*
 * used for floor colour in RGB seperated by a colon "F 255,255,10"
 */
void	mod_gen_f(char *content, int index, t_world *world, t_map *map)
{
	char	**f;

	(void)world;
	map->mods[index].type = FLOOR_COLOR;
	map->mods[index].content = ft_strdup(content);
	f = ft_split(content, ',');
	map->color_ceiling = (ft_atoi(f[0]) << 16) | (ft_atoi(f[1]) << 8) | ft_atoi(f[2]);
	free_str_array(f);
}

/*
 * used for ceiling colour in RGB seperated by a colon "C 123,10,13"
 */
void	mod_gen_c(char *content, int index, t_world *world, t_map *map)
{
	char	**c;

	(void)world;
	map->mods[index].type = CEILING_COLOR;
	map->mods[index].content = ft_strdup(content);
	c = ft_split(content, ',');
	map->color_ceiling = (ft_atoi(c[0]) << 16) | (ft_atoi(c[1]) << 8) | ft_atoi(c[2]);
	free_str_array(c);
}
