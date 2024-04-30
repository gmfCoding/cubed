/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:43:28 by kmordaun          #+#    #+#             */
/*   Updated: 2024/03/11 21:16:19 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

/*
 * used to find the first instance of a wall you map be worried that
 * it will get stopped in elements this should never happen as it 
 * always checks the first character in content and each first character 
 * in elements must consist of 1 or 2 uppercase letter, if it happen to 
 * be a 1 this will get picked up in map_checker_element.c and return error
 */
int	map_starting_tile(char *content)
{
	int	i;

	i = 0;
	while (ft_isspace(content[i]))
		i++;
	if (content[i] == '1')
		return (1);
	return (0);
}

void	tabs_change_to_space(char *new_line, char *line)
{
	int		i;
	int		k;
	int		j;

	i = -1;
	j = 0;
	while (line[++i] != '\0')
	{
		if (line[i] == '\t')
		{
			k = -1;
			while (++k < 4)
				new_line[j++] = ' ';
		}
		else
			new_line[j++] = line[i];
	}
	new_line[j] = '\0';
}

/*
 * used to replace all taps with spaces to avoid error
 * when parsing the map and modifiers
 */
int	replace_tabs(t_list *curr)
{
	size_t	new_size;
	char	*new_line;
	char	*line;
	int		num_tabs;
	int		i;

	while (curr != NULL && curr->content != NULL)
	{
		line = (char *)curr->content;
		num_tabs = 0;
		i = -1;
		while (line[++i] != '\0')
			if (line[i] == '\t')
				++num_tabs;
		new_size = ft_strlen(line) + (num_tabs * (TAB_SIZE - 1)) + 1;
		char *new_line = malloc(new_size);
		if (new_line == NULL)
			return (1);
		tabs_change_to_space(new_line, line);
		free(line);
		curr->content = new_line;
		curr = curr->next;
	}
	return (0);
}

/*//can get rid of this not using memmove anymore now allowcating for new str
void	replace_tabs(t_list *curr)
{
	int		i;
	int		j;
	char	*line;

	printf("\n");
	while (curr != NULL && curr->content != NULL)
	{
		line = (char *)curr->content;
		i = 0;
		while (line[i] != '\0')
		{
			if (line[i] == '\t')
			{
				ft_memmove(&line[i + TAB_SIZE], \
					&line[i + 1], ft_strlen(&line[i + 1]) + 1);
				j = 0;
				while (j < TAB_SIZE)
				{
					if (line[i + j] == '\0')
						break;
					line[i + j++] = ' ';
					printf("|space|");
					if(line[i + j++] == '\t')
						printf("ts a tab here\n");
				}
				i += TAB_SIZE;
			}
			else
				i++;
		}
		curr = curr->next;
	}
	printf("\n");
	printf("\n");
}
*/



/*
 * a small fucntion used to print the map in terminal
 * only useful for debugging not needed in release
 */
void	map_print(t_map *map)
{
	int	i;

	i = 0;
	while (i < (map->width * map->height))
	{
		if (i % map->width == 0)
			printf("\n");
		printf("%d", map->tiles[i].type);
		i++;
	}
}

/*
 * gets rid of(frees) the interger that hold the length of a
 * link_list from the link_list there is also a small
 * error check done here if the length of link list
 * is less then or equal to 1 the file is empty
 */
void	remove_int_from_list(t_list **raw_map_file)
{
	t_list	*temp;

	if ((intptr_t)(*raw_map_file)->content <= 1)
		error_return("File Empty", 1, 1, NULL);
	temp = *raw_map_file;
	*raw_map_file = temp->next;
	free(temp);
}

/*
 * gets rid of all the empty lines in the link_list to
 * avoid any error while creating the map and modifiers
 */
void	remove_empty_lines(t_list **raw_map_file)
{
	t_list	*curr;
	t_list	*temp;

	remove_int_from_list(raw_map_file);
	curr = *raw_map_file;
	while (curr != NULL && is_empty_line(curr->content) == 1)
	{
		temp = curr;
		*raw_map_file = temp->next;
		curr = curr->next;
		ft_lstdelone(temp, free);
	}
	while (curr != NULL && curr->next != NULL)
	{
		if (map_starting_tile((char *)curr->content) == 1)
			break ;
		if (is_empty_line(curr->next->content) == 1)
		{
			temp = curr->next;
			curr->next = temp->next;
			ft_lstdelone(temp, free);
		}
		else
			curr = curr->next;
	}
}
/*
int	map_skip_over_modifiers(char *content)
{
	int	i;

	i = -1;
	while (++i < (sizeof(g_mapsymbols) / sizeof(g_mapsymbols[0])))
	{
		if (ft_strncmp(g_mapsymbols[i], content, strlen_nl(g_mapsymbols[i])) == 0)
			return (1);
	}
	return (0);
}
*/
