/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def_tex.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:25:26 by clovell           #+#    #+#             */
/*   Updated: 2024/05/03 14:31:29 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef DEF_TEX_H
# define DEF_TEX_H
# include <stddef.h>
# include <stdlib.h>
# include <stdbool.h>
# include "texture.h"
# include "libft.h"
# include "app.h"

typedef struct s_def_tex
{
	char		*id;
	char		*path;
	int			frames;	
	bool		loaded;
	t_texture	*tex;
}	t_def_tex;
typedef struct s_def_node	t_def_node;

struct s_def_node
{
	t_def_tex	data;
	t_def_node	*next;
};

typedef struct s_def_ctx
{
	t_def_node	*head;
}	t_def_ctx;

void		def_tex_add(const t_def_tex *tex, int amount);
t_texture	*def_tex_get(const t_app *app, char *id);
t_def_tex	*def_tex_get_def(const t_app *app, char *id);
t_def_ctx	*def_get_ctx(void);

#endif
