/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:43:28 by kmordaun          #+#    #+#             */
/*   Updated: 2024/04/30 20:35:40 by kmordaun         ###   ########.fr       */
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
		new_line = malloc(new_size);
		if (new_line == NULL)
			return (1);
		tabs_change_to_space(new_line, line);
		free(line);
		curr->content = new_line;
		curr = curr->next;
	}
	return (0);
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
	free(temp->content);
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
