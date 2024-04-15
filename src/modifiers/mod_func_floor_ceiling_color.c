/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_func_floor_ceiling_color.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:22:55 by kmordaun          #+#    #+#             */
/*   Updated: 2024/04/12 16:04:20 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "render.h"
typedef union u_colour
{
	int	rgba;
	char channels[4];
} t_ucolour;

/*
 * used for floor colour in RGB seperated by a colon "F 123,10,13"
 */
t_err	mod_gen_f(char *content, int index, t_world *world, t_map *map)
{
	int			r;
	int			g;
	int			b;
	t_ucolour	colour;
	const int	found = ft_sescanf(content, "%u,%u,%u\v", &r, &g, &b);
	static bool stop = false;
	if (stop)
		return 0;
	stop = true;
	if (found != 3 && r >= 256 && g >= 256 && b >= 256)
		return (1);
	colour.channels[0] = b;
	colour.channels[1] = g;
	colour.channels[2] = r;
	colour.channels[3] = R_ALPHA;
	world->map.color_floor = colour.rgba;
	world->map.use_floor = true;
	printf("floorin:%x\n", colour.rgba);
	return (0);
}

/*
 * used for ceiling colour in RGB seperated by a colon "C 123,10,13"
 */
t_err	mod_gen_c(char *content, int index, t_world *world, t_map *map)
{
	int			r;
	int			g;
	int			b;
	t_ucolour	colour;
	const int	found = ft_sescanf(content, "%u,%u,%u\v", &r, &g, &b);
	static bool stop = false;
	if (stop)
		return 0;
	stop = true;
	if (found != 3 && r >= 256 && g >= 256 && b >= 256)
		return (1);
	colour.channels[0] = b;
	colour.channels[1] = g;
	colour.channels[2] = r;
	colour.channels[3] = R_ALPHA;
	printf("cieling:%x\n", colour.rgba);
	world->map.color_ceiling = colour.rgba;
	world->map.use_ceiling = true;
	return (0);
}