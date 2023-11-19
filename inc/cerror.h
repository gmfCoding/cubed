/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:14:16 by clovell           #+#    #+#             */
/*   Updated: 2023/10/17 12:00:50 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

typedef enum e_cerror	t_cerror;

enum e_cerror
{
	ERR_NOERR = 0,
	ERR_MALLOCFAIL,
	ERR_BADPARAM,
	ERR_NULLPARAM,
	ERR_STRDUP,
	ERR_NOFILE
};

char	*errormsg(t_cerror error);
void	ft_errx(t_cerror a, char *file, int line);
void	ft_assert(int cond, t_cerror error, char *file, int line);

#endif
