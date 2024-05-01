/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star_path_collect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 20:46:14 by kmordaun          #+#    #+#             */
/*   Updated: 2024/04/30 20:46:16 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "state.h"
#include "a_star.h"

/*
 * get the huristic which is just a fancy way of saying
 * it get the distance to the target pos from current node
 */
int	star_get_huristic(t_star_node *node, t_vec2 target)
{
	t_vec2	diff;

	diff = v2sub(node->pos, target);
	return (v2mag(diff) * 10);
}

t_star_node	*star_change_to_close(t_star_node **open, \
	t_star_node **close, t_star_node *temp, t_star_node *btemp)
{
	if (btemp == NULL)
		*open = temp->next;
	else
		btemp->next = temp->next;
	temp->next = *close;
	*close = temp;
	return (temp);
}

/*
 * this fuction is returning a ptr to the node with the smallest_cost
 * its also moving that node to close and calls the huristic function
 */
t_star_node	*star_get_smallest_cost(t_star_node **open, \
	t_star_node **close, t_vec2 target)
{
	t_star_node	*btemp;
	t_star_node	*temp;
	t_star_node	*curr;
	int			small;
	int			h;

	curr = *open;
	small = curr->g_cost + star_get_huristic(curr, target);
	btemp = NULL;
	temp = curr;
	while (curr->next != NULL)
	{
		h = star_get_huristic(curr->next, target);
		if (h + curr->next->g_cost <= small)
		{
			small = h + curr->next->g_cost;
			btemp = curr;
			temp = curr->next;
		}
		curr = curr->next;
	}
	return (star_change_to_close(open, close, temp, btemp));
}

/*
 * A* ALGORITHYM 
 * populates a path from the starting vector 
 * adding nodes for each of its neighbors
 * then checks which of those neighbors huristic 
 * and moves made from start_cost
 * is the smallest and moves to that neighboring 
 * node and repeats if two are tide for 
 * the smallest it will then choose the 
 * smallest huristic cost which is the distance
 * from current node to target. can 
 * possible change the t_vec2 struct to store ints
 * or something smaller then can get rig of the cast of int from double
 *
 * this function returns a malloc array of 
 * vector that does need to be freed
 * unless there is no valid path to target it will the return NULL
 * 
 * VVVVVV you can call the functio like this VVVVVV
 *
 * path = star_find_path(game, start, end);
 * if (path == NULL)
 * 	return ;
 * while (path[i].x != -1  && path[i].y != -1)
 * {
 * 	printf("PATH = x %d , y %d\n", (int)path[i].x, (int)path[i].y);
 * 	i++;
 * }
 * free(path);
 */
t_vec2	*star_find_path(t_game *game, t_vec2 start, t_vec2 target)
{
	t_star_node	*open;
	t_star_node	*close;
	t_star_node	*smallest;

	open = NULL;
	close = NULL;
	star_insert_node(&open, NULL, start);
	while (open != NULL)
	{
		smallest = star_get_smallest_cost(&open, &close, target);
		if ((int)smallest->pos.x == (int)target.x \
			&& (int)smallest->pos.y == (int)target.y)
			break ;
		star_get_neighbors(game, smallest, &open, &close);
	}
	if (open == NULL)
	{
		star_deallocate_node(&open);
		star_deallocate_node(&close);
		return (NULL);
	}
	return (star_construct_path(smallest, &open, &close));
}
