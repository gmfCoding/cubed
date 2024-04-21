/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 08:56:06 by clovell           #+#    #+#             */
/*   Updated: 2024/04/21 15:43:01 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <math.h>
#include "entity.h"
#include "state.h"
#include "map.h"
#include "clmath.h"

// Function declarations
void	ent_task_orbit_update(t_ent_task_orbit *orbit, t_game *game);

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
	const t_vec2	p1 = v2clock(v2divs(tang, 2));
	t_vec2			out;

	out = v2muls(tang, 0.5);
	m->door_left = v2add(d->base.pos, v2add(v2clock(out), face));
	m->door_right = v2add(v2add(d->base.pos, v2add(v2clock(out), face)), tang);
	out = v2muls(out, d->percent);
	m->door_left = v2add(m->door_left, out);
	m->left_left = v2sub(m->door_left , v2divs(tang, 2));
	m->wall_left = v2add(d->base.pos, v2add(p1, face));
	m->door_right = v2sub(m->door_right, out);
	m->right_right = v2add(m->door_right, v2divs(tang, 2));
	m->wall_right = v2add(v2add(d->base.pos, v2add(p1, face)), tang);
	m->far_left = v2add(m->door_left, v2muls(v2rev(face), 2));
	m->far_right = v2add(m->door_right, v2muls(v2rev(face), 2));
}

/*	@brief Update the sprites for a given door entity.
	@param game Game state reference
	@param d door entity
	@param vert Is facing east / west instead of north / south
*/
static void	door_update_vis(t_game *game, t_door *d, bool vert)
{
	t_door_model	m;

	m = (t_door_model){0};
	door_model_update(game, d, &m, vert);
	d->sprites[0]->pos = m.door_left;
	d->sprites[0]->s1 = m.door_left;
	d->sprites[0]->s2 = m.left_left;
	d->sprites[0]->vs1 = m.door_left;
	d->sprites[0]->vs2 = m.wall_left;
	d->sprites[2]->pos = m.door_right;
	d->sprites[2]->s1 = m.door_right;
	d->sprites[2]->s2 = m.right_right;
	d->sprites[2]->vs1 = m.door_right;
	d->sprites[2]->vs2 = m.wall_right;
	d->sprites[1]->pos = d->sprites[0]->s1;
	d->sprites[1]->s1 = d->sprites[0]->s1;
	d->sprites[1]->s2 = m.far_left;
	d->sprites[3]->pos = d->sprites[2]->s1;
	d->sprites[3]->s1 = d->sprites[2]->s1;
	d->sprites[3]->s2 = m.far_right;
	d->sprites[3]->visible = d->percent < 1.0;
	d->sprites[1]->visible = d->percent < 1.0;
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
	{0, -1},
	{0, 1},
	{-1, 0},
	{1, 0}};
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
	int	vis;

	if (door->closed)
		door->percent += door->speed;
	else
		door->percent -= door->speed;
	door->percent = fclamp(0.2, 1.0, door->percent);
	door_update_vis(game, door, door_is_vertical(door, game));
}

static const t_fn_entity_update	g_entity_updates[] = {
	[ENT_DOOR] = (void *)ent_door_update,
	[ENT_ENEMY] = (void *)NULL,
	[ENT_TASK_ORBIT] = (void *)ent_task_orbit_update,
};

static const size_t	g_entity_sizes[] = {
	[ENT_DOOR] = sizeof(t_door),
	[ENT_ENEMY] = sizeof(t_enemy),
	[ENT_TASK_ORBIT] = sizeof(t_ent_task_orbit),
};

void	entity_update(t_game *game)
{
	t_list				*lst;
	t_fn_entity_update	fn;

	lst = game->world->entities;
	while (lst != NULL && lst->content != NULL)
	{
		fn = g_entity_updates[((t_entity *)lst->content)->type];
		if (fn)
			fn(lst->content, game);
		lst = lst->next;
	}
}

t_entity	*entity_create(t_world *world, t_entity_type type)
{
	void	*const data = malloc(g_entity_sizes[type]);

	ft_lstadd_front(&world->entities, ft_lstnew(data));
	*(t_entity *)data = (t_entity){.type = type, .pos = v2new(0, 0), 0};
	return (data);
}
