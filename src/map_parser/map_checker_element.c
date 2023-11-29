/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker_element.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:00:56 by kmordaun          #+#    #+#             */
/*   Updated: 2023/11/29 16:02:01 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	map_check_element_colors(char *str)
{
	int		i;
	int		j;
	char	**rgb;
	int		syntax_check;

	i = 0;
	syntax_check = 0;
	while (*str == ' ')
		str++;
	rgb = ft_split(str, ',');
	while (rgb[i])
	{
		if (ft_atoi(rgb[i]) > 255 || ft_atoi(rgb[i]) < 0 \
			|| is_line(rgb[i]))
			syntax_check = error_with("valueRange -", 1, 1);
		j = 0;
		while (rgb[i][j] && rgb[i][j] != '\n' && rgb[i][j] != ' ')
			if (!ft_isdigit(rgb[i][j++]))
				syntax_check = error_with("nonDigit -", 1, 1);
		free(rgb[i++]);
	}
	if (i != 3)
		syntax_check = error_with("commaCount -", 1, 1);
	free(rgb);
	return (syntax_check);
}

/* str cant have spaces on end currently unsure if i should add that or not */
int	map_check_element_texture(char *str)
{
	int	texture_file;
	int	syntax_check;
	int	i;

	i = 0;
	syntax_check = 0;
	str[ft_strlen(str) - 1] = '\0';
	while (*str == ' ')
		str++;
	texture_file = open(str, O_RDONLY);
	if (texture_file == -1)
		syntax_check = error_with("failedOpen -", 1, 1);
	if (ft_strcmp(FILE_TYPE, ft_strrchr(str, '.')))
		syntax_check = error_with("fileType -", 1, 1);
	close(texture_file);
	return (syntax_check);
}

int	map_check_elements(t_list *raw_map_files)
{
	t_list	*curr;
	char	*str;

	curr = raw_map_files;
	while (curr != NULL && curr->content != NULL)
	{
		str = (char *)curr->content;
		if (map_starting_tile(str) == 1)
			break ;
		if (str[2] && str[1] != ' ' && str[2] != ' ')
			return (1);
		if (str[1] && (str[0] == 'C' || str[0] == 'F') && str[1] == ' ')
			if (map_check_element_colors(str + 2) == 1)
				return (error_with("Color", 1, 0));
		if (str[2] && !ft_strncmp(str, "NO", 2) || !ft_strncmp(str, "SO", 2) \
			|| !ft_strncmp(str, "WE", 2) || !ft_strncmp(str, "EA", 2))
			if (map_check_element_texture(str + 3) == 1)
				return (error_with("Texture", 1, 0));
		curr = curr->next;
	}
	return (0);
}
