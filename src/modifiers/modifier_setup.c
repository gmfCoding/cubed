/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifier_setup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:24:36 by kmordaun          #+#    #+#             */
/*   Updated: 2023/11/29 16:43:52 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
/*
 * ADD MODIFIERS 
 * here is where you can add modifiers or anything addition to the game
 * when adding a new modifier please make changes to
 * g_mapsymbols and g_mapfuncs and add any structs or entities to modifiers.h
 * call the function like this "see modifiers.h for details"
 * void	mod_gen_"__"(char *content, int index, t_world *world, t_map *map);
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
	"F",
	"C",
	"DR",
	"KE",
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
};

void	modifier_setup(t_list *raw_map_file, t_map *map, t_world *world)
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
		while (++i < (sizeof(g_mapsymbols) / sizeof(g_mapsymbols[0])))
		{
			if (ft_strncmp(g_mapsymbols[i], \
					str, mod_strlen(g_mapsymbols[i])) == 0)
				((t_ex_action)g_mapfuncs[i])(str + (mod_strlen(g_mapsymbols[i]) \
					+ 1), index++, world, map);
		}
		curr = curr->next;
	}
}
