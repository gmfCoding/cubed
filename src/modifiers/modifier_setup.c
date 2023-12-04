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

#include "cubed.h"

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
