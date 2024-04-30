/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:33:09 by kmordaun          #+#    #+#             */
/*   Updated: 2024/04/18 17:12:55 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

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
	int	i;

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

int	ft_isupper(int c)
{
	return (c >= 'A' && c <= 'Z');
}

void remove_spaces(char *new_str)
{
	char	*str;
	size_t	new_len;
	size_t	i;

	str = ft_strdup(new_str);
	new_len = 0;
	i = -1;
	while(str[i + 1] == ' ')
		i++;
	while (ft_isupper(str[++i]))
        new_str[new_len++] = str[i];
	new_str[new_len++] = ' ';
	while (str[++i])
	{
		if (ft_isspace(str[i]))
			continue;
		new_str[new_len++] = str[i];
	}
	new_str[new_len] = '\0';
	free(str);
}
/*
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
*/
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
