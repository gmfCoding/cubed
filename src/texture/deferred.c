/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deferred.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:13:48 by clovell           #+#    #+#             */
/*   Updated: 2024/02/07 18:49:08 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "def_tex.h"
#include "string_utils.h"

static void	def_tex_load(const t_app *app, t_def_node *node)
{
	char	buffer[4096];
	char	*insert;
	int		i;

	node->data.tex = malloc(sizeof(t_texture) * node->data.frames);
	i = -1;
	while (++i < node->data.frames)
	{
		insert = &buffer[ft_strlcpy(buffer, node->data.path, sizeof(buffer))];
		if (node->data.frames > 1)
			ft_strtol(i, insert);
		ft_strlcat(insert, ".xpm", 4096);
		node->data.tex[i] = texture_load(app->mlx, buffer);
	}
	node->data.loaded = true;
}

t_def_ctx	*def_ctx_memman(bool destroy)
{
	static t_def_ctx	context = {.head = NULL};

	if (destroy)
	{
	}
	return (&context);
}

void	def_tex_add(const t_def_tex *tex, int amount)
{
	t_def_ctx *const	ctx = def_ctx_memman(false);
	int					i;
	t_def_node			*insert;

	i = -1;
	while (++i < amount)
	{
		insert = malloc(sizeof(t_def_node));
		insert->data = tex[i];
		insert->next = ctx->head;
		ctx->head = insert;
	}
}

t_texture	*def_tex_get(const t_app *app, char *id)
{
	const t_def_tex	*def = def_tex_get_def(app, id);

	if (!def)
		return (NULL);
	return (def->tex);
}

t_def_tex	*def_tex_get_def(const t_app *app, char *id)
{
	const t_def_ctx	*ctx = def_ctx_memman(false);
	t_def_node		*curr;

	curr = ctx->head;
	while (curr != NULL)
	{
		if (ft_strcmp(curr->data.id, id) == 0)
		{
			if (curr->data.loaded == true)
				return (&curr->data);
			def_tex_load(app, curr);
			return (&curr->data);
		}
		curr = curr->next;
	}
	return (NULL);
}
