/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 08:56:06 by clovell           #+#    #+#             */
/*   Updated: 2024/03/30 15:40:34 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <math.h>
#include "entity.h"
#include "state.h"
#include "map.h"
#include "clmath.h"
typedef void (*t_fn_entity_update)(t_entity *entity, t_game *game);

// void	ent_door_update(t_door *door, t_game *game)
// {
// 	t_vec2	pct;
// 	bool	vert;
// 	// if (door->closed)
// 	// 	door->percent += door->speed;
// 	// else
// 	// 	door->percent -= door->speed;
// 	// door->percent = fclamp(0.0, 1.0, door->percent);
// 	door->percent = 0.5;
// 	vert = map_get_tile_refv(&game->world->map, \
// 	v2add(door->base.pos, v2new(1, 0)))->type == FLOOR;
// 	door->base.sprite->pos = v2add(door->base.pos, v2new(0.5, 0));
// 	pct = v2new(0.5 * door->percent, 0);
// 	if (vert)
// 		pct = v2new(0, door->percent);
// 	door->base.sprite->s1 = v2add(door->base.sprite->pos, pct);
// 	door->base.sprite->s2 = door->base.sprite->pos;
// }

static void	door_update_vis(t_game *game, t_door *door, bool vert)
{
	const t_vec2	norm = v2new(!vert, !!vert);
	const t_vecd	pl = v2det(v2sub(v2sub(game->player.pos, \
	v2new(0.5, 0.5)), door->base.pos), norm) < 0;
	const t_vec2	face = v2muls(v2clock(norm), 0.25 * ((pl * -1) + (!pl)));
	t_vec2			pct;

	pct = v2muls(norm, 0.5);
	door->sprites[0]->pos = v2add(door->base.pos, v2add(v2clock(pct), face));
	door->sprites[2]->pos = v2add(v2add(door->base.pos, \
	v2add(v2clock(pct), face)), norm);
	pct = v2muls(pct, door->percent);
	door->sprites[0]->pos = v2add(door->sprites[0]->pos, pct);
	door->sprites[0]->s1 = door->sprites[0]->pos;
	door->sprites[0]->s2 = v2sub(door->sprites[0]->pos, v2divs(norm, 2));
	door->sprites[0]->vs1 = door->sprites[0]->s1;
	door->sprites[0]->vs2 = v2add(door->base.pos, v2add(v2clock(v2divs(norm, 2)), face));

	door->sprites[2]->pos = v2sub(door->sprites[2]->pos, pct);
	door->sprites[2]->s1 = door->sprites[2]->pos;
	door->sprites[2]->s2 = v2add(door->sprites[2]->pos, v2divs(norm, 2));
	door->sprites[2]->vs1 = door->sprites[2]->s1;
	door->sprites[2]->vs2 = v2add(v2add(door->base.pos, \
	v2add(v2clock(v2divs(norm, 2)), face)), norm);
	door->sprites[1]->pos = door->sprites[0]->s1;
	door->sprites[1]->s1 = door->sprites[0]->s1;
	door->sprites[1]->s2 = v2add(door->sprites[0]->s1, v2muls(v2rev(face), 2));
	door->sprites[3]->pos = door->sprites[2]->s1;
	door->sprites[3]->s1 = door->sprites[2]->s1;
	door->sprites[3]->s2 = v2add(door->sprites[2]->s1, v2muls(v2rev(face), 2));
	door->sprites[3]->visible = door->percent < 1.0;
	door->sprites[1]->visible = door->percent < 1.0;
}


// static void	door_update_vis(t_game *game, t_door *door, bool vert)
// {
// 	const t_vec2	norm = v2new(!vert, !!vert);
// 	const t_vecd	pl = v2det(v2sub(v2sub(game->player.pos, \
// 	v2new(0.5, 0.5)), door->base.pos), norm) < 0;
// 	const t_vec2	face = v2muls(v2clock(norm), 0.25 * ((pl * -1) + (!pl)));
// 	t_vec2			pct;

// 	pct = v2muls(norm, 0.5);
// 	door->sprites[0]->pos = v2add(door->base.pos, v2add(v2clock(pct), face));
// 	door->sprites[2]->pos = v2add(v2add(door->base.pos, \
// 	v2add(v2clock(pct), face)), norm);
// 	pct = v2muls(pct, door->percent);
// 	door->sprites[0]->s1 = v2add(door->sprites[0]->pos, pct);
// 	door->sprites[0]->s2 = door->sprites[0]->pos;
// 	door->sprites[1]->pos = door->sprites[0]->s1;
// 	door->sprites[1]->s1 = door->sprites[0]->s1;
// 	door->sprites[1]->s2 = v2add(door->sprites[0]->s1, v2muls(v2rev(face), 2));
// 	door->sprites[2]->s1 = v2sub(door->sprites[2]->pos, pct);
// 	door->sprites[2]->s2 = door->sprites[2]->pos;
// 	door->sprites[3]->pos = door->sprites[2]->s1;
// 	door->sprites[3]->s1 = door->sprites[2]->s1;
// 	door->sprites[3]->s2 = v2add(door->sprites[2]->s1, v2muls(v2rev(face), 2));
// 	door->sprites[3]->visible = door->percent < 1.0;
// 	door->sprites[1]->visible = door->percent < 1.0;
// }

void	ent_door_update(t_door *door, t_game *game)
{
	if (input_keydown(&game->input, KEY_LALT)) // TODO: Remove (debug)
		door->closed = !door->closed;
	if (door->closed)
		door->percent += door->speed;
	else
		door->percent -= door->speed;
	door->percent = fclamp(0.2, 1.0, door->percent);
	door_update_vis(game, door, map_get_tile_refv(&game->world->map, \
	v2add(door->base.pos, v2new(1, 0)))->type == FLOOR);
}

static const t_fn_entity_update	g_entity_updates[] = {
	[ENT_DOOR] = (void *)ent_door_update,
};

static const size_t	g_entity_sizes[] = {
	[ENT_DOOR] = sizeof(t_door),
	[ENT_ENEMY] = sizeof(t_enemy),
};

void	entity_update(t_game *game)
{
 	t_list	*lst;

	lst = game->world->entities;
	while (lst != NULL && lst->content != NULL)
	{
		g_entity_updates[((t_entity *)lst->content)->type](lst->content, game);
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
