/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_func_door_setup.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 18:56:18 by kmordaun          #+#    #+#             */
/*   Updated: 2024/05/04 01:48:07 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "render.h"
#include "state.h"
#include "events.h"

#include "csv.h"
#include "vectorconv.h"

static void	door_setup_sprites(t_door *door, t_world *wld)
{
	door->sprites[0] = &wld->sprite[wld->sp_amount++];
	door->sprites[1] = &wld->sprite[wld->sp_amount++];
	door->sprites[2] = &wld->sprite[wld->sp_amount++];
	door->sprites[3] = &wld->sprite[wld->sp_amount++];
	door->base.sprite = door->sprites[0];
	door->sprites[0]->pos = door->base.pos;
	door->sprites[0]->tex = TEX_DOOR;
	door->sprites[0]->uv = (t_uv){.offset.v = {.5, 0}, .scale.v = {.5, .927}};
	door->sprites[0]->visible = true;
	*door->sprites[1] = *door->sprites[0];
	*door->sprites[2] = *door->sprites[0];
	door->sprites[2]->uv = (t_uv){.offset.v = {.5, 0}, .scale.v = {-.5, .927}};
	*door->sprites[3] = *door->sprites[0];
	door->sprites[1]->uv = (t_uv){.offset.v = {.4, 10}, .scale.v = {.01, .8}};
	door->sprites[1]->vsfb = true;
	*door->sprites[3] = *door->sprites[1];
}

/*
 * NAME,TEXTURE,XPOS,YPOS,SPEED,CLOSED,LOCKED
 */
t_err	mod_gen_dr(char *content, int index, t_world *wld, t_map *map)
{
	t_mod_door_data		mod;
	t_door				*door;
	t_entity_2 *const	ent2 = &wld->ent_2[wld->ent_count];
	const int			found = ft_sescanf(content, "%N%s,%s,%u,%u,%u,%c,%c\v",
			sizeof(mod.name), &mod.name, &mod.tex,
			&mod.pos.x, &mod.pos.y, &mod.speed,
			&mod.closed, &mod.locked);
	(void)index;
	(void)wld;
	(void)map;
	if (found != 8 || mod.pos.x >= map->width \
					|| mod.pos.y >= map->height)
		return (1);
	*map_get_tile_ref(map, mod.pos.x, mod.pos.y) = (t_tile){
	.type = DOOR, .vis = -1 - (mod.closed == 'C'), .tex = TEX_DOOR};
	ft_strlcpy(ent2->name, mod.name, NAME_SIZE);
	ft_strcpy(ent2->ui_display_1, "PRESS 'E' TO INTERACT");
	ft_strcpy(ent2->ui_display_2, "LOCKED");
	ent2->ref_tile = map_get_tile_ref(map, mod.pos.x, mod.pos.y);
	door = (t_door *)entity_create(wld, ENT_DOOR);
	door->closed = mod.closed == 'C';
	door->locked = mod.locked == 'L';
	door->pct = door->closed;
	door->speed = ENT_DOOR_SPEED * (1.0 / R_TFR);
	door->base.pos = v2itov2(mod.pos);
	ent2->pos = door->base.pos;
	ent2->state_1 = door->closed;
	ent2->state_2 = door->locked;
	ent2->state_3 = false;
	ent2->ui_display = &ent2->ui_display_1;
	if (door->closed && door->locked)
	{
		ent2->ui_display = &ent2->ui_display_2;
		ent2->type = ET_DOOR_LOCKED;
	}
	if (door->closed && !door->locked)
		ent2->type = ET_DOOR_UNLOCKED;
	if (!door->closed)
		ent2->type = ET_DOOR_OPEN;
	ent2->entity = &door->base;
	door_setup_sprites(door, wld);
	ent2->handle = target_handle_door;
	wld->ent_count++;
	return (0);
}

/*
 * NAME,TEXTURE,ACCESSDOORNAMED,XPOS,YPOS,AUTOUNLOCKOPEN,GRABBEDBYPLAYER 
 */
t_err	mod_gen_ke(char *content, int index, t_world *wld, t_map *map)
{
	static int	keys = 0;
	char		str[CSV_LEN];
	t_err		e;

	e = csv_next('s', &content, &str);
	if (!e)
		ft_strlcpy(wld->keys[keys].name, str, NAME_SIZE);
	e |= csv_next('s', &content, &str);
	if (!e)
		ft_strlcpy(map->mods[index].content, str, MOD_CONTENT_MAX);
	e |= csv_next('s', &content, &str);
	if (!e)
		ft_strlcpy(wld->keys[keys].doorname, str, NAME_SIZE);
	e |= csv_next('u', &content, &wld->keys[keys].pos.x);
	e |= csv_next('u', &content, &wld->keys[keys].pos.y);
	e |= csv_next('s', &content, &str);
	if (!e)
		wld->keys[keys].collected = str[0] == 'C';
	keys++;
	return (e);
}
