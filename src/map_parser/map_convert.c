/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_convert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:00:20 by kmordaun          #+#    #+#             */
/*   Updated: 2023/11/21 22:00:01 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "cubed.h"
#include "./../../lib/libft/libft.h"
#include "./../../lib/gnl/get_next_line.h"
#include <inttypes.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>



#define MAP_MAX_XY 200
#define MAP_MAX_X MAP_MAX_XY
#define MAP_MAX_Y MAP_MAX_XY
typedef float	t_vecd;
typedef struct s_vec2
{
	t_vecd	x;
	t_vecd	y;
}				t_vec2;
/*
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;
*/
typedef enum	e_tiletype
{
	FLOOR,
	WALL,
	EMPTY,
}				t_tiletype;

typedef struct s_cellinfo
{
	char type; // 1 or 0?
}				t_cellinfo;

typedef struct	s_map
{
	t_cellinfo	cells[MAP_MAX_X * MAP_MAX_Y];
	t_vec2		s_pos;
	uint8_t		width;
	uint8_t		height;
	float		s_angle;
	int			color_ceiling;
	int			color_floor;
	char*		

}				t_map;

typedef struct	s_world
{
	t_map map;

	//t_entity	map_entities[MAX_ENTITIES];
	//int ent_count;
}				t_world;


t_list	*ft_lst_readfile(const char *path)
{
	t_list	*first;
	t_list	*next;
	char	*line;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	first = ft_lstnew((void *)0);
	next = first;
	line = get_next_line(fd);
	while (line)
	{
		next->next = ft_lstnew(line);
		next = next->next;
		(first->content)++;
		line = get_next_line(fd);
	}
	close (fd);
	next->next = ft_lstnew(NULL);
	return (first);
}

t_world	world_preset(int argc, char **argv)
{
	t_world	world;
	t_list	*raw_map_file;
	t_list	*curr;
	raw_map_file = ft_lst_readfile("map1.cub");
	curr = raw_map_file;
	if (curr == NULL)
		return ;
	int lines = (intptr_t)curr->content;
		curr = curr->next;
	while (curr != NULL && curr->content != NULL)
	{

		printf("%s", (char *)curr->content);
		curr = curr->next;
	}

	return (world);
}

int	main(int argc, char **argv)
{
//	int width = 960;
//	int height = 960;
//	void *mlx = mlx_init();
//	void *win = mlx_new_window(mlx, width, height, "SO_LONG");

	printf("BEGIN\n\n");

	t_world	world;
	world = world_preset(argc, argv);
	return (0);


//	t_texture tex = texture_load(mlx, "assets/debug.xpm");
//	unsigned char alpha = pixel_get(tex, 0, 0) >> 24 & 0xFF;
//	printf("%x\n", alpha);
//	mlx_put_image_to_window(mlx, win, tex.img, 0 ,0);
//	mlx_loop(mlx);
}
