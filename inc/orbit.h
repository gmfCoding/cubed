/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orbit.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 22:24:23 by clovell           #+#    #+#             */
/*   Updated: 2024/04/16 19:03:58 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef ORBIT_H
# define ORBIT_H

# include <math.h>
# include "vector3.h"
# include "clmath.h"
# include <stdbool.h>
# include "orbit/orbit_data.h"
# include "rect.h"

# define KM_G  6.67430e-11
# define KM_AU 1.496E11

# define KEP_MIN_EPSILON 0.0001
# define EA_MAX_ERROR 10e-13
# define EA_MAX_ITER 100

typedef struct s_texture	t_texture;
typedef struct s_rand		t_rand;

typedef enum e_angt			t_angt;

enum e_angt
{
	ANG_TIME,
	ANG_MEAN,
	ANG_ECCA
};


/*** task/orbit/sys/kep_angle_util.c ***/
double			orb_time_at_mean(t_kep_path *path, t_kep_ang *ang, double mna);

double			orb_ea_to_ma(double ea, double ecc);

/*** task/orbit/sys/kep_angle.c ***/

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
void			kep_ang_set(t_kep_path *p, t_kep_ang *a, double tn, t_angt t);

/*** task/orbit/sys/body.c ***/

/* Returns a new body based on radius and density. */
t_orb_body		orb_body_create_rd(double radius, double density);

/* Returns a new body based on radius and mass. */
t_orb_body		orb_body_create_rm(double radius, double mass);

/*** task/orbit/sys/kep_properties.c ***/

/* Returns the current time since epoch in seconds. */
double			kep_time(t_kep_ang *ang);

/* Returns the orbital period in seconds. */
double			kep_period(t_kep_path *path);

/* Clamps the values of  */
void			kep_clamp(t_kep_path *path);

/*** task/orbit/sys/ktoc_position.c ***/

double			orb_radius(t_kep_path *path, t_kep_ang *ang);

void			orb_pos(t_kep_path *path, t_kep_ang *ang, t_vec3 *cart);

void			orb_cart_pos(t_kep_path *p, t_kep_ang *a, t_orb_cart *c);

/*** task/orbit/sys/ktoc_velocity.c ***/
double			orb_max_delta(t_kep_path *path, t_kep_ang *ang);
double			orb_speed(t_kep_path *path, t_kep_ang *ang);
double			orb_speed_at_ecc(t_kep_path *path, t_kep_ang *ang, double ecc);

void			orb_vel(t_kep_path *path, t_kep_ang *ang, t_vec3 *vel);

void			orb_cart_vel(t_kep_path *p, t_kep_ang *a, t_orb_cart *c);

/*** task/orbit/sys/cart_to_kep.c ***/
t_vec3			orb_cart_ecv(t_orb_cart *cart, double u);
void			orb_cart_to_kep(t_orb_cart *c, t_kep_path *p, t_kep_ang *a);

/*** task/orbit/sys/render.c ***/

void			orbit_path_render(t_kep_path *path, t_texture *rt,
					t_rect trans, int col);
void			orbit_obj_render(t_kep_path *p, t_kep_ang *a,
					t_rect trans, t_texture *rt);
void			orbit_obj_render_at(t_kep_path *path, double mean,
					t_angt angt, t_texture *rt);

/* Scales the orbit into screen space. */
t_vec3			orb_to_ndc(t_vec3 cart, t_vec3 offset, t_vecd scale);

/*** task/orbit/sys/transform.c ***/
double			orb_transform_x(t_kep_path *p, double x, double y);
double			orb_transform_y(t_kep_path *p, double x, double y);
double			orb_transform_z(t_kep_path *p, double x, double y);
void			orb_transform_cart(t_kep_path *path, t_orb_cart *cart);

/*** task/orbit/sys/generate.c ***/
void			orb_generate(t_kep_path *path,
					const t_orb_gen *gen, t_rand *rand);

/*** task/orbit/sys/equality.c ***/
double	orb_deviation(t_kep_path *a, t_kep_path *b);

#endif