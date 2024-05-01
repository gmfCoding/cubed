/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 09:43:53 by kmordaun          #+#    #+#             */
/*   Updated: 2024/04/30 20:44:09 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H
# include "entity.h"
# include "sound.h"

typedef struct s_world	t_world;
typedef struct s_map	t_map;
typedef void			(*t_event_fn)(t_game *game, t_entity_2 *ent);

void			event_player(t_game *game, bool force);
void			event_interact(t_game *game);
void			event_display_ui(t_game *game);

void			event_door(t_door *door, t_game *game);

void			event_door_unlocked(t_game *game, t_entity_2 *ent);
void			event_door_open(t_game *game, t_entity_2 *ent);
void			event_door_locked(t_game *game, t_entity_2 *ent);
void			event_alert_high(t_game *game, t_entity_2 *ent);
void			event_alert_medium(t_game *game, t_entity_2 *ent);
void			event_alert_off(t_game *game, t_entity_2 *ent);

void			event_five_lights_open(t_game *game, t_entity_2 *ent);
void			event_five_lights_closed(t_game *game, t_entity_2 *ent);

t_handle_result	entity_target_handle(t_game *game, t_entity_2 *ent);

t_handle_result	target_handle_door(t_game *game, \
t_entity_2 *door, t_entity_2 *parent);
t_handle_result	target_handle_five_lights(t_game *game, \
t_entity_2 *five_lights, t_entity_2 *parent);
t_handle_result	target_handle_or(t_game *game, \
t_entity_2 *self, t_entity_2 *other);
t_handle_result	target_handle_and(t_game *game, \
t_entity_2 *self, t_entity_2 *other);
t_handle_result	target_handle_splitter(t_game *game, \
t_entity_2 *self, t_entity_2 *other);

#endif
