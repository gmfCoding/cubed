/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:08:18 by clovell           #+#    #+#             */
/*   Updated: 2024/02/12 22:36:57 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "orbit.h"
#include "vector2.h"
#include "random.h"

void	orb_generate(t_kep_path *path, const t_orb_gen *gen, t_rand *rand)
{
	path->sma = flerp(gen->sma.min, gen->sma.max, mrand(rand) / MRAND_MAXF);
	path->ecc = flerp(gen->ecc.min, gen->ecc.max, mrand(rand) / MRAND_MAXF);
	path->inc = flerp(gen->inc.min, gen->inc.max, mrand(rand) / MRAND_MAXF);
	path->aop = flerp(gen->aop.min, gen->aop.max, mrand(rand) / MRAND_MAXF);
	path->lan = flerp(gen->lan.min, gen->lan.max, mrand(rand) / MRAND_MAXF);
}
