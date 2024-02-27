#ifndef MAP_H
# define MAP_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <inttypes.h>
# include "player.h"
# include "enemy.h"
# include "libft.h"
# include "modifiers.h"
# include "events.h"
# define TAB_SIZE 4
# define FILE_TYPE ".xpm"
# define MAP_MODIFICATION_SIZE 100
# define MAP_MAX_XY 200
# define MAP_MAX_X MAP_MAX_XY
# define MAP_MAX_Y MAP_MAX_XY
# define G_MAPTABLE_LEN 6
typedef enum	e_tiletype
{
	FLOOR,
	WALL,
	EMPTY,
	MODIFIED,
	INVALID,
	DOOR,
}				t_tiletype;

typedef struct	s_tile
{
	t_tiletype	type;
	uint8_t		tex;
	int8_t		vis;
	char		sp_count;
	char		sprite[4];
}				t_tile;

typedef struct	s_map
{
	t_tile		tiles[MAP_MAX_X * MAP_MAX_Y];
	t_mod		mods[MAP_MODIFICATION_SIZE];
	t_vec2		s_pos;
	uint8_t		width;
	uint8_t		height;
	int			color_ceiling;
	int			color_floor;
}				t_map;

typedef uint16_t t_tid;
typedef struct s_sprite t_sprite;

struct	s_sprite
{
	t_tid		tex;
	t_vec2		pos;
	t_vec2		s1;
	t_vec2		s2;
};

typedef struct	s_world
{
	t_map		map;

	t_entity	ent[MAX_ENT];//this might be getting phased out but im still using it for the moment
	t_entity_2	ent_2[MAX_ENT];
	int		ent_count;
	t_enemy		enemy;
	t_sprite	sprite[MAX_ENT];
	char		sp_amount;
}			t_world;

	// MAP PARSER //
t_tiletype	get_tiletype(char c);

//t_map		map_parse(int argc, char **argv, t_game *game);
void		map_parse(int argc, char **argv, t_game *game);
int		map_width_size(t_list *curr);
int		map_height_size(t_list *curr);
int		map_check_elements(t_list *raw_map_files);
int		map_tiles_surround(t_map *map, char *content, int index);
int		map_skip_over_modifiers(char *content);
int		map_starting_tile(char *content);
int		map_tiles(t_map *map, char *content, int index);
void		map_print(t_map *map);
void		map_check_setup(t_list *curr, t_list *raw_map_file, char *map_str);
void		map_default_map_init(t_game *game);

	// MEMORY //
t_list		*ft_lst_readfile(const char *path);
void		deallocate_list(t_list **raw_map_file);
void		free_str_array(char **str);
void		free_content(t_game *game);

	// MAP_UTILS //
void		replace_tabs(t_list *curr);
void		remove_empty_lines(t_list **raw_map_file);
int		mod_strlen(const char *str);
int		ft_strcmp(char *s1, char *s2);
int		ft_isspace(int c);
void		remove_spaces(char *str);
int		is_empty_line(const char *line);
int		error_return(char *msg, int exit_code, int print_error, t_list **free_me);
int		error_with(char *msg, int value, int print_error);

#endif
