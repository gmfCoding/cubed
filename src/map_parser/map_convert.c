/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_convert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:00:20 by kmordaun          #+#    #+#             */
/*   Updated: 2023/11/27 18:24:33 by kmordaun         ###   ########.fr       */
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
#include <stddef.h>
#include <errno.h>


#define TAB_SIZE 4
#define	FILE_TYPE ".txt"
#define MAP_MODIFICATION_SIZE 100
#define MAP_MAX_XY 200
#define MAP_MAX_X MAP_MAX_XY
#define MAP_MAX_Y MAP_MAX_XY
typedef float	t_vecd;

//((t_ex_action)g_mapsymbols[i])(str + (mod_strlen(mapsymbols[i]) + 1) , world, map);
//

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

typedef enum	e_modtype
{
	NORTH_TEXTURE,
	SOUTH_TEXTURE,
	WEST_TEXTURE,
	EAST_TEXTURE,
	FLOOR_COLOR,
	CEILING_COLOR,
}				t_modtype;

typedef struct	s_tile
{
	t_tiletype	type; // 1 or 0?
}				t_tile;

typedef struct	s_mod
{
	t_modtype	type;
	char*		content;
}			t_mod;

typedef struct	s_map
{
	t_tile	tiles[MAP_MAX_X * MAP_MAX_Y];
	t_mod	mods[MAP_MODIFICATION_SIZE];
	t_vec2		s_pos;
	uint8_t		width;
	uint8_t		height;
	float		s_angle;
	int			color_ceiling;
	int			color_floor;
}				t_map;

typedef struct	s_player
{
	t_vec2	pos;
	t_vec2	dir;
	t_vec2	plane;

	double	moveSpeed;
	double	rotSpeed;
}		t_player;

