#include "enemy.h"
#include "map.h"
#include "state.h"

double v2dist(t_vec2 a, t_vec2 b)
{
	double dx;
	double dy;

	dx = b.x - a.x;
	dy = b.y - a.y;
	return (sqrt(dx * dx + dy * dy));
}

unsigned int custom_rand(unsigned int seed)
{
	seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
	return (seed);
}

t_vec2	enemy_calculate_direction(t_vec2 enemy_pos, t_vec2 target)
{
	double	magnitude;
	t_vec2	dir;

	dir.x = target.x - enemy_pos.x;
	dir.y = target.y - enemy_pos.y;
	magnitude = sqrt(dir.x * dir.x + dir.y * dir.y);
	dir.x /= magnitude;
	dir.y /= magnitude;
	return (dir);
}

void	enemy_move_to_target(t_enemy *enemy, t_vec2 target)
{
	t_vec2	dir;

	dir = enemy_calculate_direction(enemy->sprite_ref->pos, target);
	enemy->sprite_ref->pos.x += dir.x * enemy->speed;
	enemy->sprite_ref->pos.y += dir.y * enemy->speed;
}

t_vec2	enemy_patrol_target(t_game *game, t_enemy *enemy)
{
	t_vec2	targets[4];
	int	i;
	float	x;
	float	y;

	x = (int)enemy->sprite_ref->pos.x + 0.5;
	y = (int)enemy->sprite_ref->pos.y + 0.5;
	i = custom_rand((int)game->player.pos.x * (int)game->player.pos.y) % 4;
	targets[0] = v2new(x + 1, y);
	targets[1] = v2new(x, y + 1);
	targets[2] = v2new(x - 1, y);
	targets[3] = v2new(x, y - 1);
	printf("our rand number = %d\n", i);
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

/*
 * normally takes in the s1 ans s2 which is the enemy sprits left
 * and right sides position and the end is the player position
 * i use a double as an index on walk the direction and check for walls
 */
int	enemy_has_line_of_sight(t_game *game, t_vec2 start, t_vec2 end)
{
	t_vec2	dir;
	double	dist;
	double	i;
	int	x;
	int	y;

	dir = enemy_calculate_direction(start, end);
	dist = v2dist(end, start);
	i = 0;
	while (i < dist)
	{
		x = (int)(start.x + dir.x * i);
		y = (int)(start.y + dir.y * i);
		if (game->world->map.tiles[x + y * game->world->map.width].vis != -1)
			if (game->world->map.tiles[x + y * game->world->map.width].sp_count == 0)
				return (0);
		i += 0.5;
	}
	return (1);
}

/*
 * frees the current path and attempts to get a new A-star path
 */
void	enemy_update_path_to_target(t_game *game, t_enemy *enemy)
{
	if (enemy->path != NULL)
		free(enemy->path);
	enemy->path = star_find_path(game, enemy->sprite_ref->pos, game->player.pos);
}

/*
 * are function used to update the tiles that have the enemy
 * sprite image in it the function can be made better we current
 * decrease the sp_count(sprite count) in the tile no matter what
 * this could be problematic and made better
 */
void	enemy_update_sp_tile_count(t_game *game, t_enemy *enemy)
{
	if ((int)enemy->sprite_ref->s1.x != enemy->old_pos[1].x || (int)enemy->sprite_ref->s1.y != enemy->old_pos[1].y)
	{
		game->world->map.tiles[enemy->old_pos[1].x + enemy->old_pos[1].y * game->world->map.width].sp_count--;
		if (game->world->map.tiles[(int)enemy->sprite_ref->s1.x + (int)enemy->sprite_ref->s1.y * game->world->map.width].vis == -1)
			game->world->map.tiles[(int)enemy->sprite_ref->s1.x + (int)enemy->sprite_ref->s1.y * game->world->map.width].sp_count++;
		enemy->old_pos[1].x = (int)enemy->sprite_ref->s1.x;
		enemy->old_pos[1].y = (int)enemy->sprite_ref->s1.y;
	}
	if ((int)enemy->sprite_ref->s2.x != enemy->old_pos[2].x || (int)enemy->sprite_ref->s2.y != enemy->old_pos[2].y)
	{
		game->world->map.tiles[enemy->old_pos[2].x + enemy->old_pos[2].y * game->world->map.width].sp_count--;
		if (game->world->map.tiles[(int)enemy->sprite_ref->s2.x + (int)enemy->sprite_ref->s2.y * game->world->map.width].vis == -1)
			game->world->map.tiles[(int)enemy->sprite_ref->s2.x + (int)enemy->sprite_ref->s2.y * game->world->map.width].sp_count++;
		enemy->old_pos[2].x = (int)enemy->sprite_ref->s2.x;
		enemy->old_pos[2].y = (int)enemy->sprite_ref->s2.y;
	}
	if ((int)enemy->sprite_ref->pos.x != enemy->old_pos[0].x || (int)enemy->sprite_ref->pos.y != enemy->old_pos[0].y)
	{
		game->world->map.tiles[enemy->old_pos[0].x + enemy->old_pos[0].y * game->world->map.width].sp_count--;
		if (game->world->map.tiles[(int)enemy->sprite_ref->pos.x + (int)enemy->sprite_ref->pos.y * game->world->map.width].vis == -1)
			game->world->map.tiles[(int)enemy->sprite_ref->pos.x + (int)enemy->sprite_ref->pos.y * game->world->map.width].sp_count++;
		enemy->old_pos[0].x = (int)enemy->sprite_ref->pos.x;
		enemy->old_pos[0].y = (int)enemy->sprite_ref->pos.y;
	}
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
		{
			printf("player dead\n");
			//kill the player
			return ;
		}
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
	enemy_move_to_target(enemy, target);
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
		printf("patrol_target = %f, %f\n", enemy->patrol_target.x, enemy->patrol_target.y);
	}
	enemy_move_to_target(enemy, enemy->patrol_target);
}

void	enemy_target_in_sight(t_game *game, t_enemy *enemy)
{
	if (!(enemy_has_line_of_sight(game, enemy->sprite_ref->s1, game->player.pos)))
	{
		if (!(enemy_has_line_of_sight(game, enemy->sprite_ref->s2, game->player.pos)))
		{
			enemy_update_path_to_target(game, enemy);
			enemy->p_index = 1;
			enemy->state = GO_PATH_TO_TARGET;
			return ;
		}
	}
	enemy_move_to_target(enemy, game->player.pos);
}

/*
 * the enemy will look for a valid path while in patrol
 * if the path return for a_star in NULL it will continue
 * to patrol if there is a path the enemy will change to
 * GO_PATH_TO_TARGET where it traveres the a_star path
 * if while traversing both the s1 and s2 of the enemy
 * texture have a clear line of sight to the player
 * the enemy state will change to TARGET_IN_SIGHT and move
 * directly towards the player and check if the player is still
 * in line of sight when it is not it will go back to 
 * GO_PATH_TO_TARGET
 */
void	enemy_routine(t_game *game, t_enemy *enemy)
{
	if (enemy->state == NOT_ACTIVE)
		return ;
	enemy_update_sp_tile_count(game, enemy);
	if (enemy->state == TARGET_IN_SIGHT)
		enemy_target_in_sight(game, enemy);
	else if (enemy->state == GO_PATH_TO_TARGET)
		enemy_traverse_path(game, enemy);
	else if (enemy->state == PATROL)
		enemy_patrol(game, enemy);
}
