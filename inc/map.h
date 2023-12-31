#ifndef MAP_H
# define MAP_H

# include "cubed.h"
# include "libft.h"

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

typedef enum e_mapissue
{
	MAP_COULD_NOT_OPEN,
	MAP_COULD_NOT_READ_ELEMENT,
	MAP_VALID,
	MAP_INVALID_CHAR,
	MAP_NOSTART,
	MAP_MISSINGTEXTURE,
 
}			t_mapissue;

typedef struct	s_tile
{
	t_tiletype	type;
	uint8_t		tex;
	bool		vis: 1;
}				t_tile;

typedef struct	s_mod
{
	t_modtype	type;
	char*		content;
}			t_mod;

typedef struct	s_map
{
	t_tile		tiles[MAP_MAX_X * MAP_MAX_Y];
	t_mod		mods[MAP_MODIFICATION_SIZE];
	t_vec2		s_pos;
	uint8_t		width;
	uint8_t		height;
	float		s_angle;
	int			color_ceiling;
	int			color_floor;
}				t_map;


typedef struct	s_world
{
	t_map		map;
	t_player	player;

	//t_entity	map_entities[MAX_ENTITIES];
	//int ent_count;
}				t_world;

typedef void	(*t_ex_action)(char *, int, t_world *, t_map *);


typedef void	(*t_ex_action)(char *, int, t_world *, t_map *);
extern char *const    g_mapsymbols[G_MAPTABLE_LEN];
extern t_ex_action const    g_mapfuncs[G_MAPTABLE_LEN];

t_player	player_setup(t_list *curr, t_world *world);
int	map_width_size(t_list *curr);
int	map_height_size(t_list *curr);
int	map_check_elements(t_list *raw_map_files);
t_map	map_parse(int argc, char **argv, t_world *world);
void	map_check_setup(t_list *curr, t_list *raw_map_file, char *map_str);
int	map_tiles_surround(t_map *map, char *content, int index);
int	map_skip_over_modifiers(char *content);
int	map_starting_tile(char *content);
int	map_tiles(t_map *map, char *content, int index);
void	replace_tabs(t_list *curr);
void	map_print(t_map *map);
void	remove_empty_lines(t_list **raw_map_file);
t_tiletype get_tiletype(char c);

void	modifier_setup(t_list *raw_map_file, t_map *map, t_world *world);
void	mod_gen_no(char *content, int mod_pos, t_world *world, t_map *map);
void	mod_gen_so(char *content, int mod_pos, t_world *world, t_map *map);
void	mod_gen_we(char *content, int mod_pos, t_world *world, t_map *map);
void	mod_gen_ea(char *content, int mod_pos, t_world *world, t_map *map);
void	mod_gen_c(char *content, int mod_pos, t_world *world, t_map *map);
void	mod_gen_f(char *content, int mod_pos, t_world *world, t_map *map);

int	mod_strlen(const char *str);
int	ft_strcmp(char *s1, char *s2);
int	ft_isspace(int c);
void remove_spaces(char *str);
int	is_line(const char *line);
int error_return(char *msg, int exit_code, int print_error, t_list **free_me);
int error_with(char *msg, int value, int print_error);
void	deallocate_list(t_list **raw_map_file);



void map_default_map_init(t_world *world);
#endif
