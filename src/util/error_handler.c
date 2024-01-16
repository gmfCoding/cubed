/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:31:42 by kmordaun          #+#    #+#             */
/*   Updated: 2023/11/29 15:32:59 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

/*
 * error funtions used to print error msgs to console
 * Error and a newline must be printed first so a value or exit code
 * passed in and 1 or 0 is passed whether to print error or not
 * can be expanded on
 */
int	error_with(char *msg, int value, int print_error)
{
	if (print_error)
		fprintf(stderr, "Error\n");
	if (msg)
		fprintf(stderr, "%s ", msg);
	return (value);
}

/*
 * error funtions used to print error msgs to console
 * Error and a newline must be printed first so a value or exit code
 * passed in and 1 or 0 is passed whether to print error or not
 * can be expanded on
 *
 * was planning on using exit code as a way of telling the
 * function on what to free
 * currently it only frees the link_list if an error is found in 
 * map and elements but there would be leeks if used later on 
 * because the content is strdup and used in game
 */
int	error_return(char *msg, int exit_code, int print_error, t_list **free_me)
{
	if (print_error)
		fprintf(stderr, "Error\n");
	if (msg && ft_strncmp(msg, ":", 1) == 0)
	{
		fprintf(stderr, "- %s.", msg);
		deallocate_list(free_me);
		exit(exit_code);
	}
	if (msg)
		fprintf(stderr, "- %s.", msg);
	exit(exit_code);
}
