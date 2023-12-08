
#include "cubed.h"

/*
 * use this only if you have malloc inside of a malloc
 * otherwise you can just free like normal
 */
void	free_str_array(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
		free(str[i++]);
	free(str);
}

void	free_content(t_game *game)
{
	int	i;

	i = -1;
	while(game->world.map.mods[++i].content != NULL)
		free(game->world.map.mods[i].content);
}
