/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 08:56:06 by clovell           #+#    #+#             */
/*   Updated: 2024/05/04 02:01:08 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <math.h>
#include "entity.h"
#include "state.h"
#include "clmath.h"

/*					*PLAYER*
		 |						   |
		 |						   |
LL------ WL ------- DL DR -------  WR ------ RR
		 |			|	|		   |
		 |			|	|		   |
		 |			|	|		   |
		 |			FL FR		   |
		 |						   |

 flips 180 when player is on the other side
 LL left_left,   s* assign
 RR right_right, s* assigned

 DL door_left,  s* vs* assigned
 DR door_right, s* vs* assigned

 FL far_left,  s* vs* assigned
 FR far_right, s* vs* assigned
 
 WL wall_left, vs* assigned
 WR wall_right, vs* assigned

*/

#define INSET 0.085

/*	@brief Calculates the door model from the given door.
	@param game Game state reference
	@param d door entity
	@param m door model
	@param v Is facing east / west instead of north / south
*/
static void	door_model_update(t_game *game, t_door *d, t_door_model *m, bool v)
{
	const t_vec2	tang = v2new(!v, !!v);
	const t_vecd	pl = v2det(v2sub(v2sub(game->player.pos, \
	v2new(0.5, 0.5)), d->base.pos), tang) > 0;
	const t_vec2	face = v2muls(v2aclock(tang), 0.25 * ((pl * -1) + (!pl)));
	const t_vec2	pct = v2muls(v2divs(tang, 2), ((1 - d->pct) * 0.8 - INSET));
	const t_vec2	inset = v2muls(tang, INSET);

	m->door_left = v2sub(v2add(face, d->base.pos), pct);
	m->door_right = v2add(v2add(face, d->base.pos), pct);
	m->inset_left = v2sub(m->door_left, inset);
	m->inset_right = v2add(m->door_right, inset);
	m->far_left = v2sub(v2sub(m->door_left, v2muls(face, 2)), inset);
	m->far_right = v2add(v2sub(m->door_right, v2muls(face, 2)), inset);
	m->left_left = v2sub(m->door_left, v2muls(tang, INSET / 2 + 0.5));
	m->right_right = v2add(m->door_right, v2muls(tang, INSET / 2 + 0.5));
	m->wall_left = v2sub(v2add(d->base.pos, face), v2divs(tang, 2));
	m->wall_right = v2add(v2add(d->base.pos, face), v2divs(tang, 2));
}

/*	@brief Update the sprites for a given door entity.
	@param game Game state reference
	@param d door entity
	@param vert Is facing east / west instead of north / south
*/
static void	door_update_vis(t_game *game, t_door *d, bool vert)
{
	const t_vec2	dp = d->base.pos;
	t_door_model	m;

	m = (t_door_model){0};
	d->base.pos = v2add(d->base.pos, v2new(0.5, 0.5));
	door_model_update(game, d, &m, vert);
	d->base.pos = dp;
	d->sprites[0]->s1 = m.door_left;
	d->sprites[0]->s2 = m.left_left;
	d->sprites[0]->pos = d->sprites[0]->s1;
	d->sprites[0]->vs1 = d->sprites[0]->s1;
	d->sprites[0]->vs2 = m.wall_left;
	d->sprites[2]->s1 = m.door_right;
	d->sprites[2]->s2 = m.right_right;
	d->sprites[2]->pos = d->sprites[2]->s1;
	d->sprites[2]->vs1 = d->sprites[2]->s1;
	d->sprites[2]->vs2 = m.wall_right;
	d->sprites[1]->s1 = m.inset_left;
	d->sprites[1]->s2 = m.far_left;
	d->sprites[1]->pos = d->sprites[1]->s1;
	d->sprites[3]->s1 = m.inset_right;
	d->sprites[3]->s2 = m.far_right;
	d->sprites[3]->pos = d->sprites[3]->s1;
	d->sprites[3]->visible = d->pct < 1.0;
	d->sprites[1]->visible = d->pct < 1.0;
}

/*	@brief Determins whether a door is facing east / west vs north / south
	@param game Game state reference
	@param d door entity
	@returns Whether a door is facing 
	east / west (`true`) vs north / south (`false`)
*/
bool	door_is_vertical(t_door *door, t_game *game)
{
	const static t_vec2	directions[4] = {
	{.v = {0, -1}},
	{.v = {0, 1}},
	{.v = {-1, 0}},
	{.v = {1, 0}}};
	int					i;
	t_tile				*tile;

	i = -1;
	while (++i < 4)
	{
		tile = map_get_tile_refv(&game->world->map, \
		v2add(door->base.pos, directions[i]));
		if (tile == NULL)
			continue ;
		if (tile->type == FLOOR)
			return (i >= 2);
	}
	return (true);
}

void	ent_door_update(t_door *door, t_game *game)
{
	if (door->closed)
		door->pct += door->speed;
	else
		door->pct -= door->speed;
	door->pct = fclamp(0.2, 1.0, door->pct);
	printf("%d\n", door->closed);
	door_update_vis(game, door, door_is_vertical(door, game));
}
