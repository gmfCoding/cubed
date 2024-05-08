/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_int.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:32:41 by clovell           #+#    #+#             */
/*   Updated: 2024/05/08 14:33:02 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_INT_H
# define GET_NEXT_LINE_INT_H

typedef struct s_gnl_state
{
	char	*store;
	char	*prev;
	int		prev_fd;
	int		remaining;
}			t_gnl_state;

#endif