/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_func_place_img.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 20:47:31 by kmordaun          #+#    #+#             */
/*   Updated: 2024/05/08 16:37:07 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "vectorconv.h"
#include "modifier_data.h"
#include "state.h"
#include "input.h"

void	display_placed_img(t_game *game)
{
	if (game->show_img == true)
	{
		texture_blit(game->textures[game->event_img->value], \
								game->rt0, game->event_img->pos);
		game->player.state = CANT_MOVE;
		if (input_keydown(&game->input, KEY_ENTER) \
			|| input_keydown(&game->input, KEY_E) \
			|| input_keydown(&game->input, KEY_SPACE) \
			|| input_keydown(&game->input, MB_LEFT))
		{
			game->show_img = false;
			play_sound(game->app.sfx, SFX_SELECTION, PLAY);
			game->event_img->state_3 = false;
			game->event_img = NULL;
			game->player.state = CAN_MOVE;
		}
		if (game->fpsc % 30 > 15)
			texture_blit(game->textures[TEX_UI_INTERACT_BRIGHT], \
								game->rt0, v2new(SCR_WIDTH / 2 - 60, 800));
		else
			texture_blit(game->textures[TEX_UI_INTERACT_DUL], \
								game->rt0, v2new(SCR_WIDTH / 2 - 60, 800));
	}
}

t_handle_result	target_handle_image_place(t_game *game, t_entity_2 *self, \
															t_entity_2 *parent)
{
	(void)parent;
	(void)game;
	if (self->state_3 == true)
	{
		game->show_img = true;
		game->event_img = self;
	}
	return (TARGET_HANDLE_SUCCESS);
}

/*
 * NAME,TARGET,IMAGE_INDEX,XPOS,YPOS
 */
t_err	mod_gen_pi(char *content, int index, t_world *world, t_map *map)
{
	t_mod_placeimg_data	mod;
	const int			found = ft_sescanf(content, "%N%s,%s,%u,%u,%u\v",
			sizeof(mod.name), &mod.name, &mod.target, &mod.img_i,
			&mod.pos.x, &mod.pos.y);

	(void)map;
	(void)index;
	if (found != 6)
		return (1);
	world->ent_2[world->ent_count] = (t_entity_2){0};
	ft_strlcpy(world->ent_2[world->ent_count].name, mod.name, NAME_SIZE);
	world->ent_2[world->ent_count].target_names[0] = ft_strdup(mod.target);
	world->ent_2[world->ent_count].pos = v2itov2(mod.pos);
	world->ent_2[world->ent_count].value = mod.img_i;
	world->ent_2[world->ent_count].handle = &target_handle_image_place;
	world->ent_2[world->ent_count].state_3 = true;
	world->ent_count++;
	return (0);
}
/*
t_err	mod_gen_al(char *content, int index, t_world *world, t_map *map)
{
	int	i;
	char	**al;
	int	x;
	int	y;

	i = -1;
	al = ft_split(content, ',');
	x = ft_atoi(al[3]) - 1;
	y = ft_atoi(al[4]);
	while (al[0][++i] && i < NAME_SIZE)
		world->ent_2[world->ent_count].name[i] = al[0][i];
	world->ent_2[world->ent_count].target = NULL;
	if (ft_strcmp(al[1], "NULL") != 0)
		world->ent_2[world->ent_count].target =	mod_search_name(world, al[1]);
	ft_strlcpy(map->mods[index].content, content, MOD_CONTENT_MAX);
	world->ent_2[world->ent_count].pos = v2new(x, y);
	world->ent_2[world->ent_count].ref_tile = 
	&map->tiles[y * (map->width + x) - 1];
		world->ent_2[world->ent_count].speed = ft_atoi(al[5]);
	if (al[2][0] == 'H')
		world->ent_2[world->ent_count].type = ET_ALERT_HIGH;
	if (al[2][0] == 'O')
		world->ent_2[world->ent_count].type = ET_ALERT_OFF;
	if (al[2][0] == 'M')
		world->ent_2[world->ent_count].type = ET_ALERT_MEDIUM;
	world->ent_count++;
	free_str_array(al);
	return (0);
}
*/
