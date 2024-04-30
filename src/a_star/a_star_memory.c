/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star_memory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 20:46:05 by kmordaun          #+#    #+#             */
/*   Updated: 2024/04/30 20:46:06 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "state.h"
#include "a_star.h"

void    star_deallocate_node(t_star_node **node)
{
        t_star_node	*curr;
	t_star_node	*temp;

        curr = *node;
        while (curr != NULL) 
	{
                temp = curr;
                curr = curr->next;
                free(temp);
        }
}

/*
 * allocates memory for a new node the next is used to store acces to all nodes inside open
 * or close and the parent node is used for when the target is found and can trace back the steps 
 * made to get to that location the allocated nodes a dealloacted with the above fucntion
 */
void    star_insert_node(t_star_node **node, t_star_node *parent, t_vec2 pos)
{
	t_star_node	*temp;

	temp = malloc(sizeof(t_star_node));
        if (temp == NULL)
		return;
        temp->next = NULL;
	temp->parent = parent;
	temp->g_cost = 0;
	if (parent != NULL)
	{
		if (pos.x == parent->pos.x || pos.y == parent->pos.y)
			temp->g_cost = parent->g_cost + 10;
		else if (pos.x != parent->pos.x && pos.y != parent->pos.y)
			temp->g_cost = parent->g_cost + 14;
	}
        temp->pos = pos;
        if (*node == NULL)
        {
                *node = temp;
                return;
        }
        temp->next = *node;
        *node = temp;
}

/*
 * return a malloc vector array with is the path from start to target
 * the path must be freed, if looping over the path check for end of path using  
 * pos[i].x == -1
 * pos[i].y == -1 
 * ^^ this is the last index of the return path^^
 */
t_vec2	*star_construct_path(t_star_node *end_node, t_star_node **open, t_star_node **close)
{
	int	path_length;
	t_vec2	*path;

	path_length = 0;
	t_star_node *curr = end_node;
	while (curr != NULL)
	{
		path_length++;
		curr = curr->parent;
	}
	path = malloc(sizeof(t_vec2) * (path_length + 1));
	if (path == NULL)
		return NULL;
	curr = end_node;
	path[path_length].x = -1;
	path[path_length].y = -1;
	while (curr != NULL)
	{
		path[--path_length] = curr->pos;
		curr = curr->parent;
	}
	star_deallocate_node(open);
	star_deallocate_node(close);
	return (path);
}



/*
void    print_node(t_star_node **node)
{
        t_star_node *curr = *node;
	while (curr != NULL)
        {
                printf("%d   %d\n", (int)curr->pos.x, (int)curr->pos.y);
                curr = curr->next;
        }
}
*/

/*
void	print_vector_path(t_game *game)
{
	t_vec2	start;
	t_vec2	end;
	t_vec2	*path;
	int	i;

	i = 0;

	printf("\n");
//	start = v2new(27,6);

	start = v2new(10,10);
//	end = game->player.pos;
	end = v2new(23,9);
	printf("the vis of player location is %d\n", game->world->map.tiles[(int)end.x + ((int)end.y * game->world->map.width)].vis);
	printf("\nstart = %d,%d : end = %d,%d \n", (int)start.x, (int)start.y, (int)end.x, (int)end.y);
	
	path = star_find_path(game, start, end);
	if (path == NULL)
		return ;
	while (path[i].x != -1  && path[i].y != -1)
	{
		printf("PATH = x %d , y %d\n", (int)path[i].x, (int)path[i].y);
		i++;
	}
	free(path);
}
*/
