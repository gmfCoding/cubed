/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:16:09 by clovell           #+#    #+#             */
/*   Updated: 2024/02/20 20:01:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <inttypes.h>
#include "random.h"

void	msrand(t_rand *rand, uint64_t seed)
{
	rand->next = seed;
}

int	mrand(t_rand *rand)
{
	rand->next = rand->next * 1103515245 + 12345;
	return ((unsigned)(rand->next / (MRAND_MAX * 2)) % MRAND_MAX);
}

double	mrand_rangef(t_rand *rand, double min, double max)
{
	flerp(min, max, mrand(rand) / MRAND_MAXF);
}