typedef struct	s_world
{
	t_map		map;
	t_player	player;

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

char *const    g_mapsymbols[] = {
	"NO",
	"SO",
	"WE",
	"EA",
	"F",
	"C",
};

void	fn_NO(char *content, int mod_pos, t_world *world, t_map *map);
void	fn_SO(char *content, int mod_pos, t_world *world, t_map *map);
void	fn_WE(char *content, int mod_pos, t_world *world, t_map *map);
void	fn_EA(char *content, int mod_pos, t_world *world, t_map *map);
void	fn_F(char *content, int mod_pos, t_world *world, t_map *map);
void	fn_C(char *content, int mod_pos, t_world *world, t_map *map);

typedef void	(*t_ex_action)(char *, int, t_world *, t_map *);

t_ex_action const    g_mapfuncs[] = {
     &fn_NO,
     &fn_SO,
     &fn_WE,
     &fn_EA,
     &fn_F,
     &fn_C,
};

//header stuff^^^^





//utilsVV
int	mod_strlen(const char *str)
{
	int	i;

	i = 0;
	while(str[i] != '\0' && str[i] != '\n')
		i++;
	return (i);
}

int	ft_lstremove(t_list **lst, t_list *target, void (*del)(void*))
{
	while (*lst != NULL)
	{
		if (*lst == target)
		{
			*lst = target->next;
			ft_lstdelone(target, del);
			return (1);
		}
		lst = &(*lst)->next;
	}
	return (0);
}

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

int	ft_isspace(int c)
{
	c = (unsigned char)c;
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

void remove_spaces(char *str)
{
	int i;


	if (str == NULL)
		return ;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	memmove(str, str + i, ft_strlen(str) - i + 1);
	i = ft_strlen(str) - 1;
	while (i >= 0 && ft_isspace(str[i]))
		i--;
	str[i + 1] = '\0';
}

int	is_empty_line(const char *line)
{
	int	i;
	
	if(!line)
		return (1);
	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}
//standard utils^^

//map utilsVV

int	map_skip_over_modifiers(char *content)
{
	int	i;
//	char	temp[3];
	
	i = -1;
//	strncpy(temp, content, 2);
//	temp[2] = '\0';
	while (++i < sizeof(g_mapsymbols) / 8)
	{
		if (strncmp(g_mapsymbols[i], content, mod_strlen(g_mapsymbols[i])) == 0)
			return (1);
//		if (strcmp(g_mapsymbols[i], temp) == 0)
//			return (1);
//		printf("%s\n", g_mapsymbols[i]);
	}
	return (0);
}

int	map_starting_tile(char *content)
{
	int	i;
	
//	if (!content)
	i = 0;
	while (ft_isspace(content[i]))
		i++;
	if(content[i] == '1')
		return (1);
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

void	map_print(t_map *map)
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

void	remove_empty_lines(t_list **raw_map_file)
{
	t_list	*curr;
	t_list	*temp;

	int lines = (intptr_t)raw_map_file[0]->content;
	*raw_map_file = raw_map_file[0]->next;
	curr = *raw_map_file;
	while(curr != NULL && curr->next != NULL) 
	{
		if (map_starting_tile((char *)curr->content) == 1)
			break ;
		if (is_empty_line(curr->next->content) == 1)
		{
			temp = curr->next;
			curr->next = temp->next;
			ft_lstdelone(temp, free);
		}
		else
			curr = curr->next;
	}
}


//map utils^^

//map size

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
// map size^^

//map tiles VV and boarder

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


//map checkers VV

int	map_check_player(char *content)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (content[i])
	{
		if (content[i] == 'N' || content[i] == 'S')
			count++;
		if (content[i] == 'E' || content[i] == 'W')
			count++;
		i++;
	}
	return (count);
}

int	map_check_invalid_char(char *content)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (content[i])
	{
		if (content[i] != 'N' && content[i] != 'S' && \
			content[i] != 'E' && content[i] != 'W' && \
			content[i] != '0' && content[i] != '1' && \
			content[i] != ' ' && content[i] != '\n')
			count++;
		i++;
	}
	return (count);
}

int	map_check_surrounded(t_map *map_temp, int pos)
{
	if (pos >= 0 && pos <= (map_temp->width * map_temp->height) && map_temp->tiles[pos].type != WALL && map_temp->tiles[pos].type != EMPTY)
		return (1);//can return and print char position and tile type? and handle exit funtion here
	if (!(pos >= 0 && pos <= (map_temp->width * map_temp->height)) || map_temp->tiles[pos].type == WALL)
		return (0);
	if (map_temp->tiles[pos].type == EMPTY)
		map_temp->tiles[pos].type = WALL;
	if (map_check_surrounded(map_temp, pos - map_temp->width) == 1)
		return (1);
	if (map_check_surrounded(map_temp, pos + map_temp->width) == 1)
		return (1);
	if (map_check_surrounded(map_temp, pos - 1) == 1)
		return (1);
	if (map_check_surrounded(map_temp, pos + 1) == 1)
		return (1);
	return (0);
}

//map checker ^^

// map element checker VV

int	map_check_element_colors(char *str)
{
	int	i;
	int	j;
	char	**rgb;
	int	syntax_check;

	i = 0;
	syntax_check = 0;
	while (*str == ' ')
		str++;
	rgb = ft_split(str, ',');
	while(rgb[i])
	{
		if (atoi(rgb[i]) > 255 || atoi(rgb[i]) < 0 || is_empty_line(rgb[i]))
			syntax_check = 1;
		j = 0;
		while (rgb[i][j] && rgb[i][j] != '\n' && rgb[i][j] != ' ')
			if (!ft_isdigit(rgb[i][j++]))
				syntax_check = 1;
		free(rgb[i++]);
	}
	if (i != 3)
		syntax_check = 1;
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
		syntax_check = 1;
	if (strcmp(FILE_TYPE, ft_strrchr(str, '.')))
		syntax_check = 1;
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
				return (1);
		if (str[2] && !strncmp(str, "NO", 2) || !strncmp(str, "SO", 2) || !strncmp(str, "WE", 2) || !strncmp(str, "EA", 2))
			if (map_check_element_texture(str + 3) == 1)
				return (1);
		curr = curr->next;
	}
	return (0);
}

//map element_checker ^^


//can be apart of other map checker fucntionVV

