/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:00:20 by kmordaun          #+#    #+#             */
/*   Updated: 2024/03/16 13:42:26 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "state.h"
#include "map.h"
#include "cerror.h"

static void	map_update_vis(t_map *map)
{
	t_tile	*tile;
	int		x;
	int		y;
	int		index;

	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			tile = map_get_tile_ref(map, x, y);
			tile->vis = -1;
			if (tile->type == WALL)
				tile->vis = 0;
		}
	}
}

void	map_tiles_init(t_map *map, t_list *curr)
{
	t_tile	*tile;
	int		x;
	int		y;
	int		index;

	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			tile = map_get_tile_ref(map, x, y);
			*tile = (t_tile){0, .type = FLOOR, .vis = -1};
		}
	}
	index = 0;
	while (curr != NULL && curr->content != NULL)
	{
		index += map_tiles(map, (char *)curr->content, index);
		curr = curr->next;
	}
	map_update_vis(map);
}

/*
 * creates a link_list and checks if the map file is read
 * removes empty lines and replaces tabs with spaces
 * skips over modifiers in the list and checks map content is
 * correctly formatted initializes map and players start postion
 * calls setup modifiers and deallocates same link_list
 * the content is str_dup and if freed at a later point
 */
// TODO: REMOVE
// if (raw_map_file == NULL || (int64_t)raw_map_file->content <= 1)
// 	error_return("File Invalid", 1, 1, &raw_map_file);

t_err	map_init(t_map *map, char *map_str, t_game *game)
{
	t_list	*curr;
	t_list	*raw_map_file;

	raw_map_file = ft_lst_readfile(map_str);
	if (raw_map_file == NULL || (int64_t)raw_map_file->content <= 1)
		return (deallocate_list(&raw_map_file), err(1, "File Invalid\n"));
	remove_empty_lines(&raw_map_file);
	replace_tabs(raw_map_file);
	curr = raw_map_file;
	while (curr != NULL && map_starting_tile((char *)curr->content) == 0)
		curr = curr->next;
	if (map_check_setup(curr, raw_map_file, map_str))
		return (deallocate_list(&raw_map_file), 1);
	map->width = map_width_size(curr);
	map->height = map_height_size(curr);
	if (map->width > 200 || map->height > 200)
		return (err(1, "Map Exceeds Limits\n"));
	player_setup(curr, game);
	map_tiles_init(map, curr);
	if (modifier_setup(raw_map_file, map, game->world))
		return (err(1, ": unexpected modifier content\n"));
	deallocate_list(&raw_map_file);
	return (0);
}

/*
 * this fuction chooses where to get the map content 
 * currently if there is only 1 argument it will call
 * a default map but will need to change this if there
 * is map selection from splash/title screen and pass
 * the mapstr or a map number to this fuction
 */

t_err	map_parse(int argc, char **argv, t_game *game)
{
	char	*map_str;

	if (argc == 1)
		map_str = "assets/maps/default.cub";
	else if (argc == 2)
		map_str = argv[1];
	else
		exit(2);
	if (map_init(&game->world->map, map_str, game))
		return (1);
	mmap_init(game);
	return (0);
}
