/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:35:52 by clovell           #+#    #+#             */
/*   Updated: 2024/02/19 19:35:00 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MUI_H
# define MUI_H
# include "def_tex.h"
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
	t_vec2		pos;
	char		*id;
	t_def_tex	*def;
	uint8_t		frame;
	int			anim;
	t_rect		rect;
	bool		unlock;
}	t_mui_base;

typedef struct s_mui_dial
{
	t_mui_base	base;
	t_vec2		drag_start;
	double		curr_angle;
	double		prev_angle;
	double		angle;
	t_vec2		range;
}	t_mui_dial;

/*
Idea: reset to mid point when let go
*/
typedef struct s_mui_slider
{
	t_mui_base	base;
	t_vec2		start;
	t_vec2		end;
	double		value;
	bool		elastic;
	double		rest;
}	t_mui_slider;

typedef struct s_mui_button
{
	t_mui_base	base;
	bool		on;
	bool		toggle;
}	t_mui_button;

typedef union u_mui_any
{
	union
	{
		t_mui_base		*p;
		t_mui_base		*base;
	};
	union
	{
		t_mui_button	*button;
		t_mui_button	*b;
	};
	union
	{
		t_mui_slider	*slider;
		t_mui_slider	*s;
	};
	union
	{
		t_mui_dial		*dial;
		t_mui_dial		*d;
	};
}	t_mui_any;

# define MUI_LEN_TYPES 4


typedef struct s_game t_game; // TODO: REMOVE
typedef struct s_mui_context
{
	void		*ctx;
	union
	{
		struct
		{
			int				len_dials;
			int				len_sliders;
			int				len_buttons;
			int				len_inds;
			int				size_dials;
			int				size_sliders;
			int				size_buttons;
			int				size_inds;
			t_mui_dial		*dials;
			t_mui_slider	*sliders;
			t_mui_button	*buttons;
			t_mui_base		*inds;
		};
		struct
		{
			int			lengths[MUI_LEN_TYPES];
			int			sizes[MUI_LEN_TYPES];
			t_mui_base	*all[MUI_LEN_TYPES];
		};
	};
	bool			heap;
	t_vecd			oscale;
	t_vecd			scale;
	t_vec2			offset;
}	t_mui_ctx;

void	mui_clone(const t_mui_ctx *src, t_mui_ctx *dst);
void	mui_destroy(t_mui_ctx *mui, t_mui_ctx **store, bool heap);

/* Preloads all the deferred textures. */
void	mui_def_preload(t_app *app, t_mui_ctx *ctx);

typedef struct s_inputctx	t_inputctx;

void	mui_init(t_mui_ctx *ctx);

void	mui_process(t_mui_ctx *ctx, t_inputctx *in);

void	mui_render(t_mui_ctx *ctx, const t_texture *rt);

#endif