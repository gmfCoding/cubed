/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_func_wincon.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 20:47:31 by kmordaun          #+#    #+#             */
/*   Updated: 2024/05/02 22:10:07 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "vectorconv.h"
#include "modifier_data.h"


t_err	mod_gen_vc(char *content, int index, t_world *world, t_map *map)
{
	t_mod_wincon    mod;
	const int		found = ft_sescanf(content, "%N%s,%s\v",
			sizeof(mod.name), &mod.name, &mod.target);

	(void)index;
	if (found != 3)
		return (1);
	world->ent_2[world->ent_count] = (t_entity_2){0};
	ft_strlcpy(world->ent_2[world->ent_count].name, mod.name, NAME_SIZE);
	world->ent_2[world->ent_count].target_names[0] = ft_strdup(mod.target);
	world->ent_2[world->ent_count].handle = &target_handle_wincon;
	world->ent_count++;
	return (0);
}