/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sescanf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:57:53 by clovell           #+#    #+#             */
/*   Updated: 2024/04/05 18:06:43 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdbool.h>
#include <stddef.h>
#include "sescanf_int.h"
#include "libft.h"

char	sesc_fmt_gettype(char *fmt, char **type_start)
{
	char		*type;

	ft_strtol(fmt, &type, 10);
	if (fmt[-1] != '%')
		type = ((char *)"\0\0\0\0\0\0\0\0") + 4;
	if (type_start)
		*type_start = type;
	return (*type);
}

bool	sesc_nodelim_nextis(t_sescanf_ctx *ctx, char type)
{
	return (ctx->fmt[1] != '%' && *ctx->next_type == type);
}

static bool	sesc_handle_nonfmt(t_sescanf_ctx *ctx)
{
	bool	found_isspace;

	found_isspace = false;
	if (*ctx->fmt == '\v')
	{
		while (*ctx->current && ft_isspace(*ctx->current))
		{
			ctx->current++;
			(*ctx->read_ptr)++;
			found_isspace = true;
		}
		if (found_isspace == false && *ctx->current)
			return (true);
	}
	else
	{
		if (*ctx->current != *ctx->fmt)
			return (true);
		(*ctx->read_ptr)++;
		ctx->current++;
	}
	return (false);
}

int	ft_vsescanf(char *src, char *fmt, va_list *list)
{
	t_sescanf_ctx	ctx;

	ctx = (t_sescanf_ctx){.current = src, .fmt = fmt, .list = list, \
	.source = src, .read_ptr = &ctx.read_total};
	if (src == NULL || fmt == NULL)
		return (0);
	while (*ctx.fmt != '\0')
	{
		if (ctx.fmt[0] == '%' && ctx.fmt[1])
		{
			sesc_fmt_gettype(++ctx.fmt, &ctx.type);
			sesc_fmt_gettype(ctx.type + 2, &ctx.next_type);
			if (sesc_handle_fmt_type(&ctx) == -1)
				return (-ctx.found);
		}
		else
		{
			if (sesc_handle_nonfmt(&ctx))
				return (-ctx.found);
		}
		ctx.fmt++;
	}
	return (ctx.found);
}

int	ft_sescanf(char *from, char *fmt, ...)
{
	va_list	list;
	int		found;

	va_start(list, fmt);
	found = ft_vsescanf(from, fmt, &list);
	va_end(list);
	return (found);
}
/*
typedef struct s_vec2i
{
	int x;
	int y;
} t_vec2i;

struct s_mod_door {
	char	name[50];
	char	tex[50];
	t_vec2i	pos;
	int		speed;
	char	locked;
	char	closed;
};

#include <stdio.h>
int main(void)
{
	struct s_mod_door door;
	int found = ft_sescanf("DR\vdooor01,./tex,10,25,6,C,L,", \
	"DR\v%s,%s,%u,%u,%u,%c,%c\v",
		&door.name,
		&door.tex,
		&door.pos.x,
		&door.pos.y,
		&door.speed,
		&door.locked,
		&door.closed
	);

	printf("%s\n%s\n%u\n%u\n%u\n%c\n%c",
		door.name,
		door.tex,
		door.pos.x,
		door.pos.y,
		door.speed,
		door.locked,
		door.closed);
	if (found != 7)
		printf("failed %d", found);
	return (0);
}
*/