void	map_check_err(t_map *map_temp, t_list *temp, t_list *raw_map_file, char *map_str)
{
	t_list	*curr;
	int	count_players;
	int	count_invalid_char;

	count_players = 0;
	count_invalid_char = 0;
	curr = temp;
	while (curr != NULL && curr->content != NULL)
	{
		if (is_empty_line((char *)curr->content) && ((char *)curr->content)[0] != ' ')
			printf("empty line in map\n");
		count_players += map_check_player((char *)curr->content);
		count_invalid_char += map_check_invalid_char((char *)curr->content);
		curr = curr->next;
	}
	if (map_check_elements(raw_map_file) == 1)
		printf("element format incorrect\n");//replace with error handler
	if (count_players > 1 || count_players < 1)
		printf("incorrect player count\n");
	if (count_invalid_char > 0)
		printf("incorrect char in map\n");
	if (map_check_surrounded(map_temp, 0) == 1)
		printf("boarder_not_valid\n");
	if (strcmp(".cub", ft_strrchr(map_str, '.')) != 0)
		printf("incorrect file type\n");
}

void	map_check_setup(t_list *curr, t_list *raw_map_file, char *map_str)
{
	t_list	*temp;
	t_map	map_temp;
	int		index;

	index = 0;
	temp = curr;
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
//	map_print(&map_temp);//dont need this
//	printf("\n");
	map_check_err(&map_temp, temp, raw_map_file, map_str);
}

//can be apart of other map checker above ^^

//player setup VV


void	player_rot_setup(char rot, t_player *player)
{
	if (rot == 'N')
	{
		player->dir.x = 0;
		player->dir.y = 1;
	}
	else if (rot == 'S')
	{
		player->dir.x = 0;
		player->dir.y = -1;
	}
	else if (rot == 'E')
	{
		player->dir.x = 1;
		player->dir.y = 0;
	}
	else if (rot == 'W')
	{
		player->dir.x = -1;
		player->dir.y = 0;
	}
}

void	player_pos_setup(t_list *curr, t_player *player)
{
	char	*str;
	int	x;
	int	y;

	y = 0;
	while (curr != NULL && curr->content != NULL)
	{
		str = (char *)curr->content;
		x = -1;
		while (str[++x] != '\n' && str[x] != '\0')
		{
			if (str[x] == 'N' || str[x] == 'S' || str[x] == 'E' || str[x] == 'W')
			{
				player_rot_setup(str[x], player);
				player->pos.x = x;
				player->pos.y = y;
			}
		}
		y++;
		curr = curr->next;
	}
}

t_player	player_setup(t_list *curr, t_world *world)
{
	t_player player;

	player_pos_setup(curr, &player);
	player.moveSpeed = 0.05;
	player.rotSpeed = 0.001;
	return (player);
}
//player setup ^^

// texture ptr function

void	fn_NO(char *content, int mod_pos, t_world *world, t_map *map)
{
	(void)world;
	map->mods[mod_pos].type = NORTH_TEXTURE;
	map->mods[mod_pos].content = content;
}
void	fn_SO(char *content, int mod_pos, t_world *world, t_map *map)
{
	(void)world;
	map->mods[mod_pos].type = SOUTH_TEXTURE;
	map->mods[mod_pos].content = content;
}
void	fn_WE(char *content, int mod_pos, t_world *world, t_map *map)
{
	(void)world;
	map->mods[mod_pos].type = WEST_TEXTURE;
	map->mods[mod_pos].content = content;
}
void	fn_EA(char *content, int mod_pos, t_world *world, t_map *map)
{
	(void)world;
	map->mods[mod_pos].type = EAST_TEXTURE;
	map->mods[mod_pos].content = content;
}
//map_textur ptr func

//map_color ptr func

void	fn_F(char *content, int mod_pos, t_world *world, t_map *map)
{
	(void)world;
	map->mods[mod_pos].type = FLOOR_COLOR;
	map->mods[mod_pos].content = content;
}
void	fn_C(char *content, int mod_pos, t_world *world, t_map *map)
{
	(void)world;
	map->mods[mod_pos].type = CEILING_COLOR;
	map->mods[mod_pos].content = content;
}
//map_color ptr func^^

