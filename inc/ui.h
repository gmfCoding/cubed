/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 18:55:47 by clovell           #+#    #+#             */
/*   Updated: 2024/02/05 00:22:29 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef UI_H
# define UI_H
# include "rect.h"
# include "texture.h"
# include <stdbool.h>

typedef struct s_button		t_button;
typedef struct s_ui_context	t_ui_context;
typedef void				(*t_uibtn_click_cb)(t_button *, t_ui_context *);
typedef struct s_button		t_button;
typedef struct s_text		t_text;

struct s_button
{
	t_rect				rect;
	t_texture			*texture;
	int					colour;
	void				*reference;
	void				*context;
	bool				repeat;
	t_uibtn_click_cb	callback;
	int					held;
};

struct s_text
{
	t_rect		rect;
	t_texture	*texture;
	void		*context;
	char		*text;
};

struct s_ui_context
{
	void	*parent;
	union
	{
		struct s_buttons
		{
			t_button	kep_prograde;	
			t_button	kep_retrograde;	
			t_button	kep_time;	
			t_button	kep_retrotime;
			t_button	node_next;	
			t_button	node_prev;	
		} b;
		t_button	buttons[sizeof(struct s_buttons) / sizeof(t_button)];
	};
	union
	{
		struct s_texts
		{
			t_text	node_control;	
		} t;
		t_text	texts[sizeof(struct s_texts) / sizeof(t_text)];
	};
};
#endif