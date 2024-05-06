/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifier_setup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:24:36 by kmordaun          #+#    #+#             */
/*   Updated: 2024/05/06 22:38:22 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "state.h"
#include "modifiers.h"
#include "iter.h"

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

static char *const			g_mapsymbols[] = {
[MOD_ID_NO] = "NO",
[MOD_ID_SO] = "SO",
[MOD_ID_WE] = "WE",
[MOD_ID_EA] = "EA",
[MOD_ID_F] = "F ",
[MOD_ID_C] = "C ",
[MOD_ID_DR] = "DR",
[MOD_ID_KE] = "KE",
[MOD_ID_AL] = "AL",
[MOD_ID_MM] = "MM",
[MOD_ID_EN] = "EN",
[MOD_ID_WN] = "WN", // WINDOW
[MOD_ID_WL] = "WL", // WINDOW LINE (really box)
[MOD_ID_FL] = "FL", // Five lights
[MOD_ID_OB] = "OB", // Orbit task
[MOD_ID_GO] = "GO", // Or-Gate / Redirect
[MOD_ID_GA] = "GA", // And-Gate
[MOD_ID_GM] = "GM", // Multi Gate Splitter
[MOD_ID_TA] = "TA", // Trigger area
[MOD_ID_VC] = "VC",
};

static const t_ex_action	g_mapfuncs[] = {
[MOD_ID_NO] = &mod_gen_no,
[MOD_ID_SO] = &mod_gen_so,
[MOD_ID_WE] = &mod_gen_we,
[MOD_ID_EA] = &mod_gen_ea,
[MOD_ID_F] = &mod_gen_f,
[MOD_ID_C] = &mod_gen_c,
[MOD_ID_DR] = &mod_gen_dr,
[MOD_ID_KE] = &mod_gen_ke,
[MOD_ID_AL] = &mod_gen_al,
[MOD_ID_MM] = &mod_gen_mm,
[MOD_ID_EN] = &mod_gen_en,
[MOD_ID_WN] = &mod_gen_wn,
[MOD_ID_WL] = &mod_gen_wl,
[MOD_ID_FL] = &mod_gen_fl,
[MOD_ID_OB] = &mod_gen_ob,
[MOD_ID_GO] = &mod_gen_go,
[MOD_ID_GA] = &mod_gen_ga,
[MOD_ID_GM] = &mod_gen_gm,
[MOD_ID_TA] = &mod_gen_ta,
[MOD_ID_VC] = &mod_gen_vc,
};

t_err	modifier_seperate_content(char *content, char *type, char *data)
{
	if (ft_sescanf(content, "%N%s\v%s", (size_t)512, type, data) != 3)
		return (1);
	return (0);
}

t_ex_action	modifier_get_func(char *type)
{
	size_t	i;

	i = ITER_SIZET_START;
	while (++i < (sizeof(g_mapsymbols) / sizeof(g_mapsymbols[0])))
	{
		if (ft_strncmp(g_mapsymbols[i], type, ft_strlen(type)) == 0)
			return (g_mapfuncs[i]);
	}
	return (NULL);
}

t_err	modifier_setup(t_list *raw_map_file, t_map *map, t_world *world)
{
	t_list		*curr;
	char		*str;
	int			index;
	char		mod[2][512];
	t_ex_action	func;

	index = 0;
	curr = raw_map_file;
	while (curr != NULL && curr->content != NULL)
	{
		remove_spaces(curr->content);
		str = (char *)curr->content;
		if (ft_strlen(str) > 0)
		{
			if (modifier_seperate_content(str, mod[0], mod[1]))
				return (ft_putstr_fd(str, STDERR_FILENO), 1);
			func = modifier_get_func(mod[0]);
			if (func && func(mod[1], index++, world, map))
				return (ft_putstr_fd(mod[0], STDERR_FILENO), 1);
		}
		curr = curr->next;
	}
	return (0);
}
