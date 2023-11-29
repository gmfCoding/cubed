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

#include "cubed.h"

int	error_with(char *msg, int value, int print_error)
{
	if (print_error)
		fprintf(stderr, "Error\n");
	if (msg)
		fprintf(stderr, "%s ", msg);
	return (value);
}

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
