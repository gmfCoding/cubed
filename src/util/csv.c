/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csv.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 07:19:49 by clovell           #+#    #+#             */
/*   Updated: 2024/03/18 23:29:41 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cerror.h"
#include "libft.h"
#include "csv.h"
#include <math.h>

int	csv_clen(char **str)
{
	int	i;

	i = 0;
	while ((*str) != NULL && (*str)[i] != '\0' && (*str)[i] != ',')
		i++;
	return (i);
}

void	csv_skip(char **str)
{
	*str += csv_clen(str);
	if (**str == ',')
		(*str)++;
}

t_err	csv_next(char type, char **str, void *dst)
{
	if (type == 'i' || type == 'd')
		*((int *)dst) = ft_atoi(*str);
	if (type == 'u')
	{
		*((int *)dst) = ft_atoi(*str);
		if (*(int *)dst < 0)
			return (1);
	}
	else if (type == 'f')
		*((float *)dst) = ft_atoi(*str);
	else if (type == 'F')
		*((double *)dst) = ft_atoi(*str);
	if (type == 's')
		ft_strlcpy((char *)dst, *str, fmin(CSV_LEN, csv_clen(str)));
	csv_skip(str);
	return (0);
}
