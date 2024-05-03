/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 02:30:24 by clovell           #+#    #+#             */
/*   Updated: 2024/05/03 18:01:42 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "state.h"

// EVALUATE: REMOVE FUNCTION?
void	debug_world_print_vis(t_world *world)
{
	int		vis;
	size_t	y;
	size_t	x;

	printf("\n");
	x = -1;
	y = -1;
	while (++y < world->map.height)
	{
		while (++x < world->map.width)
		{
			vis = map_get_tile(&world->map, x, y).vis;
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
