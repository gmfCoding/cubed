/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:18:51 by clovell           #+#    #+#             */
/*   Updated: 2024/02/17 20:54:03 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memsetf64(void *b, double c, size_t len)
{
	while (len > 0)
	{
		len--;
		((double *)b)[len] = c;
	}
	return (b);
}

void	*ft_memsetf32(void *b, float c, size_t len)
{
	while (len > 0)
	{
		len--;
		((float *)b)[len] = c;
	}
	return (b);
}

void	*ft_memset(void *b, int c, size_t len)
{
	while (len > 0)
	{
		len--;
		((char *)b)[len] = c;
	}
	return (b);
}
