
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
 * adds node in up/down/left/right pos from current.pos
 */
void star_check_cardinal_neighbors(t_game *game, t_star_node *curr, t_star_node **open, t_star_node **close)
{
    const int deltas[][2] = DELTAS;
    int i = -1;

    while (++i < DELTAS_LEN)
    {
        int index;
        t_vec2 pos;

        index = game->world->map.width * curr->pos.y + curr->pos.x;
        pos.x = curr->pos.x + deltas[i][0];
        pos.y = curr->pos.y + deltas[i][1];

        if (pos.x >= 0 && pos.x < game->world->map.width && pos.y >= 0 && pos.y < game->world->map.height &&
            game->world->map.tiles[(int)pos.y * game->world->map.width + (int)pos.x].vis == -1 &&
            star_not_in_list(open, close, pos, curr))
        {
            star_insert_node(game, open, curr, pos);
        }
    }
}

/*
 * adds nodes on the corners around current.pos this will also check to make sure at leased
 * one cardinal neighbors is not a wall, if they are both walls it will not create the node
 */
void star_check_diagonal_neighbors(t_game *game, t_star_node *curr, t_star_node **open, t_star_node **close)
{
	int	i; 
	int	index;
	t_vec2	pos;

	i = -1;
	while (++i < 4)
	{
		index = game->world->map.width * curr->pos.y + curr->pos.x;
		if ((i == 0 && game->world->map.tiles[index - game->world->map.width - 1].vis == -1 \
			&& (game->world->map.tiles[index - game->world->map.width].vis == -1 || game->world->map.tiles[index - 1].vis == -1)) \
			|| (i == 1 && game->world->map.tiles[index - game->world->map.width + 1].vis == -1 \
			&& (game->world->map.tiles[index - game->world->map.width].vis == -1 || game->world->map.tiles[index + 1].vis == -1)) \
			|| (i == 2 && game->world->map.tiles[index + game->world->map.width - 1].vis == -1 \
			&& (game->world->map.tiles[index + game->world->map.width].vis == -1 || game->world->map.tiles[index - 1].vis == -1)) \
			|| (i == 3 && game->world->map.tiles[index + game->world->map.width + 1].vis == -1 \
			&& (game->world->map.tiles[index + game->world->map.width].vis == -1 || game->world->map.tiles[index + 1].vis == -1)))
		{
			pos.x = curr->pos.x + ((i % 2 == 0) ? -1 : 1);
			pos.y = curr->pos.y + ((i < 2) ? -1 : 1);
			if (star_not_in_list(open, close, pos, curr))
				star_insert_node(game, open, curr, pos);
		}
	}
}
/*
void star_get_neighbors(t_game *game, t_star_node *curr, t_star_node **open, t_star_node **close)
{
    star_check_cardinal_neighbors(game, curr, open, close);
    star_check_diagonal_neighbors(game, curr, open, close);
}
*/
/*
 * this function allows movement through corner to corner 
 * which should not be allowed in our situation but it is a nice function
 */

void	star_get_neighbors(t_game *game, t_star_node *curr, t_star_node **open, t_star_node **close)
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

