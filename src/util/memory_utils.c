/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:00:20 by kmordaun          #+#    #+#             */
/*   Updated: 2024/03/16 10:26:12 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "map.h"
#include "state.h"
#include "get_next_line.h"

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

/*
 * free all content from link list and the node of the list
 * its self is called before the game starts

 */
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
	*raw_map_file = NULL;
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
