/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 12:33:21 by clovell           #+#    #+#             */
/*   Updated: 2024/04/05 18:01:52 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int				e;
	int				diff;
	const t_uchar	*us1;
	const t_uchar	*us2;

	if (n == 0)
		return (0);
	e = n;
	us1 = (const t_uchar *)s1;
	us2 = (const t_uchar *)s2;
	while (e - n < n)
	{
		diff = us1[e - n] - us2[e - n];
		if (diff != 0)
			return (diff);
		e++;
	}
	return (0);
}
