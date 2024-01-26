/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orbit.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 22:24:23 by clovell           #+#    #+#             */
/*   Updated: 2024/01/27 01:33:07 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef ORBIT_H
# define ORBIT_H

# include <math.h>
# include "vector3.h"
# include "constants.h"
# include <stdbool.h>
# include "orbit/orbit_data.h"

# define KM_G  6.67430e-11
# define KM_AU 1.496E11

# define EA_MAX_ERROR 10e-13
# define EA_MAX_ITER 100

typedef struct s_texture t_texture;

/*** task/orbit/kep_angle.c ***/

/* Calculates the angular rate at which the mean anomally changes. */
double			kep_mean_rate(t_kep_path *path);

/* Returns mean anomaly.
 	An angle that describes the position along the orbit.
	Remains linear throughout the orbit, limit of 0 -> 2 PI radians.
	It has no geometric relation.
*/
double			kep_mean(t_kep_path *path, t_kep_ang *ang);

/* Returns true anomaly.
 	An angle that describes the position along the orbit.
	Rate throughout the orbit changes, limit of 0 -> 2 PI radians.
	The angle from the foci (parent body) to the position.
*/
double			kep_ta(t_kep_path *path, t_kep_ang *ang);

/* Returns eccentric anomaly.
 	An angle that describes the position along the orbit.
	Rate throughout the orbit changes, limit of 0 -> 2 PI radians.
	The angle from orbit (ellipse) center to the projected circular position.
*/
double			kep_anom_e(t_kep_path *path, t_kep_ang *ang);

/* Sets the time sample of angular position parameters and updates them */
double			kep_ang_set(t_kep_path *path, t_kep_ang *ang, double tn);

/*** task/orbit/body.c ***/

/* Returns a new body based on radius and density. */
t_orb_body		orb_body_create_rd(double radius, double density);

/* Returns a new body based on radius and mass. */
t_orb_body		orb_body_create_rm(double radius, double mass);

/*** task/orbit/kep_properties.c ***/

/* Returns the current time since epoch in seconds. */
double			kep_time(t_kep_ang *ang);

/* Returns the orbital period in seconds. */
double			kep_period(t_kep_path *path);

/*** task/orbit/ktoc_position.c ***/

double			orb_radius(t_kep_path *path, t_kep_ang *ang);

void			orb_pos(t_kep_path *path, t_kep_ang *ang, t_vec3 *cart);

void			orb_cart_pos(t_kep_path *p, t_kep_ang *a, t_orb_cart *c);

/*** task/orbit/ktoc_velocity.c ***/
double			orb_speed(t_kep_path *path, t_kep_ang *ang);

void			orb_cart_vel(t_kep_path *p, t_kep_ang *a, t_orb_cart *c);

/*** task/orbit/ctok_position.c ***/
void			orb_cart_to_kep(t_orb_cart *c, t_kep_path *p, t_kep_ang *a);


/*** task/orbit/render.c ***/

void	orbit_path_render(t_kep_path *path, t_texture *rt);

void	orbit_obj_render(t_orb_obj *obj, t_texture *rt);
#endif