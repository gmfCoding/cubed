/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:43:28 by kmordaun          #+#    #+#             */
/*   Updated: 2023/11/29 16:47:49 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

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

void	replace_tabs(t_list *curr)
{
	int		i;
	int		j;
	char	*line;

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
					line[i + j++] = ' ';
				i += TAB_SIZE;
			}
			else
				i++;
		}
		curr = curr->next;
	}
}

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

void	remove_int_from_list(t_list **raw_map_file)
{
	t_list	*temp;

	if ((intptr_t)(*raw_map_file)->content <= 1)
		error_return("File Empty", 1, 1, NULL);
	temp = *raw_map_file;
	*raw_map_file = temp->next;
	free(temp);
}

void	remove_empty_lines(t_list **raw_map_file)
{
	t_list	*curr;
	t_list	*temp;

	remove_int_from_list(raw_map_file);
	curr = *raw_map_file;
	while (curr != NULL && is_line(curr->content) == 1)
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
		if (is_line(curr->next->content) == 1)
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
		if (ft_strncmp(g_mapsymbols[i], content, mod_strlen(g_mapsymbols[i])) == 0)
			return (1);
	}
	return (0);
}
*/
