/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_func_trigger_area.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:20:00 by kmordaun          #+#    #+#             */
/*   Updated: 2024/05/08 18:14:10 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "map.h"
#include "state.h"
#include "vectorconv.h"
#include "modifiers.h"

static t_err	setup_entity(t_world *world, t_mod_trigger_area *data, \
																t_entity_2 *ent)
{
	t_ent_trigger_area	*area;

	area = (t_ent_trigger_area *)entity_create(world, ENT_TRIGGER_AREA);
	if (area == NULL)
		return (1);
	area->base.pos = v2itov2(data->pos);
	area->enabled = data->active == 'O';
	if (data->watch == 'E')
		area->watch = DYN_ENT_ENEMY;
	else
		area->watch = DYN_ENT_PLAYER;
	area->manhattan = data->dist_mode == 'M';
	area->radius = data->radius / 100.0f;
	area->ent2 = ent;
	return (0);
}

t_handle_result	target_handle_trigger_area(t_game *game, t_entity_2 *area, \
					t_entity_2 *parent)
{
	(void)game;
	(void)parent;
	((t_ent_trigger_area *)area->entity)->enabled = true;
	return (TARGET_HANDLE_SUCCESS);
}

//if (entity_target_handle(game, area->ent2) == TARGET_HANDLE_FAILED)
//	printf("HOW HANDLE ERRROR\n"); // TODO: How handle error?
void	ent_trigger_area_update(t_ent_trigger_area *area, t_game *game)
{
	t_vec2	target_pos;
	float	distance;

	if (area->enabled == false)
		return ;
	if (area->watch == DYN_ENT_PLAYER)
		target_pos = game->player.pos;
	else if (game->world->enemy != NULL)
		target_pos = game->world->enemy->base.pos;
	else
		return ;
	printf("We here2?\n");
	target_pos = v2sub(target_pos, v2new(0.5, 0.5));
	if (area->manhattan)
		distance = v2distm(area->base.pos, target_pos);
	else
		distance = v2dist(area->base.pos, target_pos);
	printf("We here1 %f?\n", distance);
	if (distance < area->radius)
	{
		area->enabled = false;
		if (entity_target_handle(game, area->ent2) == TARGET_HANDLE_FAILED)
			printf("HOW HANDLE ERRROR\n");
	}
}

/*
 * NAME,TARGET,ACTIVE (O | C), XPOS, YPOS, RADIUS PCT, WATCH_MODE (P | E), 
 * DIST_MODE (M | E)
 * Radius Percent: 100 is 1 tile 150 would be 1.5 tiles
 * MASK: Player or Enemy
 * DIST_MODE: Manhattan distance or Euclidean
 */
t_err	mod_gen_ta(char *content, int index, t_world *world, t_map *map)
{
	t_mod_trigger_area	mod;
	t_entity_2 *const	ent2 = &world->ent_2[world->ent_count];
	const int			found = ft_sescanf(content, \
												"%N%s,%s,%c,%u,%u,%u,%c,%c\v",
			sizeof(mod.name), &mod.name, &mod.target,
			&mod.active, &mod.pos.x, &mod.pos.y, &mod.radius, &mod.watch, \
			&mod.dist_mode);

	(void)index;
	if (found != 9 || mod.pos.x >= map->width \
					|| mod.pos.y >= map->height)
		return (1);
	*ent2 = (t_entity_2){.type = ET_EMPTY};
	ft_strlcpy(ent2->name, mod.name, NAME_SIZE);
	ent2->target_names[0] = ft_strdup(mod.target);
	ent2->pos = v2itov2(mod.pos);
	ent2->handle = target_handle_trigger_area;
	if (setup_entity(world, &mod, ent2))
		return (1);
	world->ent_count++;
	return (0);
}