//modifiers setupVV

void	map_modifier_setup(t_list *raw_map_file, t_map *map, t_world *world)
{
	t_list	*curr;
	char	*str;
	int		i;
	int		mod_pos;

	mod_pos = 0;
	curr = raw_map_file;
	while (curr != NULL && curr->content != NULL)
	{
		str = (char *)curr->content;
		remove_spaces(str);
		i = -1;
		while (++i < (sizeof(g_mapsymbols) / sizeof(g_mapsymbols[0])))
		{
			if (strncmp(g_mapsymbols[i], str, mod_strlen(g_mapsymbols[i])) == 0)
				((t_ex_action)g_mapfuncs[i])(str + (mod_strlen(g_mapsymbols[i]) + 1), mod_pos++, world, map);
		}
		curr = curr->next;
	}
}

//modifiers setup^^


//the rest can stay
t_map	map_init(t_map *map, char *map_str, t_world *world)
{
	t_list	*curr;
	t_list	*raw_map_file;
	int		index;

	raw_map_file = ft_lst_readfile(map_str);
	if (raw_map_file == NULL)
		exit(2);//returnrapper here
	index = 0;
	remove_empty_lines(&raw_map_file);
	replace_tabs(raw_map_file);
	curr = raw_map_file;
	while (curr != NULL && map_skip_over_modifiers((char *)curr->content) == 1)
		curr = curr->next;
	map_check_setup(curr, raw_map_file, map_str);
	map->width = map_width_size(curr);
	map->height = map_height_size(curr);
	world->player = player_setup(curr, world);
	while (curr != NULL && curr->content != NULL)
	{
		index += map_tiles(map, (char *)curr->content, index);
		curr = curr->next;
	}
	map_modifier_setup(raw_map_file, map, world);
	//free raw_map_file
	return (*map);
}

t_map	map_parse(int argc, char **argv, t_world *world)
{
	t_map	map;
	char	*map_str;

	if (argc == 1)
		map_str = "map1.cub";
	else if (argc == 2)
		map_str = argv[1];
	else
		exit(2);
	map = map_init(&map, map_str, world);
	return (map);
}

t_world	world_preset(int argc, char **argv, t_world *world)
{
	world->map = map_parse(argc, argv, world);
	

	return (*world);
}

int	main(int argc, char **argv)
{
//	int width = 960;
//	int height = 960;
//	void *mlx = mlx_init();
//	void *win = mlx_new_window(mlx, width, height, "SO_LONG");

	printf("BEGIN\n\n");

	t_world	world;
	world = world_preset(argc, argv, &world);
//	map_print(&world.map);
//	printf("\n%f\n", world.player.moveSpeed);
	return (0);


//	t_texture tex = texture_load(mlx, "assets/debug.xpm");
//	unsigned char alpha = pixel_get(tex, 0, 0) >> 24 & 0xFF;
//	printf("%x\n", alpha);
//	mlx_put_image_to_window(mlx, win, tex.img, 0 ,0);
//	mlx_loop(mlx);
}

/*
t_map	map_init(t_map *map, char *map_str)
{
	t_list	*curr;
	t_list	*raw_map_file;
	int		index;

	raw_map_file = ft_lst_readfile(map_str);
	if (raw_map_file == NULL)
		exit(2);//returnrapper here
	index = 0;
	curr = raw_map_file;
	int lines = (intptr_t)curr->content;
	curr = curr->next;
	remove_empty_lines(&raw_map_file);
	replace_tabs(curr);
	while (curr != NULL && map_starting_tile((char *)curr->content) == 1)
		curr = curr->next;
	map_check_setup(curr, raw_map_file, map_str);
	map->width = map_width_size(curr);
	map->height = map_height_size(curr);
	while (curr != NULL && curr->content != NULL)
	{
		index += map_tiles(map, (char *)curr->content, index);
		printf("%s", (char *)curr->content);// dont need this
		curr = curr->next;
	}
	return (*map);
}
*/
//	printf("%s", (char *)curr->content);// dont need this

