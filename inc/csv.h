/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csv.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 07:01:21 by clovell           #+#    #+#             */
/*   Updated: 2024/03/16 07:49:09 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef CSV_H
# define CSV_H
# include "libft.h"
# include "cerror.h"

# define CSV_LEN 1000

t_err	csv_next(char type, char **str, void *dst);
int		csv_clen(char **str);
void	csv_skip(char **str);
#endif