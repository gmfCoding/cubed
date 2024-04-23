/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifier_setup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:24:36 by kmordaun          #+#    #+#             */
/*   Updated: 2024/04/18 17:21:48 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "state.h"
#include "modifiers.h"
/*
 * ADD MODIFIERS 
 * here is where you can add modifiers or anything addition to the game
 * when adding a new modifier please make changes to
 * g_mapsymbols and g_mapfuncs and add any structs or entities to modifiers.h
 * call the function like this "see modifiers.h for details"
 * t_err	mod_gen_"__"(char *content, int index, t_world *world, t_map *map);
 * add detail of how to write modifier above function for instance
 * NAME,TEXTURE,XPOS,YPOS,SPEED,CLOSED,LOCKED,VERTICLE 
 * DR door01,/assets/debug.xpm,25,10,1,C,L
 * //more details here
 * ELEMENT_TYPE	= DR			"calls the fucntion"
 * NAME 	= door01		"identify the door in game"
 * TEXTURE	= /assets/debug.xpm	"add a custom tecture to door"
 * XPOS		= 25			"door X position on map"
 * YPOS		= 10			"door Y position on map"
 * SPEED	= 1			"door speed multipler"
 * CLOSED	= C			"the state of the door"
 * LOCKED	= L			"if the door is locked or not"
 *
 * EXAMPE OF ELEMENTS IN .CUB FILE 
 * NO ./assets/debug.xpm
 * SO ./assets/debug.xpm
 * WE ./assets/debug.xpm
 * EA ./assets/debug.xpm
 * F 225,100,0
 * C 223,20,0 
 * DR door01,/assets/debug.xpm,25,10,1,C,L
 * KE key01,/assets/debug.xpm,door01,26,10,A,N
 * //the rest of the map here//
 *
 */
char *const			g_mapsymbols[] = {
	"NO",
	"SO",
	"WE",
	"EA",
	"F ",
	"C " ,
	"DR",
	"KE",
	"AL",
	"MM",
	"EN",
	"WN", // WINDOW
	"WL", // WINDOW LINE (really box)
	"FL",
	"GO", // Or-Gate / Redirect
	"GA", // And-Gate
	"GM", // Multi Gate Splitter
};

t_ex_action const	g_mapfuncs[] = {
	&mod_gen_no,
	&mod_gen_so,
	&mod_gen_we,
	&mod_gen_ea,
	&mod_gen_f,
	&mod_gen_c,
	&mod_gen_dr,
	&mod_gen_ke,
	&mod_gen_al,
	&mod_gen_mm,
	&mod_gen_en,
	&mod_gen_wn,
	&mod_gen_wl,
	&mod_gen_fl,
	&mod_gen_go,
	&mod_gen_ga,
	&mod_gen_gm,
};

t_err modifier_setup(t_list *raw_map_file, t_map *map, t_world *world)
{
	t_list	*curr;
	char	*str;
	int		i;
	int		index;

	index = 0;
	curr = raw_map_file;
	while (curr != NULL && curr->content != NULL)
	{
		str = (char *)curr->content;
		remove_spaces(str);
		i = -1;
		while ((size_t)++i < (sizeof(g_mapsymbols) / sizeof(g_mapsymbols[0])))
		{
			if (ft_strncmp(g_mapsymbols[i], str, \
			strlen_nl(g_mapsymbols[i])) == 0)
				if ((g_mapfuncs[i])(str + (strlen_nl(g_mapsymbols[i]) \
					+ 1), index++, world, map))
					return (ft_putstr_fd(g_mapsymbols[i], STDERR_FILENO), 1);
		}
		curr = curr->next;
	}
	return (0);
}

t_mm_tile	*mmap_find_tile(t_game *game, t_vec2 pos)
{
	int	i;

	i = -1;
	while (game->mmap.tiles[++i].img != NULL)
		if (game->mmap.tiles[i].ref == (pos.y * game->world->map.width) + pos.x)
			return (&game->mmap.tiles[i]);
	return (NULL);
}

void	modifier_after(t_game *game)
{
	t_world *const	w = game->world;
	int				i;
	int				j;
	t_list			*ent_iter;
	t_entity		*ent_curr;

	i = -1;
	while ((size_t)++i < w->ent_count)
	{
	//	printf("%s : %p\n", w->ent_2[i].name, &w->ent_2[i]);
		j = -1;
		while (++j < EVENT_ENT_MAX_TARGETS)
		{
			if (w->ent_2[i].target_names[j] && w->ent_2[i].target_names[j][0] && ft_strcmp(w->ent_2[i].target_names[j], "NULL") != 0)
				w->ent_2[i].targets[j] = mod_search_name(w, w->ent_2[i].target_names[j]);
		//	printf("\t%d: %p / %s\n", j, w->ent_2[i].targets[j], w->ent_2[i].target_names[j]);
		//	printf("freein: %p\n", w->ent_2[i].target_names[i]);
			if (w->ent_2[i].target_names[j] != NULL)
				free(w->ent_2[i].target_names[j]);
		}
		w->ent_2[i].ref_mm_tile = mmap_find_tile(game, w->ent_2[i].pos);
	}
	ent_iter = game->world->entities;
	while (ent_iter != NULL)
	{
		if (ent_iter->content != NULL)
		{
			ent_curr = (t_entity *)ent_iter->content;
			ent_curr->mm_tile = mmap_find_tile(game, ent_curr->pos);	
		}
		ent_iter = ent_iter->next;
	}
}
