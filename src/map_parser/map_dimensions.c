/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:00:20 by kmordaun          #+#    #+#             */
/*   Updated: 2023/11/27 18:24:33 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	map_width_size(t_list *curr)
{
	int i;

	i = 0;
	while (curr != NULL && curr->content != NULL)
	{
		if (ft_strlen((char *)curr->content) > i)
		{
			if (((char *)curr->content)[ft_strlen((char *)curr->content)] == '\n')
				i = ft_strlen((char *)curr->content) - 1;
			else
				i = ft_strlen((char *)curr->content);
		}
		curr = curr->next;
	}

	return (i-1);
}

int	map_height_size(t_list *curr)
{
	int i;

	i = 0;
	while (curr != NULL && curr->content != NULL)
	{
		i++;
		curr = curr->next;
	}
	return (i);
}
