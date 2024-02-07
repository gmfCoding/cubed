/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deferred.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:13:48 by clovell           #+#    #+#             */
/*   Updated: 2024/02/07 16:29:53 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "def_tex.h"
#include "string_utils.h"

void	def_tex_add(t_def_tex *tex, int amount)
{
	t_def_ctx *const	ctx = def_get_ctx();
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

void	def_tex_load(t_app *app, t_def_node *node)
{
	char	buffer[4096];
	char	*insert;
	int		i;

	node->data.tex = malloc(sizeof(t_texture) * node->data.frames);
	i = -1;
	while (++i < node->data.frames)
	{
		insert = &buffer[ft_strlcpy(buffer, node->data.path, sizeof(buffer))];
		ft_strtol(i, insert);
		ft_strlcat(insert, ".xpm", 4096);
		node->data.tex[i] = texture_load(app->mlx, buffer);
	}
}

t_texture	*def_tex_get(t_app *app, char *id)
{
	const t_def_ctx	*ctx = def_get_ctx();
	t_def_node		*curr;

	curr = ctx->head;
	while (curr != NULL)
	{
		if (ft_strcmp(curr->data.id, id) == 0)
		{
			if (curr->data.loaded == true)
				return (curr->data.tex);
			def_tex_load(app, curr);
			return (curr->data.tex);
		}
		curr = curr->next;
	}
	return (NULL);
}

t_def_ctx	*def_get_ctx(void)
{
	static t_def_ctx	context = {.head = NULL};

	return (&context);
}
