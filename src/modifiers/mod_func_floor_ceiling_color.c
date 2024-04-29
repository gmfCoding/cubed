/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_func_floor_ceiling_color.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:22:55 by kmordaun          #+#    #+#             */
/*   Updated: 2024/04/29 15:45:49 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "render.h"

t_err	mod_get_colour(char *content, union u_colour *colour)
{
	int			c[3];
	const int	found = ft_sescanf(content, "%u,%u,%u\v", &c[0], &c[1], &c[2]);

	if (found != 3 && c[0] >= 256 && c[1] >= 256 && c[2] >= 256)
		return (1);
	colour->channels[0] = c[0];
	colour->channels[1] = c[1];
	colour->channels[2] = c[2];
	colour->rgba |= R_ALPHA;
	return (0);
}

/*
 * used for floor colour in RGB seperated by a colon "F 123,10,13"
 */
t_err	mod_gen_f(char *content, int index, t_world *world, t_map *map)
{
	union u_colour	colour;

	if (mod_get_colour(content, &colour))
		return (1);
	world->map.color_floor = colour.rgba;
	world->map.use_floor = true;
	return (0);
}

/*
 * used for ceiling colour in RGB seperated by a colon "C 123,10,13"
 */
t_err	mod_gen_c(char *content, int index, t_world *world, t_map *map)
{
	union u_colour	colour;

	if (mod_get_colour(content, &colour))
		return (1);
	world->map.color_ceiling = colour.rgba;
	world->map.use_ceiling = true;
	return (0);
}
