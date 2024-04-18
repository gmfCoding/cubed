/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_dimensions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:11:56 by kmordaun          #+#    #+#             */
/*   Updated: 2024/04/18 17:22:51 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

/*
 * both functions take the link_list and return a size
 * the list thats passed through has skipped over the elements
 */
int	map_width_size(t_list *curr)
{
	size_t	i;
	char	*str;

	i = 0;
	while (curr != NULL && curr->content != NULL)
	{
		str = (char *)curr->content;
		if (ft_strlen(str) > i)
		{
			if (str[ft_strlen(str)] == '\n')
				i = ft_strlen(str) - 1;
			else
				i = ft_strlen(str);
		}
		curr = curr->next;
	}
	return (i - 1);
}

int	map_height_size(t_list *curr)
{
	int	i;

	i = 0;
	while (curr != NULL && curr->content != NULL)
	{
		i++;
		curr = curr->next;
	}
	return (i);
}
