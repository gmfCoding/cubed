/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 01:43:16 by clovell           #+#    #+#             */
/*   Updated: 2024/02/26 01:57:07 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef RAY_H
# define RAY_H

# include <inttypes.h>
# include "config.h"
/**
 * @param depth Distance from the normal plane
 * @param dist Distance from the start
 * @param minX The smallest height of the ray
 * @param minY The largest height of the ray
 * @param x The x position of the wall
 * @param y The y position of the wall
 * @param side The side the wall hit: `0: NORTH` `1: SOUTH` `2: EAST` `3: WEST`
 * 			
*/
typedef struct s_hitpoint	t_hitpoint;
struct s_hitpoint
{
	float depth;
	float dist;
	float minX;
	float minY;
	int	sp_tex;
	int x;
	int y;
	int side;
};

typedef struct s_rayinfo	t_rayinfo;
struct s_rayinfo
{
	t_hitpoint	depths[MAX_DEPTHS];
	uint8_t		hits;
};

typedef struct s_dda
{
	t_vec2	delta;
	t_vec2i	map;
	t_vec2i	step;
	t_vec2	side;
}			t_dda;

typedef struct s_game t_game;
t_rayinfo	raycast(t_game *game, t_vec2 start, t_vec2 dir);
#endif
