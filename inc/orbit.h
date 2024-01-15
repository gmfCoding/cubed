#include <math.h>
#include "vector3.h"
#include "constants.h"
#include <stdbool.h>

#ifndef ORBIT_H
# define ORBIT_H

#define C_GRAV  6.67430e-11
//#define C_GRAV  0.00001
#define EA_MAX_ERROR 10e-13
#define EA_MAX_ITER 100


/// @brief Kepler element precision
typedef enum e_elem_prec
{
	ELEM_NONE,
	ELEM_EXACT,
	ELEM_DERIVED,
} t_kpep;

typedef struct s_orb_body
{
    double radius;
    double mass;
    double grav;
} t_orb_body;

/*
	Create a new orbital body definition
	@param radius planet radius in meters
	@param density density in kg/m3
*/
t_orb_body orb_body_create(double radius, double density);

typedef enum e_kep_elem
{
	KEP_SMA,
	KEP_APO,
	KEP_PER,
	KEP_ECC,
	KEP_AOP,
	KEP_LAN,
	KEP_INC,
	KEP_MNA,
	KEP_TA,
	KEP_EA,
	KEP_SMA2 = 1,
	KEP_APO2 = 2,
	KEP_PER2 = 4,
	KEP_ECC2 = 8,
	KEP_AOP2 = 16,
	KEP_LAN2 = 32,
	KEP_INC2 = 64,
	KEP_MNA2 = 128,
	KEP_TA2 = 256,
	KEP_EA2 = 512
} t_kpe;

typedef struct s_kep_use
{
	union
	{
		struct
		{		
			t_kpep	sma;
			t_kpep	apo;
			t_kpep	per;
			t_kpep	ecc;
			t_kpep	aop;
			t_kpep	lan;
			t_kpep	inc;
			t_kpep	mna;
			t_kpep	ta;
			t_kpep	ea;
		};
		t_kpep	encoded[10];
	};
}			t_kep_use;

typedef struct s_kep_oparam
{
	t_orb_body	body;
	t_kep_use	set;
	double		sma;

	double		apo;
	double		per;

	double		ecc;

	double		inc;
	double		lan;

	double		aop;
	double		mna;

	double		radius;
	double		distance;
	double		ta;
	double		ea;
	double		mom;
	t_kpe		prime_angle;
}	t_kep_orb;

typedef struct s_cart_oparam
{
	t_orb_body body;
	t_vec3 position;
	t_vec3 velocity;
} t_cart_orb;

double  orb_ta_to_ea(double ta, double ecc);
double  orb_ma_to_ea(double ma, double ecc);
double  orb_ea_to_ta(double ea, double ecc);
double  orb_ea_to_ma(double ea, double ecc);
double	orb_ma_to_ta(double ma, double ecc);
double	orb_ta_to_ma(double ta, double ecc);

void	kep_elem_set(t_kep_orb *kep, double value, t_kpe prop, t_kpep prec);
void	kep_complete(t_kep_orb *kep);

void    orb_cart_to_kepler(t_cart_orb cart, t_kep_orb *kep);
void    orb_kepler_to_cart(t_kep_orb kep, t_cart_orb *cart);
#endif