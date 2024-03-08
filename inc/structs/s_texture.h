/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_texture.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 03:32:52 by clovell           #+#    #+#             */
/*   Updated: 2024/03/09 03:32:59 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef S_TEXTURE_H
# define S_TEXTURE_H

typedef struct s_texture
{
	void	*img;
	int		*data;
	int		width;
	int		height;
	int		bpp;
	int		line_size;
	int		endian;
}				t_texture;
#endif