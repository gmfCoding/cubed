#include "state.h"
#include "a_star.h"

void    deallocate_node(t_star_node **node)
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

void    print_node(t_star_node **node)
{
        t_star_node *curr = *node;
	while (curr != NULL)
        {
                printf("%d   %d\n", (int)curr->pos.x, (int)curr->pos.y);
                curr = curr->next;
        }
}
void    move_node(t_star_node **node, t_star_node **dst)
{
        t_star_node  *temp;

        if (*node == NULL)
                return ;
        temp = *node;
        *node = (*node)->next;
        temp->next = *dst;
        *dst = temp;
}

void    star_move_node(t_star_node **node, t_star_node **dst)
{

	printf("temp before return = %d, %d and g_cost = %d\n", (int)(*node)->pos.x, (int)(*node)->pos.y, (*node)->g_cost);
        (*node)->next = *dst;
        *dst = *node;
}

void    insert_node_start(t_game *game, t_star_node **node, t_star_node *parent, t_vec2 pos)
{
        t_star_node *temp;
	printf("inserting node at pos x %d, y %d\n", (int)pos.x, (int)pos.y);	
	temp = malloc(sizeof(t_star_node));
        if (temp == NULL)
		return;
        temp->next = NULL;
	temp->parent = parent;
	temp->f_cost = 0;
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


int	star_not_in_list(t_star_node **open, t_star_node **close, t_vec2 pos, t_star_node *active)
{
	t_star_node *curr;


	curr = *close;
	while (curr != NULL)
	{
		if ((int)curr->pos.x == (int)pos.x && (int)curr->pos.y == (int)pos.y)
			return (0);
		curr = curr->next;
	}
	curr = *open;
	while (curr != NULL)
	{
		if ((int)curr->pos.x == (int)pos.x && (int)curr->pos.y == (int)pos.y)
		{
			if (((int)curr->pos.x == (int)active->pos.x || (int)curr->pos.y == (int)active->pos.y) && curr->g_cost > active->g_cost + 10)
				curr->g_cost = active->g_cost + 10;
			else if (((int)curr->pos.x != (int)active->pos.x && (int)curr->pos.y != (int)active->pos.y) && curr->g_cost > active->g_cost + 14)
				curr->g_cost = active->g_cost + 14;
			return (0);
		}
		curr = curr->next;
	}
	return (1);
}

void	star_get_neighbours(t_game *game, t_star_node *curr, t_star_node **open, t_star_node **close)
{//have to print out the nodes inserted and double check the math is correct
	int index;
	t_vec2 pos;
	index = game->world->map.width * curr->pos.y + curr->pos.x;
	if (game->world->map.tiles[index + 1].vis == -1)
	{
		pos = v2add(curr->pos, v2new(1, 0));
		printf("right1 x%f, y %f\n", pos.x, pos.y);
		if (star_not_in_list(open, close, pos, curr))
			insert_node_start(game, open, curr, pos);
	}
	if (game->world->map.tiles[index + game->world->map.width].vis == -1)
	{
		pos = v2add(curr->pos, v2new(0, 1));
		printf("down1 x%f, y %f\n", pos.x, pos.y);

		if (star_not_in_list(open, close, pos, curr))
			insert_node_start(game, open, curr, pos);
	}
	if (game->world->map.tiles[index - 1].vis == -1)
	{
		pos = v2sub(curr->pos, v2new(1, 0));
		printf("left1 x%f, y %f\n", pos.x, pos.y);
		if (star_not_in_list(open, close, pos, curr))
			insert_node_start(game, open, curr, pos);
	}
	if (game->world->map.tiles[index - game->world->map.width].vis == -1)
	{
		pos = v2sub(curr->pos, v2new(0, 1));
		printf("up1 x%f, y %f\n", pos.x, pos.y);
		if (star_not_in_list(open, close, pos, curr))
			insert_node_start(game, open, curr, pos);
	}
	if (game->world->map.tiles[index - game->world->map.width - 1].vis == -1 \
		&& (game->world->map.tiles[index - game->world->map.width].vis == -1 \
		|| game->world->map.tiles[index - 1].vis == -1))
	{

		pos = v2sub(curr->pos, v2new(1, 1));
		printf("topleft x%f, y %f\n", pos.x, pos.y);
		if (star_not_in_list(open, close, pos, curr))
			insert_node_start(game, open, curr, pos);
	}
	if (game->world->map.tiles[index - game->world->map.width + 1].vis == -1 \
		&& (game->world->map.tiles[index - game->world->map.width].vis == -1 \
		|| game->world->map.tiles[index + 1].vis == -1))
	{

		pos = v2add(curr->pos, v2new(1, -1));
		printf("topright x%f, y %f\n", pos.x, pos.y);
		if (star_not_in_list(open, close, pos, curr))
			insert_node_start(game, open, curr, pos);
	}
	if (game->world->map.tiles[index + game->world->map.width - 1].vis == -1 \
		&& (game->world->map.tiles[index + game->world->map.width].vis == -1 \
		|| game->world->map.tiles[index - 1].vis == -1))
	{
		pos = v2add(curr->pos, v2new(-1, 1));
		printf("bottomleft x%f, y %f\n", pos.x, pos.y);
		if (star_not_in_list(open, close, pos, curr))
			insert_node_start(game, open, curr, pos);
	}
	if (game->world->map.tiles[index + game->world->map.width + 1].vis == -1 \
		&& (game->world->map.tiles[index + game->world->map.width].vis == -1 \
		|| game->world->map.tiles[index + 1].vis == -1))
	{
		pos = v2add(curr->pos, v2new(1, 1));
		printf("bottomright x%f, y %f\n", pos.x, pos.y);
		if (star_not_in_list(open, close, pos, curr))
			insert_node_start(game, open, curr, pos);
	}

}

int	star_get_huristic(t_star_node *node, t_vec2 target)
{
	t_vec2	diff;

	diff = v2sub(node->pos, target);

	return (v2mag(diff) * 10);
}
/*
t_star_node	*star_get_smallest_cost(t_star_node **open, t_star_node **close, t_vec2 target)
{
	t_star_node	*curr;
	int		small;
	int		h;
	t_star_node	*btemp;
	t_star_node	*temp;

	curr = *open;
	small = curr->g_cost + star_get_huristic(curr, target);
	btemp = curr;
	temp = curr;
	if (curr->next == NULL)
		*open = NULL;
	while (curr->next != NULL)
	{
		h = star_get_huristic(curr->next, target);
		printf("H is = %d\n", h);
		if (h + curr->next->g_cost == small && h < star_get_huristic(temp, target))
			temp = temp;
		if (h + curr->next->g_cost < small)
		{
			small = h + curr->next->g_cost;
			btemp = curr;
			temp = curr->next;
		}
		curr = curr->next;
	}
	printf("temp before return = %d, %d and g_cost = %d\n", (int)temp->pos.x, (int)temp->pos.y, temp->g_cost);
	btemp->next = temp->next;
        temp->next = *close;
        *close = temp;

	//first time through the stack does not get moved properly
	return (temp);
}
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



t_vec2	*star_get_path(t_game *game, t_vec2 start, t_vec2 target)
{
	t_vec2 *path;
	t_star_node	*open;
	t_star_node	*close;
	t_star_node	*smallest;
	t_star_node	*curr;
	int		i;
	bool		target_found;

	target_found = false;
	i = 0;
	open = NULL;
	close = NULL;

	insert_node_start(game, &open, NULL, start);
//	move_node(&open, &close);
	while (target_found == false && open != NULL)
	{
		smallest = star_get_smallest_cost(&open, &close,target);
	//	star_move_node(&smallest, &close);
		if ((int)smallest->pos.x == (int)target.x && (int)smallest->pos.y == (int)target.y)
		{
			printf("targetfound\n");
			target_found = true;
			break ;
		}
		printf("in open\n");
	
		print_node(&open);
		star_get_neighbours(game, smallest, &open, &close);
	//	break ;
	}

	curr = smallest;
	while (curr != NULL)
	{
		i++;
		curr = curr->parent;
	}
	path = malloc(sizeof(t_vec2) * (i + 1));
	printf("i is = %d\n", i);
	if (path == NULL)
		return (NULL);
	path[i].x = -1;
	path[i].y = -1;
	printf("path-1 is %d , %d\n", (int)path[i].x, (int)path[i].y);
	while(smallest != NULL)
	{
		--i;
		path[i] = smallest->pos;
		printf("SMALLPATH = x %d , y %d\n", (int)path[i].x, (int)path[i].y);

		smallest = smallest->parent;
	}
//	printf("in open\n");
//	print_node(&open);
//	printf("in close\n");
//	print_node(&close);
	deallocate_node(&open);
	deallocate_node(&close);

	return (path);
}

















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
	
	path = star_get_path(game, start, end);
	while (path[i].x != -1  && path[i].y != -1)
	{
		printf("PATH = x %d , y %d\n", (int)path[i].x, (int)path[i].y);
		i++;
	}
	free(path);
}
