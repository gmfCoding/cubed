/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:33:09 by kmordaun          #+#    #+#             */
/*   Updated: 2024/03/16 10:29:27 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

char	*ft_strcat(char *dest, char *src)
{
	int i;
	int j;

	i = 0;
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

char	*ft_strcpy(char *s1, char *s2)
{
	int i;

	i = -1;
	while (s2[++i])
		s1[i] = s2[i];
	s1[i] = s2[i];
	return (s1);
}

int	strlen_nl(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] == s2[i]) && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	ft_isspace(int c)
{
	c = (unsigned char)c;
	if (c == '\t' || c == '\n' || c == '\v' \
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

void	remove_spaces(char *str)
{
	int	i;

	if (str == NULL)
		return ;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	ft_memmove(str, str + i, ft_strlen(str) - i + 1);
	i = ft_strlen(str) - 1;
	while (i >= 0 && ft_isspace(str[i]))
		i--;
	str[i + 1] = '\0';
}

int	is_empty_line(const char *line)
{
	int	i;

	if (!line)
	{
		return (1);
	}
	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}
