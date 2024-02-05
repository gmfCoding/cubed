/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:08:18 by clovell           #+#    #+#             */
/*   Updated: 2024/02/05 17:41:30 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "orbit.h"
#include "vector2.h"
#include "random.h"

void	orb_generate(t_kep_path *path, const t_orb_gen *gen, t_rand *rand)
{
	path->sma = flerp(mrand(rand) / MRAND_MAXF, gen->sma.min, gen->sma.max);
	path->ecc = flerp(mrand(rand) / MRAND_MAXF, gen->ecc.min, gen->ecc.max);
	path->inc = flerp(mrand(rand) / MRAND_MAXF, gen->inc.min, gen->inc.max);
	path->aop = flerp(mrand(rand) / MRAND_MAXF, gen->aop.min, gen->aop.max);
	path->lan = flerp(mrand(rand) / MRAND_MAXF, gen->lan.min, gen->lan.max);
}
