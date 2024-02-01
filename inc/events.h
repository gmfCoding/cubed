#ifndef EVENTS_H
# define EVENTS_H

typedef struct	s_world t_world;
typedef struct	s_map t_map;

void	event_player(t_game *game);
void	event_interact(t_game *game);
void	event_display_ui(t_game *game);
#endif
