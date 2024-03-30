/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_func_door_setup.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 18:56:18 by kmordaun          #+#    #+#             */
/*   Updated: 2024/03/30 15:39:04 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "render.h"
#include "state.h"
#include "csv.h"
#include "vectorconv.h"

char    *ft_strcpy(char *s1, char *s2)
{
	int i;
 
	i = -1;
	while (s2[++i])
		s1[i] = s2[i];
	s1[i] = s2[i];
	return (s1);
}

/*
 * NAME,TEXTURE,XPOS,YPOS,SPEED,CLOSED,LOCKED
 */
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
	wld->ent_2[wld->ent_count].target = NULL;
	e |= csv_next('u', &content, &wld->ent_2[wld->ent_count].speed);
	e |= csv_next('s', &content, &str);
	door = entity_create(wld, ENT_DOOR);
	door->closed = str[0] == 'C';
	door->speed = ENT_DOOR_SPEED * (1.0 / R_TFR);
	e |= csv_next('s', &content, &str);
	door->locked = str[0] == 'L';
	door->base.pos = v2itov2(pos);
	door->base.sprite = &wld->sprite[wld->sp_amount++];

	door->sprites[0] = door->base.sprite;
	door->sprites[0]->pos = v2itov2(pos);
	door->sprites[1] = &wld->sprite[wld->sp_amount++];
	door->sprites[1]->pos = v2itov2(pos);
	door->sprites[2] = &wld->sprite[wld->sp_amount++];
	door->sprites[2]->pos = v2itov2(pos);
	door->sprites[3] = &wld->sprite[wld->sp_amount++];
	door->sprites[3]->pos = v2itov2(pos);

	door->sprites[0]->tex = TEX_WINDOW;
	door->sprites[1]->tex = TEX_WINDOW;
	door->sprites[2]->tex = TEX_WINDOW;
	door->sprites[3]->tex = TEX_WINDOW;
	door->sprites[0]->visible = true;
	door->sprites[2]->visible = true;

	//door->sprites[0]->vsfb = true;
	// door->sprites[0]->vsfb = false;
	door->sprites[1]->vsfb = true;
	// door->sprites[2]->vsfb = true;
	door->sprites[3]->vsfb = true;
	doors++;
	wld->ent_count++;
	return (0);
}

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
