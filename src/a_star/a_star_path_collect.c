
#include "state.h"
#include "a_star.h"

/*
 * check to make sure node doesnt already exist also updating those nodes g_cost
 * from new nodes postion only if the g_cost is greater then what current g_cost
 * is plus 10 there maybe a way to reduce loop time here but i havent worked it out
 * possibly combining both loops into 1 idk
 */
int	star_not_in_list(t_star_node **open, t_star_node **close, t_vec2 pos, t_star_node *active)
{
	t_star_node	*curr;

	curr = *close;
	while (curr != NULL)
	{
		if ((int)curr->pos.x == (int)pos.x && (int)curr->pos.y == (int)pos.y)
			return 0;
		curr = curr->next;
	}
	curr = *open;
	while (curr != NULL)
	{
		if ((int)curr->pos.x == (int)pos.x && (int)curr->pos.y == (int)pos.y)
		{
			if ((int)curr->pos.x == (int)active->pos.x || (int)curr->pos.y == (int)active->pos.y)
				if (curr->g_cost > active->g_cost + 10)
					curr->g_cost = active->g_cost + 10;
			else
				if (curr->g_cost > active->g_cost + 14)
					curr->g_cost = active->g_cost + 14;
			return 0;
		}
		curr = curr->next;
	}
	return 1;
}

/*
 * inserts a node around the current node as long as the node doesnt exit and
 * its vis is set to -1, this has been updated but it is incorrect have to 
 * checkout old star_get_neighbours function because this still allows movement
 * through corner to corner which should not be allowed earlier code handles this
 */
void	star_get_neighbours(t_game *game, t_star_node *curr, t_star_node **open, t_star_node **close)
{
	int		index;
	int		i;
	t_vec2		pos;
	const int	deltas[][2] = DELTAS;

	index = game->world->map.width * curr->pos.y + curr->pos.x;
	i = -1;
	while (++i < DELTAS_LEN)
	{
		pos.x = curr->pos.x + deltas[i][0];
		pos.y = curr->pos.y + deltas[i][1];
		if (pos.x >= 0 && pos.x < game->world->map.width && pos.y >= 0 && pos.y < game->world->map.height \
			&& game->world->map.tiles[(int)pos.y * game->world->map.width + (int)pos.x].vis == -1)
			if (star_not_in_list(open, close, pos, curr))
				star_insert_node(game, open, curr, pos);
	}
}

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

/*
 * this fuction is returning a ptr to the node with the smallest_cost
 * its also moving that node to close and calls the huristic function
 */
t_star_node	*star_get_smallest_cost(t_star_node **open, t_star_node **close, t_vec2 target) 
{
	t_star_node	*curr;
	int		small;
	int		h;
	t_star_node	*btemp;
	t_star_node	*temp;
	
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
	if (btemp == NULL)
		*open = temp->next;
	else
		btemp->next = temp->next;
	temp->next = *close;
	*close = temp;
	return temp;
}


/*
 * A* ALGORITHYM 
 * populates a path from the starting vector adding nodes for each of its neibours
 * then checks which of those neibours huristic and moves made from start_cost
 * is the smallest and moves to that neiboring node and repeats if two are tide for 
 * the smallest it will then choose the smallest huristic cost which is the distance
 * from current node to target. can possible change the t_vec2 struct to store ints
 * or something smaller then can get rig of the cast of int from double
 *
 * this function returns a malloc array of vector that does need to be freed
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
	star_insert_node(game, &open, NULL, start);
	while (open != NULL)
	{
		smallest = star_get_smallest_cost(&open, &close, target);
		if ((int)smallest->pos.x == (int)target.x && (int)smallest->pos.y == (int)target.y)
			break;
		star_get_neighbours(game, smallest, &open, &close);
	}
	if (open == NULL)
	{
		star_deallocate_node(&open);
		star_deallocate_node(&close);
		return (NULL);
	}
	return (star_construct_path(smallest, &open, &close));
}
