/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:00:20 by kmordaun          #+#    #+#             */
/*   Updated: 2023/11/28 20:34:39 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"


char *const    g_mapsymbols[] = {
	"NO",
	"SO",
	"WE",
	"EA",
	"F",
	"C",
};

t_ex_action const    g_mapfuncs[] = {
     &fn_NO,
     &fn_SO,
     &fn_WE,
     &fn_EA,
     &fn_F,
     &fn_C,
};

void	deallocate_list(t_list **raw_map_file)
{
	t_list	*curr;
	t_list	*temp;

	curr = *raw_map_file;
	while (curr != NULL)
	{
		temp = curr;
		curr = curr->next;
		free(temp->content);
		free(temp);
	}
}

t_list	*ft_lst_readfile(const char *path)
{
	t_list	*first;
	t_list	*next;
	char	*line;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	first = ft_lstnew((void *)0);
	next = first;
	line = get_next_line(fd);
	while (line)
	{
		next->next = ft_lstnew(line);
		next = next->next;
		(first->content)++;
		line = get_next_line(fd);
	}
	close (fd);
	next->next = ft_lstnew(NULL);

	return (first);
}

t_map	map_init(t_map *map, char *map_str, t_world *world)
{
	t_list	*curr;
	t_list	*raw_map_file;
	int		index;

	raw_map_file = ft_lst_readfile(map_str);
	if (raw_map_file == NULL)
		exit(2);//returnrapper here
	index = 0;
	remove_empty_lines(&raw_map_file);
	replace_tabs(raw_map_file);
	curr = raw_map_file;

	while (curr != NULL && map_starting_tile((char *)curr->content) == 0)
		curr = curr->next;
	map_check_setup(curr, raw_map_file, map_str);
	map->width = map_width_size(curr);
	map->height = map_height_size(curr);
	world->player = player_setup(curr, world);
	while (curr != NULL && curr->content != NULL)
	{
		index += map_tiles(map, (char *)curr->content, index);
		curr = curr->next;
	}
	modifier_setup(raw_map_file, map, world);
	deallocate_list(&raw_map_file);

	return (*map);
}

t_map	map_parse(int argc, char **argv, t_world *world)
{
	t_map	map;
	char	*map_str;
	if (argc == 1)
		map_str = "assets/maps/map1.cub";
	else if (argc == 2)
		map_str = argv[1];
	else
		exit(2);
	map = map_init(&map, map_str, world);
	return (map);
}
