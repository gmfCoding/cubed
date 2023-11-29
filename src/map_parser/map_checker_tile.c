/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker_tile.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:01:10 by kmordaun          #+#    #+#             */
/*   Updated: 2023/11/29 16:09:28 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	map_check_player(char *content)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (content[i])
	{
		if (content[i] == 'N' || content[i] == 'S')
			count++;
		if (content[i] == 'E' || content[i] == 'W')
			count++;
		i++;
	}
	return (count);
}

int	map_check_invalid_char(char *content)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (content[i])
	{
		if (content[i] != 'N' && content[i] != 'S' && \
			content[i] != 'E' && content[i] != 'W' && \
			content[i] != '0' && content[i] != '1' && \
			content[i] != ' ' && content[i] != '\n')
			count++;
		i++;
	}
	return (count);
}

/*flood fill */
int	map_check_surrounded(t_map *map_temp, int pos)
{
	if (pos >= 0 && pos <= (map_temp->width * map_temp->height) \
			&& map_temp->tiles[pos].type != WALL \
			&& map_temp->tiles[pos].type != EMPTY)
		return (1);
	if (!(pos >= 0 && pos <= (map_temp->width * map_temp->height)) \
		|| map_temp->tiles[pos].type == WALL)
		return (0);
	if (map_temp->tiles[pos].type == EMPTY)
		map_temp->tiles[pos].type = WALL;
	if (map_check_surrounded(map_temp, pos - map_temp->width) == 1)
		return (1);
	if (map_check_surrounded(map_temp, pos + map_temp->width) == 1)
		return (1);
	if (map_check_surrounded(map_temp, pos - 1) == 1)
		return (1);
	if (map_check_surrounded(map_temp, pos + 1) == 1)
		return (1);
	return (0);
}

void	map_check_err(t_map *map_temp, t_list *temp, \
		t_list *raw_map_file, char *map_str)
{
	const t_list	*curr = temp;
	int		count_players;
	int		count_invalid_char;

	count_players = 0;
	count_invalid_char = 0;
	while (curr != NULL && curr->content != NULL)
	{
		if (is_line((char *)curr->content) && ((char *)curr->content)[0] != ' ')
			error_return(":Invalid Line In Map", 1, 1, &raw_map_file);
		count_players += map_check_player((char *)curr->content);
		count_invalid_char += map_check_invalid_char((char *)curr->content);
		curr = curr->next;
	}
	if (map_check_elements(raw_map_file) == 1)
		error_return(":Invalid Element", 1, 0, &raw_map_file);
	if (count_players > 1 || count_players < 1)
		error_return(":Invalid Player Count", 1, 1, &raw_map_file);
	if (count_invalid_char > 0)
		error_return(":Invalid Character", 1, 1, &raw_map_file);
	if (map_check_surrounded(map_temp, 0) == 1)
		error_return(":Invalid Boarder", 1, 1, &raw_map_file);
	if (ft_strcmp(".cub", ft_strrchr(map_str, '.')) != 0)
		error_return(":Invalid File Type", 1, 1, &raw_map_file);
}

void	map_check_setup(t_list *curr, t_list *raw_map_file, char *map_str)
{
	t_list	*temp;
	t_map	map_temp;
	int		index;

	index = 0;
	temp = curr;
	map_temp.width = (map_width_size(curr) + 2);
	map_temp.height = (map_height_size(curr) + 2);
	while (index < map_temp.width)
		map_temp.tiles[index++].type = get_tiletype(' ');
	while (curr != NULL && curr->content != NULL)
	{
		index += map_tiles_surround(&map_temp, (char *)curr->content, index);
		curr = curr->next;
	}
	while (++index < ((map_temp.width * map_temp.height) + map_temp.width))
		map_temp.tiles[index].type = get_tiletype(' ');
	map_check_err(&map_temp, temp, raw_map_file, map_str);
}
