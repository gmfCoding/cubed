/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cerror.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 00:33:50 by clovell           #+#    #+#             */
/*   Updated: 2023/11/22 20:47:24 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "cerror.h"
#include "libft.h"

char	*errormsg(t_cerror error)
{
	char *const	message[] = { 
	[ERR_BADPARAM] = "Supplied parameter not valid",
	[ERR_STRDUP] = "String duplication failed, out of memory.",
	[ERR_MALLOCFAIL] = "Ran out of available heap memory.",
	[ERR_NULLPARAM] = "Supplied parameter cannot be null.",
	[ERR_NOFILE] = "Fatal error occured, no file or directory.",
	};

	return (message[error]);
}

void	ft_assert(int cond, t_cerror error, char *file, int line)
{
	if (cond)
		ft_errx(error, file, line);
}

static void	ft_putbacktrace(void);

void	ft_errx(t_cerror err, char *file, int line)
{
	ft_putstr_fd("[", STDERR_FILENO);
	ft_putnbr_fd(err, STDERR_FILENO);
	ft_putstr_fd("] ", STDERR_FILENO);
	ft_putstr_fd(errormsg(err), STDERR_FILENO);
	ft_putstr_fd(" (", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd(":", STDERR_FILENO);
	ft_putnbr_fd(line, STDERR_FILENO);
	ft_putstr_fd(")\n", STDERR_FILENO);
	ft_putbacktrace();
	exit(err);
}

// XXX FT_PUTBACKTRACE XXX
// USE FIRST VARIANT FOR NON-EVAL PURPOSES
// TODO COMMENT AND SWITCH TO SECOND VARIANT BEFORE EVAL

//FIRST VARIANT 
#include <execinfo.h>
static void ft_putbacktrace(void)
{
 	int nptrs;
    void *buffer[128];
	// XXX DEBUG FUNCTION, PLEASE USE SECOND VARIANT IN EVAL XXX
	// XXX COMMENT THIS FUNCTION OUT WITH EXECINFO.H XXX
    nptrs = backtrace(buffer, 128);
	ft_putstr_fd("Backtrace: \n", STDERR_FILENO);
    backtrace_symbols_fd(buffer, nptrs, STDOUT_FILENO);
}

// SECOND VARIANT
// static void	ft_putbacktrace(void)
// {
// 	ft_putstr_fd("backtrace unavailable!\n", STDERR_FILENO);
// }
