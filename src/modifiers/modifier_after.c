/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifier_after.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:24:36 by kmordaun          #+#    #+#             */
/*   Updated: 2024/05/06 22:38:29 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "entity.h"
#include "state.h"

t_mm_tile	*mmap_find_tile(t_game *game, t_vec2 pos)
{
	int	i;

	i = -1;
	while (game->mmap.tiles[++i].img != NULL)
		if (game->mmap.tiles[i].ref == (pos.y * game->world->map.width) + pos.x)
			return (&game->mmap.tiles[i]);
	return (NULL);
}

static void	modifier_grab_mmap_ref(t_game *game)
{
	t_list			*ent_iter;
	t_entity		*ent_curr;

	ent_iter = game->world->entities;
	while (ent_iter != NULL)
	{
		if (ent_iter->content != NULL)
		{
			ent_curr = (t_entity *)ent_iter->content;
			ent_curr->mm_tile = mmap_find_tile(game, ent_curr->pos);
		}
		ent_iter = ent_iter->next;
	}
}

void	modifier_after(t_game *game)
{
	t_world *const	w = game->world;
	int				i;
	int				j;

	i = -1;
	while ((size_t)++i < w->ent_count)
	{
		j = -1;
		while (++j < EVENT_ENT_MAX_TARGETS)
		{
			if (w->ent_2[i].target_names[j] && w->ent_2[i].target_names[j][0] \
						&& ft_strcmp(w->ent_2[i].target_names[j], "NULL") != 0)
				w->ent_2[i].targets[j] = mod_search_name(w, \
												w->ent_2[i].target_names[j]);
			if (w->ent_2[i].target_names[j] != NULL)
				free(w->ent_2[i].target_names[j]);
		}
		w->ent_2[i].ref_mm_tile = mmap_find_tile(game, w->ent_2[i].pos);
	}
	modifier_grab_mmap_ref(game);
}
