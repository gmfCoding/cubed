/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:33:25 by clovell           #+#    #+#             */
/*   Updated: 2023/11/27 19:21:13 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_lstremove(t_list **lst, t_list *target, void (*del)(void*))
{
	while (*lst != NULL)
	{
		if (lst[0] == target)
		{
			lst[0] = target->next;
			ft_lstdelone(target, del);
			return (1);
		}
		lst = &lst[0]->next;
	}
	return (0);
}
