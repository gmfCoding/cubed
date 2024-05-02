/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_go_to_target.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:55:06 by kmordaun          #+#    #+#             */
/*   Updated: 2024/05/02 20:47:20 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enemy.h"
#include "map.h"
#include "state.h"
#include "clmath.h"

void	enemy_adjust_step_volume(t_game *game, double dist)
{
	int		i;
	float	v_set;

	i = SFX_ESTEP01;
	v_set = fclamp(0.0, 0.8, (0.1 * (dist < 8.0)) + 0.1 * (8.0 - dist));
	while (i <= SFX_ESTEP03)
		set_sound_volume(game->app.sfx, i++, v_set);
}
/*
void	enemy_adjust_step_volume(t_game *game, \
	double dist)//enable this if you cant get volume working
{
	if (dist < 6.0)
		game->world->enemy->hear_steps = true;
	else
		game->world->enemy->hear_steps = false;
}
*/

//angle = v2x2ang(dir) - v2x2ang(v2norm(v2sub(player_pos, \
//	enemy->sprite_ref->pos)));//if we wanna rotate the other way 
int	enemy_move_to_target(t_game *game, t_enemy *enemy, \
	t_vec2 target, t_vec2 player_pos)
{
	t_vec2	dir;
	t_vec2	ep;
	double	dist;
	float	angle;

	dir = v2norm(v2sub(target, enemy->sprite_ref->pos));
	ep = v2norm(v2sub(player_pos, enemy->sprite_ref->pos));
	angle = atan2(ep.y, ep.x) - atan2(dir.y, dir.x);
	if (angle < 0)
		angle += M_TAU;
	enemy->angle_frame = fabs(angle) / M_TAU * 32;
	enemy->sprite_ref->pos.x += dir.x * (enemy->speed * 0.01);
	enemy->sprite_ref->pos.y += dir.y * (enemy->speed * 0.01);
	dist = v2dist(enemy->sprite_ref->pos, player_pos);
	enemy_adjust_step_volume(game, dist);
	if (dist < 1.1)
	{
		stop_all_sound(game->app.sfx);
		play_sound(game->app.sfx, SFX_HEARTBEAT, LOOP);
		return (1);
	}
	return (0);
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
	int		x;
	int		y;

	dir = v2norm(v2sub(end, start));
	dist = v2dist(end, start);
	i = 0;
	while (i < dist)
	{
		x = (int)(start.x + dir.x * i);
		y = (int)(start.y + dir.y * i);
		if (game->world->map.tiles[x + y * game->world->map.width].vis != -1)
			return (0);
		i += 0.5;
	}
	return (1);
}

void	enemy_target_in_sight(t_game *game, t_enemy *enemy)
{
	if (!(enemy_has_line_of_sight(game, \
		enemy->sprite_ref->s1, game->player.pos)))
	{
		enemy_update_path_to_target(game, enemy);
		enemy->p_index = 1;
		enemy->state = GO_PATH_TO_TARGET;
		return ;
	}
	if (!(enemy_has_line_of_sight(game, \
		enemy->sprite_ref->s2, game->player.pos)))
	{
		enemy_update_path_to_target(game, enemy);
		enemy->p_index = 1;
		enemy->state = GO_PATH_TO_TARGET;
		return ;
	}
	if (enemy_move_to_target(game, enemy, game->player.pos, game->player.pos))
		game->title.state = LOSE_SCREEN;
}
