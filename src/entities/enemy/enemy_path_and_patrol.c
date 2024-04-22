
#include "enemy.h"
#include "map.h"
#include "state.h"

/*
 * frees the current path and attempts to get a new A-star path
 */
void	enemy_update_path_to_target(t_game *game, t_enemy *enemy)
{
	if (enemy == NULL)
		return ;
	if (enemy->path != NULL)
		free(enemy->path);
	enemy->path = star_find_path(game, enemy->sprite_ref->pos, game->player.pos);
}

t_vec2	enemy_patrol_target(t_game *game, t_enemy *enemy)
{
	t_vec2	targets[4];
	int	i;
	float	x;
	float	y;

	x = (int)enemy->sprite_ref->pos.x + 0.5;
	y = (int)enemy->sprite_ref->pos.y + 0.5;
	i = mrand(&game->rand) % 4;
	targets[0] = v2new(x + 1, y);
	targets[1] = v2new(x, y + 1);
	targets[2] = v2new(x - 1, y);
	targets[3] = v2new(x, y - 1);
	while (i < 4)
	{
		if (game->world->map.tiles[(int)targets[i].x + (int)targets[i].y * game->world->map.width].vis == -1)
			break ;
		i++;
		if (i == 4)
			i = 0;
	}
	return (targets[i]);
}

void	enemy_traverse_path(t_game *game, t_enemy *enemy)
{
	t_vec2	target;
	double	dist;
	int	i;

	i = 0;
	if (enemy->path == NULL)
	{
		enemy->patrol_target = enemy_patrol_target(game, enemy);
		enemy->state = PATROL;
		return ;
	}
	if (enemy->path[enemy->p_index].x == -1 && enemy->path[enemy->p_index].y == -1)
	{
		dist = v2dist(enemy->sprite_ref->pos, game->player.pos);
		if (dist < 2.0)
			return ;
		enemy_update_path_to_target(game, enemy);
		enemy->p_index = 1;
	}
	if (enemy->path == NULL)
	{
		enemy->patrol_target = enemy_patrol_target(game, enemy);
		enemy->state = PATROL;
		return ;
	}
	if ((enemy_has_line_of_sight(game, enemy->sprite_ref->s1, game->player.pos)))
	{
		if (enemy_has_line_of_sight(game, enemy->sprite_ref->s2, game->player.pos))
		{
			enemy->state = TARGET_IN_SIGHT;
			return ;
		}
	}
	target = v2new((int)enemy->path[enemy->p_index].x + 0.5, (int)enemy->path[enemy->p_index].y + 0.5);
	dist = v2dist(enemy->sprite_ref->pos, target);
	if (enemy_move_to_target(game, enemy, target, game->player.pos))
		game->title.state = LOSE_SCREEN;
	if (dist < 0.01)
		enemy->p_index++;
}

void	enemy_patrol(t_game *game, t_enemy *enemy)
{
	double	dist;

	dist = v2dist(enemy->sprite_ref->pos, enemy->patrol_target);
	if (dist < 0.01 || dist > 3.5)
	{
		enemy_update_path_to_target(game, enemy);
		enemy->p_index = 1;
		if (enemy->path != NULL)
		{
			enemy->state = GO_PATH_TO_TARGET;
			return ;
		}
		enemy->patrol_target = enemy_patrol_target(game, enemy);
	}
	if (enemy_move_to_target(game, enemy, enemy->patrol_target, game->player.pos))
		game->title.state = LOSE_SCREEN;
}
