#include "cubed.h"

void	modifier_setup(t_list *raw_map_file, t_map *map, t_world *world)
{
	t_list	*curr;
	char	*str;
	int		i;
	int		mod_pos;

	mod_pos = 0;
	curr = raw_map_file;
	while (curr != NULL && curr->content != NULL)
	{
		str = (char *)curr->content;
		remove_spaces(str);
		i = -1;
		while (++i < (sizeof(g_mapsymbols) / sizeof(g_mapsymbols[0])))
		{
			if (ft_strncmp(g_mapsymbols[i], str, mod_strlen(g_mapsymbols[i])) == 0)
				((t_ex_action)g_mapfuncs[i])(str + (mod_strlen(g_mapsymbols[i]) + 1), mod_pos++, world, map);
		}
		curr = curr->next;
	}
}
