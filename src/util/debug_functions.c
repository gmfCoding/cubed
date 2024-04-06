/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 02:30:24 by clovell           #+#    #+#             */
/*   Updated: 2024/04/07 02:30:52 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "state.h"

void	debug_world_print_vis(t_world *world)
{
	// EVALUATE: REMOVE FUNCTION?
	printf("\n");
	for (size_t y = 0; y < world->map.height; y++)
	{
		for (size_t x = 0; x < world->map.width; x++)
		{
			int vis = map_get_tile(&world->map, x, y).vis;
			if (vis == -2)
				printf("0");
			else if (vis == -1)
				printf(" ");
			else if (vis == 0)
				printf("#");
			else if (vis == 1)
				printf("=");
		}
		printf("\n");
	}
	printf("\n");
}