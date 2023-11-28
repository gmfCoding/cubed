#include "cubed.h"

void	fn_NO(char *content, int mod_pos, t_world *world, t_map *map)
{
	(void)world;
	map->mods[mod_pos].type = NORTH_TEXTURE;
	map->mods[mod_pos].content = content;
}
void	fn_SO(char *content, int mod_pos, t_world *world, t_map *map)
{
	(void)world;
	map->mods[mod_pos].type = SOUTH_TEXTURE;
	map->mods[mod_pos].content = content;
}
void	fn_WE(char *content, int mod_pos, t_world *world, t_map *map)
{
	(void)world;
	map->mods[mod_pos].type = WEST_TEXTURE;
	map->mods[mod_pos].content = content;
}
void	fn_EA(char *content, int mod_pos, t_world *world, t_map *map)
{
	(void)world;
	map->mods[mod_pos].type = EAST_TEXTURE;
	map->mods[mod_pos].content = content;
}
