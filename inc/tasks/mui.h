/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:35:52 by clovell           #+#    #+#             */
/*   Updated: 2024/02/07 16:31:46 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MUI_H
# define MUI_H
# include "vector2i.h"
# include "texture.h"
# include "rect.h"
# include <stdbool.h>

typedef enum e_mui_type
{
	MUI_BASE,
	MUI_DIAL,
	MUI_SLIDE,
	MUI_BUTTON,
}	t_mui_type;

typedef struct s_mui_base
{
	t_mui_type	type;
	t_vec2i		pos;
	t_texture	*texture;
	const char	**paths;
	int			frame;
	int			frames;
	int			anim;
	t_rect		rect;
	bool		unlock;
}	t_mui_base;

typedef struct s_mui_dial
{
	t_mui_base	base;
	t_vec2		drag_start;
	float		angle;
	t_vec2		range;
}	t_mui_dial;

typedef struct s_mui_slider
{
	t_mui_base	base;
	t_vec2		start;
	t_vec2		end;
	double		value;
}	t_mui_slider;

typedef struct s_mui_button
{
	t_mui_base	base;
	bool		on;
	bool		toggle;
}	t_mui_button;

typedef union u_mui_any
{
	t_mui_base		*base;
	t_mui_button	*button;
	t_mui_slider	*slider;
	t_mui_dial		*dial;
}	t_mui_any;

typedef struct s_mui_context
{
	t_mui_dial		*dials;
	int				len_dials;
	t_mui_slider	*sliders;
	int				len_sliders;
	t_mui_button	*buttons;
	int				len_buttons;
	bool			heap;
}	t_mui_ctx;

void	mui_clone(const t_mui_ctx *src, t_mui_ctx *dst);
void	mui_destroy(t_mui_ctx *mui, t_mui_ctx **store, bool heap);

typedef struct s_inputctx t_inputctx;

void	mui_process_buttons(t_mui_ctx *ctx, t_inputctx *in);
void	mui_process_dials(t_mui_ctx *ctx, t_inputctx *in);
void	mui_process_sliders(t_mui_ctx *ctx, t_inputctx *in);
void	mui_process(t_mui_ctx *ctx, t_inputctx *in);

#endif