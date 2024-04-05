/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 12:23:51 by clovell           #+#    #+#             */
/*   Updated: 2024/04/05 18:01:20 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	int				e;
	const t_uchar	*us;
	t_uchar			uc;

	if (n == 0)
		return (0);
	e = n;
	us = (const t_uchar *)s;
	uc = (t_uchar)c;
	while (us[e - n] != uc)
	{
		if (e - n == n - 1)
			return (0);
		e++;
	}
	return ((void *)&s[e - n]);
}
