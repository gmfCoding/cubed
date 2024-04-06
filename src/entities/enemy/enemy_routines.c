#include "enemy.h"
# include "map.h"
# include "state.h"
# include "clmath.h"
# include "cubed.h"
# include <math.h>

/*
 * are function used to update the tiles that have the enemy
 * sprite image in it the function can be made better we current
 * decrease the sp_count(sprite count) in the tile no matter what
 * this could be problematic and made better
 */
void	enemy_update_sp_tile_count(t_game *game, t_enemy *enemy)
{
	// if ((int)enemy->sprite_ref->s1.x != enemy->old_pos[1].x || (int)enemy->sprite_ref->s1.y != enemy->old_pos[1].y)
	// {
	// 	game->world->map.tiles[enemy->old_pos[1].x + enemy->old_pos[1].y * game->world->map.width].sp_count--;
	// 	if (game->world->map.tiles[(int)enemy->sprite_ref->s1.x + (int)enemy->sprite_ref->s1.y * game->world->map.width].vis == -1)
	// 		game->world->map.tiles[(int)enemy->sprite_ref->s1.x + (int)enemy->sprite_ref->s1.y * game->world->map.width].sp_count++;
	// 	enemy->old_pos[1].x = (int)enemy->sprite_ref->s1.x;
	// 	enemy->old_pos[1].y = (int)enemy->sprite_ref->s1.y;
	// }
	// if ((int)enemy->sprite_ref->s2.x != enemy->old_pos[2].x || (int)enemy->sprite_ref->s2.y != enemy->old_pos[2].y)
	// {
	// 	game->world->map.tiles[enemy->old_pos[2].x + enemy->old_pos[2].y * game->world->map.width].sp_count--;
	// 	if (game->world->map.tiles[(int)enemy->sprite_ref->s2.x + (int)enemy->sprite_ref->s2.y * game->world->map.width].vis == -1)
	// 		game->world->map.tiles[(int)enemy->sprite_ref->s2.x + (int)enemy->sprite_ref->s2.y * game->world->map.width].sp_count++;
	// 	enemy->old_pos[2].x = (int)enemy->sprite_ref->s2.x;
	// 	enemy->old_pos[2].y = (int)enemy->sprite_ref->s2.y;
	// }
	// if ((int)enemy->sprite_ref->pos.x != enemy->old_pos[0].x || (int)enemy->sprite_ref->pos.y != enemy->old_pos[0].y)
	// {
	// 	game->world->map.tiles[enemy->old_pos[0].x + enemy->old_pos[0].y * game->world->map.width].sp_count--;
	// 	if (game->world->map.tiles[(int)enemy->sprite_ref->pos.x + (int)enemy->sprite_ref->pos.y * game->world->map.width].vis == -1)
	// 		game->world->map.tiles[(int)enemy->sprite_ref->pos.x + (int)enemy->sprite_ref->pos.y * game->world->map.width].sp_count++;
	// 	enemy->old_pos[0].x = (int)enemy->sprite_ref->pos.x;
	// 	enemy->old_pos[0].y = (int)enemy->sprite_ref->pos.y;
	// }
}

/*
 * animates the enemy the speed of the animation should be adjusted
 * based on platform and could use a define instead or set through
 * the modifiers we have a game fpsc counter which is used for all
 * game animations we modul it by 4 meaning if it is dividable by 
 * 4 we enter the loop and change the animation frame coz we only want 
 * 1 frame past the previous frame we divide fpsc by the animation speed
 * the angle frame is used to determin which angled animation we wanna view
 * and we times that by the frame to get the same framecount we are on but
 * on that angle
 */
void	enemy_animate(t_game *game, t_enemy *enemy)
{
	int	animation_frame;
	int	texture_index;
	int	animation_speed;

	animation_speed = 4;
	if (game->fpsc % animation_speed == 0)
	{
		animation_frame = game->fpsc / animation_speed;
		texture_index = TEX_ENEMY_START + (animation_frame % 18);
		enemy->sprite_ref->tex = enemy->angle_frame * 18 + texture_index;
	}
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
	if (enemy == NULL)
		return ;
	if (enemy->state == NOT_ACTIVE)
		return ;
	sprite_rotate(game, enemy->sprite_ref, game->player.dir);
	//enemy_update_sp_tile_count(game, enemy);
	enemy_animate(game, enemy);
	if (enemy->state == TARGET_IN_SIGHT)
		enemy_target_in_sight(game, enemy);
	else if (enemy->state == GO_PATH_TO_TARGET)
		enemy_traverse_path(game, enemy);
	else if (enemy->state == PATROL)
		enemy_patrol(game, enemy);
}
