/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_convert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:00:20 by kmordaun          #+#    #+#             */
/*   Updated: 2023/11/23 21:48:56 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "cubed.h"
#include "./../../lib/libft/libft.h"
#include "./../../lib/gnl/get_next_line.h"
#include <inttypes.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TAB_SIZE 4 
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
	INVALID
}				t_tiletype;

typedef struct	s_tile
{
	t_tiletype	type; // 1 or 0?
}				t_tile;

typedef struct	s_map
{
	t_tile	tiles[MAP_MAX_X * MAP_MAX_Y];
	t_vec2		s_pos;
	uint8_t		width;
	uint8_t		height;
	float		s_angle;
	int			color_ceiling;
	int			color_floor;
	char*		texture_n_wall;
	char*		texture_s_wall;
	char*		texture_w_wall;
	char*		texture_e_wall;
}				t_map;

typedef struct	s_world
{
	t_map map;

	//t_entity	map_entities[MAX_ENTITIES];
	//int ent_count;
}				t_world;

typedef enum	e_mapissue
{
		MAP_VALID,
		MAP_INVALID_CHAR,
		MAP_NOSTART,
		MAP_MISSINGTEXTURE,
		MAP_BADFILETYPE,
}		t_mapissue;

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

char *const    g_mapsymbols[] = {
	"NO",
	"SO",
	"WE",
	"EA",
	"S ",
	"F ",
	"C ",
};
//if(ft_strcmp(".cub", ft_strrchr(filePath, ".")) == 0)

int	map_starting_point(char *content)
{
	int	i;
	char	temp[3];
	
	i = -1;
	strncpy(temp, content, 2);
	temp[2] = '\0';
	while (++i < sizeof(g_mapsymbols) / 8)
	{
		//if (strncmp(g_mapsymbols[i], content, strlen(g_mapsymbols[i])))
		if (strcmp(g_mapsymbols[i], temp) == 0)
			return (1);
	//	printf("%s\n", g_mapsymbols[i]);
	}
	return (0);
}

void	replace_tabs(t_list *curr)
{
	int	i;
	int	j;
	char	*line;

	while (curr != NULL && curr->content != NULL)
	{
		line = (char *)curr->content;
		i = 0;
		while (line[i] != '\0')
		{
			if (line[i] == '\t')
			{
				memmove(&line[i + TAB_SIZE], &line[i + 1], strlen(&line[i + 1]) + 1);
				j = 0;
				while (j < TAB_SIZE)
					line[i + j++] = ' ';
				i += TAB_SIZE;
			}
			else
				i++;
		}
		curr = curr->next;
	}
}

int	map_width_size(t_list *curr)
{
	int i;

	i = 0;
	while (curr != NULL && curr->content != NULL)
	{
		if (strlen((char *)curr->content) > i)
		{
			if (((char *)curr->content)[strlen((char *)curr->content)] == '\n')
				i = strlen((char *)curr->content) - 1;
			else
				i = strlen((char *)curr->content);
		}
		curr = curr->next;
	}

	return (i-1);
}

int	map_height_size(t_list *curr)
{
	int i;

	i = 0;
	while (curr != NULL && curr->content != NULL)
	{
		i++;
		curr = curr->next;
	}
	return (i);
}

t_tiletype get_tiletype(char c)
{
	if (c == '0')
		return (FLOOR);
	else if (c == '1')
		return (WALL);
	else
		return (EMPTY);
}

int	map_tiles(t_map *map, char *content, int index)
{
	int	i;

	i = 0;
	while (i < map->width)
	{
		if (content[i] == '\0' || content[i] == '\n')
			while(i < map->width)
				map->tiles[index + i++].type = get_tiletype(' ');
		else
		{
			map->tiles[index + i].type = get_tiletype(content[i]);
			i++;
		}
	}
	return (i);
}

void	print_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < (map->width * map->height))
	{
		if (i % map->width == 0)
			printf("\n");
		printf("%d", map->tiles[i].type);
		i++;
	}
}

int	map_tiles_surround(t_map *map, char *content, int index)
{
	int	i;

	i = 0;
	map->tiles[index].type = get_tiletype(' ');
	while (i < (map->width))
	{
		if (content[i] == '\0' || content[i] == '\n')
			while(i < map->width)
				map->tiles[(index + 1) + i++].type = get_tiletype(' ');
		else
		{
			map->tiles[(index + 1) + i].type = get_tiletype(content[i]);
			i++;
		}
	}
	return (i);
}



void	map_check_errors(t_map *map, t_list *raw_map_file)
{
	t_list	*curr;
	t_map	map_temp;
	int		index;
	index = 0;
	curr = raw_map_file;
	int lines = (intptr_t)curr->content;
	curr = curr->next;

	while (curr != NULL && map_starting_point((char *)curr->content) == 1)
	{
		curr = curr->next;
	}
	map_temp.width = (map_width_size(curr) + 2);
	map_temp.height = (map_height_size(curr) + 2);
	while (index < map_temp.width)
		map_temp.tiles[index++].type = get_tiletype(' ');
	while (curr != NULL && curr->content != NULL)
	{
		index += map_tiles_surround(&map_temp, (char *)curr->content, index);
		curr = curr->next;
	}
	while (++index < ((map_temp.width * map_temp.height) + map_temp.width))
		map_temp.tiles[index].type = get_tiletype(' ');
	printf("MAPWIDTH%d  MAPHEIGHT%d  \n", map_temp.width, map_temp.height);
	print_map(&map_temp);
}

t_map	map_init(t_map *map, t_list *raw_map_file)
{
	t_list	*curr;
	int		index;

	index = 0;
	curr = raw_map_file;
	int lines = (intptr_t)curr->content;
	curr = curr->next;
	replace_tabs(curr);
	while (curr != NULL && map_starting_point((char *)curr->content) == 1)
		curr = curr->next;
	map->width = map_width_size(curr);
	map->height = map_height_size(curr);
	printf("MAPWIDTH%d  MAPHEIGHT%d  \n", map->width, map->height);
	while (curr != NULL && curr->content != NULL)
	{
		index += map_tiles(map, (char *)curr->content, index);
		printf("%s", (char *)curr->content);
		curr = curr->next;
	}
	map_check_errors(map, raw_map_file);
	return (*map);
}

t_map	map_parse(int argc, char **argv)//get the map done first
{
	t_map	map;
	t_list	*raw_map_file;

	if (argc == 1)
		raw_map_file = ft_lst_readfile("map1.cub");
	else if (argc == 2)
		raw_map_file = ft_lst_readfile(argv[1]);
	else
		exit(2);
	map = map_init(&map, raw_map_file);
	return (map);
}

t_world	world_preset(int argc, char **argv)
{
	t_world	world;

	world.map = map_parse(argc, argv);
	print_map(&world.map);

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
