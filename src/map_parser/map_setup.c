/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:00:20 by kmordaun          #+#    #+#             */
/*   Updated: 2023/11/29 14:20:04 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "state.h"
#include "map.h"

/*
 * creates a link_list and checks if the map file is read
 * removes empty lines and replaces tabs with spaces
 * skips over modifiers in the list and checks map content is
 * correctly formatted initializes map and players start postion
 * calls setup modifiers and deallocates same link_list
 * the content is str_dup and if freed at a later point
 */

t_map	map_init(t_map *map, char *map_str, t_game *game)
{
	t_list	*curr;
	t_list	*raw_map_file;
	int		index;

	raw_map_file = ft_lst_readfile(map_str);
	if (raw_map_file == NULL)
		error_return("File Invalid", 1, 1, NULL);
	index = 0;
	remove_empty_lines(&raw_map_file);
	replace_tabs(raw_map_file);
	curr = raw_map_file;
	while (curr != NULL && map_starting_tile((char *)curr->content) == 0)
		curr = curr->next;
	map_check_setup(curr, raw_map_file, map_str);
	map->width = map_width_size(curr);
	map->height = map_height_size(curr);
	player_setup(curr, game);
	while (curr != NULL && curr->content != NULL)
	{
		index += map_tiles(map, (char *)curr->content, index);
		curr = curr->next;
	}
	modifier_setup(raw_map_file, map, game->world);
	deallocate_list(&raw_map_file);
	return (*map);
}

/*
 * this fuction chooses where to get the map content 
 * currently if there is only 1 argument it will call
 * a default map but will need to change this if there
 * is map selection from splash/title screen and pass
 * the mapstr or a map number to this fuction
 */

t_map	map_parse(int argc, char **argv, t_game *game)
{
	t_map	map;
	char	*map_str;

	if (argc == 1)
		map_str = "assets/maps/map1.cub";
	else if (argc == 2)
		map_str = argv[1];
	else
		exit(2);
	map = map_init(&map, map_str, game);
	return (map);
}
