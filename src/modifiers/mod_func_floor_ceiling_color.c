/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_func_floor_ceiling_color.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:22:55 by kmordaun          #+#    #+#             */
/*   Updated: 2024/04/16 16:41:38 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "render.h"
/*
 * used for floor colour in RGB seperated by a colon "F 255,255,10"
 */
t_err	mod_gen_f(char *content, int index, t_world *world, t_map *map)
{
	char	**f;

	printf("F %s\n", content);
	(void)world;
	map->mods[index].type = MT_FLOOR_COLOR;
	ft_strlcpy(map->mods[index].content, content, MOD_CONTENT_MAX);
	f = ft_split(content, ',');
	map->use_floor = true;
	map->color_floor = 0;
	map->color_floor |= ft_atoi(f[0]) << OF_RED;
	map->color_floor |= ft_atoi(f[1]) << OF_GREEN;
	map->color_floor |= ft_atoi(f[2]) << OF_BLUE;
	map->color_floor |= R_ALPHA;
	free_str_array(f);
	return (0);
}

/*
 * used for ceiling colour in RGB seperated by a colon "C 123,10,13"
 */
t_err	mod_gen_c(char *content, int index, t_world *world, t_map *map)
{
	char	**c;

	(void)world;
	map->mods[index].type = MT_CEILING_COLOR;
	ft_strlcpy(map->mods[index].content, content, MOD_CONTENT_MAX);
	c = ft_split(content, ',');
	map->use_ceiling = true;
	map->color_ceiling = 0;
	map->color_ceiling |= ft_atoi(c[0]) << OF_RED;
	map->color_ceiling |= ft_atoi(c[1]) << OF_GREEN;
	map->color_ceiling |= ft_atoi(c[2]) << OF_BLUE;
	map->color_ceiling |= R_ALPHA;
	free_str_array(c);
	return (0);
}
