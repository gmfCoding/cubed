#ifndef EVENTS_H
# define EVENTS_H

typedef struct	s_world t_world;
typedef struct	s_map t_map;

void	event_player(t_game *game);
void	event_interact(t_game *game);
void	event_display_ui(t_game *game);


void	event_door_unlocked(t_game *game, t_entity_2 *ent);
void	event_door_open(t_game *game, t_entity_2 *ent);
void	event_door_locked(t_game *game, t_entity_2 *ent);
void	event_alert_high(t_game *game, t_entity_2 *ent);
void	event_alert_medium(t_game *game, t_entity_2 *ent);
void	event_alert_off(t_game *game, t_entity_2 *ent);
#endif
