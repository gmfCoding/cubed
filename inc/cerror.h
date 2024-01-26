/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cerror.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:14:16 by clovell           #+#    #+#             */
/*   Updated: 2024/01/26 23:03:23 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CERROR_H
# define CERROR_H
# include <stddef.h>

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

// Null parameter (argument)
# define E_P "Null argument supplied"
# define E_M "Malloc failure"
# define E_L __LINE__
# define E_F __FILE__

char	*errormsg(t_cerror error);
void	ft_errx(t_cerror a, char *file, int line);
void	ft_assert(int cond, t_cerror error, char *file, int line);
void	ft_asrt(int cond, char *err);

#endif
