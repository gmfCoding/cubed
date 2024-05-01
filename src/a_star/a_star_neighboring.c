/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star_neighboring.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 20:46:10 by kmordaun          #+#    #+#             */
/*   Updated: 2024/04/30 20:46:12 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "state.h"
#include "a_star.h"

/*
 * check to make sure node doesnt already 
 * exist also updating those nodes g_cost
 * from new nodes postion only if the g_cost 
 * is greater then what current g_cost
 * is plus 10 there maybe a way to reduce loop 
 * time here but i havent worked it out
 * possibly combining both loops into 1 idk
 */
int	star_not_in_list(t_star_node **open, \
	t_star_node **close, t_vec2 pos, t_star_node *a)
{
	t_star_node	*c;

	c = *close;
	while (c != NULL)
	{
		if ((int)c->pos.x == (int)pos.x && (int)c->pos.y == (int)pos.y)
			return (0);
		c = c->next;
	}
	c = *open;
	while (c != NULL)
	{
		if ((int)c->pos.x == (int)pos.x && (int)c->pos.y == (int)pos.y)
		{
			if (((int)c->pos.x == (int)a->pos.x || (int)c->pos.y \
				== (int)a->pos.y) && c->g_cost > a->g_cost + 10)
				c->g_cost = a->g_cost + 10;
			else
				if (c->g_cost > a->g_cost + 14)
					c->g_cost = a->g_cost + 14;
			return (0);
		}
		c = c->next;
	}
	return (1);
}

const static int	g_deltas[][2] = {
{0, -1},
{0, 1},
{-1, 0},
{1, 0}
};

/*
 * adds node in up/down/left/right pos from current.pos
 */
void	star_check_cardinal_neighbors(t_game *game, \
	t_star_node *curr, t_star_node **open, t_star_node **close)
{
	int			i;
	int			index;
	t_vec2		pos;

	i = -1;
	while (++i < sizeof(g_deltas) / sizeof(g_deltas[0]))
	{
		pos.x = curr->pos.x + g_deltas[i][0];
		pos.y = curr->pos.y + g_deltas[i][1];
		index = (int)pos.y * game->world->map.width + (int)pos.x;
		if (pos.x >= 0 && pos.x < game->world->map.width \
			&& pos.y >= 0 && pos.y < game->world->map.height \
			&& game->world->map.tiles[index].vis == -1 \
			&& star_not_in_list(open, close, pos, curr))
			star_insert_node(open, curr, pos);
	}
}

int	star_are_not_walls(t_game *game, t_vec2	pos, int i)
{
	t_tile	*t;
	int		w;
	int		k;

	t = game->world->map.tiles;
	w = game->world->map.width;
	k = w * pos.y + pos.x;
	if ((i == 0 && t[k - w - 1].vis == -1 && (t[k - w].vis == -1 \
	|| t[k - 1].vis == -1)) || (i == 1 && t[k - w + 1].vis == -1 \
	&& (t[k - w].vis == -1 || t[k + 1].vis == -1)) \
	|| (i == 2 && t[k + w - 1].vis == -1 && (t[k + w].vis == -1 \
	|| t[k - 1].vis == -1)) || (i == 3 && t[k + w + 1].vis == -1 \
	&& (t[k + w].vis == -1 || t[k + 1].vis == -1)))
		return (1);
	return (0);
}

/*
 * adds nodes on the corners around current.pos
 * this will also check to make sure at leased
 * one cardinal neighbors is not a wall, if they
 * are both walls it will not create the node
 */
void	star_check_diagonal_neighbors(t_game *game, t_star_node *curr, \
	t_star_node **open, t_star_node **close)
{
	int		i;
	t_vec2	pos;

	i = -1;
	while (++i < 4)
	{
		if (star_are_not_walls(game, curr->pos, i))
		{
			if (i % 2 == 0)
				pos.x = curr->pos.x - 1;
			else
				pos.x = curr->pos.x + 1;
			if (i < 2)
				pos.y = curr->pos.y - 1;
			else
				pos.y = curr->pos.y + 1;
			if (star_not_in_list(open, close, pos, curr))
				star_insert_node(open, curr, pos);
		}
	}
}

/*
void star_get_neighbors(t_game *game, \
t_star_node *curr, t_star_node **open, t_star_node **close)
{
    star_check_cardinal_neighbors(game, curr, open, close);
    star_check_diagonal_neighbors(game, curr, open, close);
}
*/
/*
 * this function allows movement through corner to corner 
 * which should not be allowed in our situation but it is a nice function
 */
void	star_get_neighbors(t_game *game, t_star_node *curr, \
	t_star_node **open, t_star_node **close)
{
	int			index;
	int			i;
	t_vec2		pos;

	i = -1;
	while (++i < sizeof(g_deltas) / sizeof(g_deltas[0]))
	{
		pos.x = curr->pos.x + g_deltas[i][0];
		pos.y = curr->pos.y + g_deltas[i][1];
		index = (int)pos.y * game->world->map.width + (int)pos.x;
		if (pos.x >= 0 && pos.x < game->world->map.width \
			&& pos.y >= 0 && pos.y < game->world->map.height \
			&& game->world->map.tiles[index].vis == -1)
			if (star_not_in_list(open, close, pos, curr))
				star_insert_node(open, curr, pos);
	}
}
