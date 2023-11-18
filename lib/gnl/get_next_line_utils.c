/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:16:39 by clovell           #+#    #+#             */
/*   Updated: 2023/04/19 16:10:52 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

size_t	gnl_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	while (src[i] != '\0')
		i++;
	while (j < i && j + 1 < dstsize)
	{
		dst[j] = src[j];
		j++;
	}
	if (dstsize > 0)
		dst[j] = '\0';
	return (i);
}

char	*gnl_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (0);
}

void	*gnl_memcpy(void *dst, const void *src, size_t size)
{
	size_t	idx;

	if (dst == NULL && src == NULL)
		return (NULL);
	idx = 0;
	while (idx < size)
	{
		((char *)dst)[idx] = ((char *)src)[idx];
		idx++;
	}
	return (dst);
}

char	*gnl_strjoin(char const *s1, char const *s2)
{	
	size_t	s1len;
	size_t	s2len;
	char	*dst;

	s1len = 0;
	s2len = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	while (s1[s1len] != '\0')
		s1len++;
	while (s2[s2len] != '\0')
		s2len++;
	dst = malloc(s1len + s2len + 1);
	if (dst == NULL)
		return (NULL);
	gnl_memcpy(dst, s1, s1len);
	gnl_strlcpy(dst + s1len, s2, s2len + 1);
	return (dst);
}

/* Copies the content of source into dest by len. */
char	*gnl_strldup(const char *source, size_t len)
{
	char	*dest;

	dest = malloc((len + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	gnl_strlcpy(dest, source, len + 1);
	return (dest);
}
