/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 00:47:04 by clovell           #+#    #+#             */
/*   Updated: 2024/02/05 00:54:34 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_abs(int abs)
{
	if (abs < 0)
		return (-abs);
	return (abs);
}

char	*ft_ftoa(double n, int precision)
{
	char		*whole;
	char		*frac;
	const char	*padding = "";

	whole = ft_ltoa((long long int)n);
	n = ft_abs((n - (long long int)n) * (double)precision);
	frac = ft_ltoa(n);
	if (n < 10)
		padding = "00";
	else if (n < 100)
		padding = "0";
	return (ft_strfmt("%S.%s%S", whole, padding, frac));
}
