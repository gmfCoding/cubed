/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker_tile.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:01:10 by kmordaun          #+#    #+#             */
/*   Updated: 2024/03/16 06:39:01 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "cerror.h"

/*
 * checks how many players are in map it currently returns
 * the number of players and errors if its less or more then 1
 * just incase we wanted to add more player later on we could 
 * implement.. but i think it maybe better to do that through the
 * modifiers instead if we do. 
 */
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

/*
 * check the map making sure it doesnt contain any invalid chars
 */
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

/*
 * a FLOOD_FILL type of function used to check the whole map surrounds
 * making sure each tile is not a FLOOR/0 or anything other then a
 * WALL/1 or EMPTY/2. if it is it will return an error
 */
static t_err	map_check_surrounded(t_map *map_temp, int pos)
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

#define ERR_LINE ":Invalid Line In Map"
#define ERR_BADELEM ":Invalid Element"
#define ERR_BADPLAYER ":Invalid Player Count"
#define ERR_BOARDER ":Invalid Player Count"
#define ERR_TYPE ":Invalid File Type"
/*
 * checks content of the map to follow the rules of subject
 * Return 1 on error 0 on success
 */
static t_err	 map_check_err(t_map *map_temp, t_list *temp, \
		t_list *file, char *path)
{
	const t_list	*curr = temp;
	char ***const	cstr = (void *)&curr;
	int				players;
	int				count_invalid_char;
	int				e;

	players = 0;
	count_invalid_char = 0;
	e = 0;
	while (curr != NULL && curr->content != NULL)
	{
		e |= err(is_empty_line(**cstr) && (**cstr)[0] != ' ', ERR_LINE);
		if (e)
			break ;
		players += map_check_player(**cstr);
		count_invalid_char += map_check_invalid_char(**cstr);
		curr = curr->next;
	}
	e = err(map_check_elements(file) == 1, ERR_BADELEM);
	e |= err(players != 1, ERR_BADPLAYER);
	e |= err(count_invalid_char > 0, ERR_BADELEM);
	e |= err(map_check_surrounded(map_temp, 0) == 1, ERR_BOARDER);
	if (ft_strrchr(path, '.') != NULL)
		e |= err(ft_strcmp(".cub", ft_strrchr(path, '.')) != 0, ERR_TYPE);
	return (e);
}

/*
 * sets up the map ready for checking for map errors
 */
t_err	map_check_setup(t_list *curr, t_list *raw_map_file, char *path)
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
	return (map_check_err(&map_temp, temp, raw_map_file, path));
}
