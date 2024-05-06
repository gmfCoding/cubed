/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:33:09 by kmordaun          #+#    #+#             */
/*   Updated: 2024/05/06 22:43:53 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

int	strlen_nl(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	return (i);
}

void	remove_spaces(char *new_str)
{
	char	*str;
	size_t	new_len;
	size_t	i;

	str = ft_strdup(new_str);
	new_len = 0;
	i = -1;
	while (str[i + 1] == ' ')
		i++;
	while (ft_isupper(str[++i]))
		new_str[new_len++] = str[i];
	new_str[new_len++] = ' ';
	while (str[++i])
	{
		if (ft_isspace(str[i]))
			continue ;
		new_str[new_len++] = str[i];
	}
	new_str[new_len] = '\0';
	free(str);
}
/*//only good for removing spaces at the start of the line
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
