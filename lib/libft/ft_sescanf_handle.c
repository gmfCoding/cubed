/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sescanf_handle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:56:00 by clovell           #+#    #+#             */
/*   Updated: 2024/04/05 18:05:27 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdbool.h>
#include <stddef.h>
#include "sescanf_int.h"
#include "libft.h"

static bool	sesc_should_stop(t_sescanf_ctx *ctx)
{
	const char	*data = ctx->current;

	if (data == NULL || *data == '\0')
		return (true);
	if (*ctx->fmt == '\0')
		return (false);
	if (sesc_nodelim_nextis(ctx, 'u'))
		return (ft_isdigit(*data));
	else if (sesc_nodelim_nextis(ctx, 'd') || sesc_nodelim_nextis(ctx, 'i'))
		return (ft_isdigit(*data) || \
		((*data == '-' || *data == '+') && ft_isdigit(data[1])));
	else if (sesc_nodelim_nextis(ctx, 's') || sesc_nodelim_nextis(ctx, 'c'))
		return (ft_isspace(*data));
	else
		return (ft_isspace(*data) || *ctx->current == ctx->fmt[1]);
}

static int	sesc_handle_s(t_sescanf_ctx *ctx)
{
	char *const	dest = va_arg(*ctx->list, char *);
	int			i;

	i = 0;
	while (*ctx->current && !sesc_should_stop(ctx))
	{
		dest[i] = *ctx->current;
		ctx->current++;
		i++;
	}
	dest[i] = '\0';
	return (0);
}

static int	sesc_handle_num(t_sescanf_ctx *ctx)
{
	int *const	dest = va_arg(*ctx->list, int *);
	char		*end;
	int			base;
	int			value;

	base = 10;
	if (*ctx->type == 'x' || *ctx->type == 'p')
		base = 16;
	value = ft_strtol(ctx->current, &end, base);
	*dest = value;
	if (*ctx->type == 'u' && value < 0)
		return (-1);
	ctx->current = end;
	return (0);
}

static int	sesc_handle_c(t_sescanf_ctx *ctx)
{
	char *const	dest = va_arg(*ctx->list, char *);

	*dest = *ctx->current;
	if (*ctx->current)
		ctx->current++;
	return (0);
}

int64_t	sesc_handle_fmt_type(t_sescanf_ctx *ctx)
{
	if (*ctx->type == 'r')
	{
		ctx->read_ptr = va_arg(*ctx->list, int64_t *);
		*ctx->read_ptr = 0;
	}
	else if (*ctx->type == 's')
		ctx->read = sesc_handle_s(ctx);
	else if (*ctx->type == 'd' || *ctx->type == 'i' || *ctx->type == 'u' \
		|| *ctx->type == 'p' || *ctx->type == 'x')
		ctx->read = sesc_handle_num(ctx);
	else if (*ctx->type == 'c')
		sesc_handle_c(ctx);
	else
		return (-1);
	if (ctx->read_ptr && ctx->read > 0)
		*ctx->read_ptr += ctx->read;
	if (ctx->read >= 0)
		ctx->found++;
	return (ctx->read);
}
