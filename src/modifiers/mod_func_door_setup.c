/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_func_door_setup.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 18:56:18 by kmordaun          #+#    #+#             */
/*   Updated: 2024/04/07 01:33:37 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "render.h"
#include "state.h"

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
	door->sprites[0]->tex = TEX_WINDOW;
	door->sprites[0]->uv = (t_uv){.offset = {0.5, 0}, .scale = {0.5, 1}};
	door->sprites[0]->visible = true;
	*door->sprites[1] = *door->sprites[0];
	*door->sprites[2] = *door->sprites[0];
	*door->sprites[3] = *door->sprites[0];
	door->sprites[1]->uv = (t_uv){.offset = {0.25, 0}, .scale = {0.5, 1}};
	door->sprites[1]->vsfb = true;
	*door->sprites[3] = *door->sprites[1];
}
/*
struct s_mod_door {

};

struct s_mod_door door;
int found = ft_sscanf("DR dooor01,./tex,10,25,6,C,L\n", "DR %s,%s,%u,%u,%u,%c,%c",
    &door.name,
    &door.tex,
    &door.pos.x,
    &door.pos.y,
    &door.locked,
    &door.closed
);

if (found != 7)
    return;

*/

/*
 * NAME,TEXTURE,XPOS,YPOS,SPEED,CLOSED,LOCKED
 *
t_err	mod_gen_dr(char *content, int index, t_world *wld, t_map *map)
{
	static int	doors = 0;
	char		str[CSV_LEN];
	t_err		e;
	t_vec2i		pos;
	t_door		*door;

	printf("mod door gen!\n");
	e = csv_next('s', &content, &str);
	ft_strlcpy(wld->ent_2[wld->ent_count].name, str, NAME_SIZE);
	e |= csv_next('s', &content, &str);
	e |= csv_next('u', &content, &pos.x);
	e |= csv_next('u', &content, &pos.y);
	pos.x--;
	if (e || pos.x >= map->width || pos.y >= map->height)
		return (1);
	*map_get_tile_ref(map, pos.x, pos.y) = (t_tile){
	.type = DOOR, .vis = -1, .tex = TEX_DOOR};
	ft_strcpy(wld->ent_2[wld->ent_count].ui_display_1, "PRESS 'E' TO INTERACT");
	ft_strcpy(wld->ent_2[wld->ent_count].ui_display_2, "LOCKED");
	wld->ent_2[wld->ent_count].ref_tile = map_get_tile_ref(map, pos.x, pos.y);
	e |= csv_next('u', &content, &wld->ent_2[wld->ent_count].speed);
	e |= csv_next('s', &content, &str);
	door = (t_door *)entity_create(wld, ENT_DOOR);
	door->closed = str[0] != 'C';
	door->percent = door->closed;
	wld->ent_2[wld->ent_count].state_1 = door->closed;
	door->speed = ENT_DOOR_SPEED * (1.0 / R_TFR);
	e |= csv_next('s', &content, &str);
	door->locked = str[0] == 'L';
	wld->ent_2[wld->ent_count].pos = v2itov2(pos);
	wld->ent_2[wld->ent_count].state_2 = door->locked;
	wld->ent_2[wld->ent_count].state_3 = false;
	if (door->closed && door->locked)
		wld->ent_2[wld->ent_count].type = ET_DOOR_LOCKED;
	if (door->closed && !door->locked)
		wld->ent_2[wld->ent_count].type = ET_DOOR_UNLOCKED;
	if (!door->closed)
		wld->ent_2[wld->ent_count].type = ET_DOOR_OPEN;
	door->base.pos = v2itov2(pos);
	wld->ent_2[wld->ent_count].entity = &door->base;
	door_setup_sprites(door, wld);
	doors++;
	printf("doorname is %s the door is type %d\n", wld->ent_2[wld->ent_count].name, wld->ent_2[wld->ent_count].type);

	wld->ent_count++;
	return (0);
}
*/


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

	mod.pos.x--;
	if (found != 8 || mod.pos.x >= map->width \
					|| mod.pos.y >= map->height)
		return (1);
	*map_get_tile_ref(map, mod.pos.x, mod.pos.y) = (t_tile){
	.type = DOOR, .vis = -1 - mod.closed == 'C', .tex = TEX_DOOR};
	ft_strlcpy(ent2->name, mod.name, NAME_SIZE);
	ft_strcpy(ent2->ui_display_1, "PRESS 'E' TO INTERACT");
	ft_strcpy(ent2->ui_display_2, "LOCKED");
	ent2->ref_tile = map_get_tile_ref(map, mod.pos.x, mod.pos.y);
	door = (t_door *)entity_create(wld, ENT_DOOR);
	door->closed = mod.closed == 'C';
	door->locked = mod.locked == 'L';
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
	wld->ent_count++;
	return (0);
}


// t_err	mod_gen_dr(char *content, int index, t_world *wld, t_map *map)
// {
// 	static int	doors = 0;
// 	char		str[CSV_LEN];
// 	t_err		e;
// 	t_vec2i		pos;

// 	printf("mod door gen!\n");
// 	e = csv_next('s', &content, &str);
	
// 	e |= csv_next('s', &content, &str);
// 	e |= csv_next('u', &content, &pos.x);
// 	e |= csv_next('u', &content, &pos.y);

	
// 	e |= csv_next('u', &content, &wld->ent_2[wld->ent_count].speed);
// 	e |= csv_next('s', &content, &str);
	
	
// 	return (0);
// }

/*
 * NAME,TEXTURE,ACCESSDOORNAMED,XPOS,YPOS,AUTOUNLOCKOPEN,GRABBEDBYPLAYER 
 */
t_err mod_gen_ke(char *content, int index, t_world *wld, t_map *map)
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

/*
	while (dr[0][++i] && i < NAME_SIZE)
		wld->ent->doors[dr_count].name[i] = dr[0][i];
	map->mods[index].content = ft_strdup(dr[1]);

	wld->ent->doors[dr_count].pos.x = ft_atoi(dr[2]);
	wld->ent->doors[dr_count].pos.y = ft_atoi(dr[3]);
	wld->ent->doors[dr_count].speed = ft_atoi(dr[4]);
	wld->ent->doors[dr_count].closed = (dr[5][0] == 'C') ? true : false;
	wld->ent->doors[dr_count].locked = (dr[6][0] == 'L') ? true : false;
*/
