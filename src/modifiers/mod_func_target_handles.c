/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_func_target_handles.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:38:42 by clovell           #+#    #+#             */
/*   Updated: 2024/04/10 01:37:04 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "map.h"
#include "state.h"
#include "csv.h"
#include "modifier_data.h"

/*
 * NAME,TARGET
 */
t_err	mod_gen_go(char *content, int index, t_world *world, t_map *map)
{
	char		target[NAME_SIZE];
	t_entity_2 *const	ent = &world->ent_2[world->ent_count];
	const int	found = ft_sescanf(content, "%N%s,%s\v", \
									NAME_SIZE, ent->name, target);

	if (found != 3)
		return (1);
	ent->target_names[0] = ft_strdup(target);
	if (!ent->target_names[0])
		return (1);
	ent->handle = &target_handle_or;
	world->ent_count++;
	return (0);
}

/*
 * NAME,TARGET,PARENT1,PARENT2
 */
t_err	mod_gen_ga(char *content, int index, t_world *world, t_map *map)
{
	char				name[NAME_SIZE];
	char				targets[3][NAME_SIZE];
	t_entity_2 *const	ent = &world->ent_2[world->ent_count];
	const int			found = ft_sescanf(content, "%N%s,%s,%s,%s\v", \
									NAME_SIZE, ent->name, targets[0], targets[1],targets[2]);

	if (found != 5)
		return (1);
	ent->target_names[0] = ft_strdup(targets[0]);
	if (!ent->target_names[0])
		return (1);
	ent->target_names[1] = ft_strdup(targets[1]);
	if (!ent->target_names[1])
		return (1);
	ent->target_names[2] = ft_strdup(targets[2]);
	if (!ent->target_names[2])
		return (2);
	ent->handle = &target_handle_and;
	world->ent_count++;
	return (0);
}

/*
 * NAME,TARGET1,TARGET2,TARGET3
 */
t_err	mod_gen_gm(char *content, int index, t_world *world, t_map *map)
{
	char				targets[3][NAME_SIZE];
	t_entity_2 *const	ent = &world->ent_2[world->ent_count];
	const int			found = ft_sescanf(content, "%N%s,%s,%s,%s\v", \
									sizeof(*targets), ent->name, targets[0], targets[1], targets[2]);
	if (found != 5)
		return (1);
	ent->target_names[0] = ft_strdup(targets[0]);
	if (!ent->target_names[0])
		return (1);
	ent->target_names[1] = ft_strdup(targets[1]);
	if (!ent->target_names[1])
		return (1);
	ent->target_names[2] = ft_strdup(targets[2]);
	if (!ent->target_names[2])
		return (1);
	ent->handle = &target_handle_splitter;
	world->ent_count++;
	return (0);
}
