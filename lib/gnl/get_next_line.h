/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:15:39 by clovell           #+#    #+#             */
/*   Updated: 2023/04/19 16:11:01 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>

size_t	gnl_strlcpy(char *dst, const char *src, size_t dstsize);
char	*gnl_strchr(const char *s, int c);
void	*gnl_memcpy(void *dst, const void *src, size_t size);
char	*gnl_strjoin(char const *s1, char const *s2);
char	*gnl_strldup(const char *source, size_t len);
char	*get_next_line(int fd);
#endif
