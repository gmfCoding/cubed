/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_func_door_setup.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 18:56:18 by kmordaun          #+#    #+#             */
/*   Updated: 2023/12/01 19:23:12 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

/*
typedef struct s_door
{
	char	name[NAME_SIZE];
	t_vec2	pos;
	float	speed;
	bool	state;
	bool	locked;
	bool	vertical;
}		t_door;

typedef struct	s_map_entities
{
	t_door	doors[MAX_DOORS];

}

typedef struct	s_world
{
	t_map		map;
	t_player	player;

	t_entity	entities;
	//int ent_count;
}	
*/
/*NAME,TEXTURE,XPOS,YPOS,SPEED,CLOSED,LOCKED,VERTICLE */
void	mod_gen_dr(char *content, int index, t_world *world, t_map *map)
{
	static int	dr_count = 0;
	printf("%s\n", content);
	int	i;
	char	**dr;
	char	*texture;

	i = -1;
	map->mods[index].type = DOOR;
	dr = ft_split(content, ',');
	while (dr[0][++i] && i < NAME_SIZE)
		world->ent->doors[dr_count].name[i] = dr[0][i];
	map->mods[index].content = ft_strdup(dr[1]);
	world->ent->doors[dr_count].pos.x = ft_atoi(dr[2]);
	world->ent->doors[dr_count].pos.y = ft_atoi(dr[3]);
	world->ent->doors[dr_count].speed = ft_atoi(dr[4]);
	world->ent->doors[dr_count].closed = (dr[5][0] == 'C') ? true : false;
	world->ent->doors[dr_count].locked = (dr[6][0] == 'L') ? true : false;
	world->ent->doors[dr_count].vertical = (dr[7][0] == 'V') ? true : false;



	printf("%s\n", world->ent->doors[dr_count].name);
	printf("%s\n", map->mods[index].content);
	printf("%f\n", world->ent->doors[dr_count].pos.x);
	printf("%f\n", world->ent->doors[dr_count].pos.y);
	printf("%d\n", world->ent->doors[dr_count].speed);
	printf("%d\n", world->ent->doors[dr_count].closed);
	printf("%d\n", world->ent->doors[dr_count].locked);
	printf("%d\n", world->ent->doors[dr_count].vertical);
//	free(map->mods[index].content);









	free_str_array(dr);
	
}
