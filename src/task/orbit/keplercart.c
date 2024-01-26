#include "orbit.h"

t_orb_body orb_body_create_rd(double radius, double density)
{
    t_orb_body body;
    body.radius = radius;
    body.mass = 4.0 / 3.0 * PI * radius * radius * radius * density;
    body.grav = body.mass * C_GRAV;
	return (body);
}

t_orb_body orb_body_create_rm(double radius, double mass)
{
    t_orb_body body;
	const double vol = 4.0 / 3.0 * PI * radius * radius * radius;

    body.radius = radius;
    body.mass = mass;
    body.grav = body.mass * C_GRAV;
	return (body);
}
// void    orb_cart_to_kepler(t_cart_orb cart, t_kep_orb *kep)
// {
// 	const t_vec3  v_mo = v3cross(cart.pos, cart.vel);
// 	t_vec3  v_ec;
// 	t_vec3  v_an;
	
// 	v_ec = v3sub(v3divs(v3cross(cart.vel, v_mo), cart.body.grav), v3norm(cart.pos));
// 	v_an = v3new(-v_mo.y, v_mo.x, 0);
// 	//v_an = v3cross(v3new(0,0,1), v_mo));
// 	kep->ecc = v3mag(v_ec);
// 	kep->ta = acos(v3dot(v_ec, cart.pos) / (kep->ecc * v3mag(cart.pos)));
// 	if (v3dot(cart.pos, cart.vel) < 0)
// 		kep->ta = 2 * PI - kep->ta;
// 	kep->sma =  1.0 / (2.0 / v3mag(cart.pos) - v3sqrmag(cart.vel) / cart.body.grav);
// 	kep->inc = acosf(v_mo.z/v3mag(v_mo));
// 	kep->ea = 2 * atan(tan(kep->ta / 2.0) / sqrt((1.0 + kep->ecc) / (1.0 - kep->ecc)));
// 	kep->lan = acos(v_an.x / v3mag(v_an));
// 	if (v_an.y < 0)
// 		kep->lan = 2 * PI - kep->lan;
// 	kep->aop = acos(v3dot(v_an, v_ec));
// 	if (v_ec.z < 0)
// 		kep->aop = 2 * PI - kep->aop;
// 	kep->mna = kep->ea - kep->ecc * sin(kep->ea);
// }

void    orb_cart_to_kepler(t_cart_orb cart, t_kep_orb *kep)
{
	const t_vec3  v_mo = v3cross(cart.pos, cart.vel);
	t_vec3  v_ec;
	t_vec3  v_an;
	double temp;
	cart.parent = kep->parent;
	v_ec = v3sub(v3divs(v3cross(cart.vel, v_mo), kep->parent.grav), v3norm(cart.pos));
	v_an = v3new(-v_mo.y, v_mo.x, 0);
	//v_an = v3cross(v3new(0,0,1), v_mo));
	kep_elem_set(kep, v3mag(v_ec), KEP_ECC, ELEM_EXACT);
	temp = acos(v3dot(v_ec, cart.pos) / (kep->ecc * v3mag(cart.pos)));
	if (v3dot(cart.pos, cart.vel) < 0)
		temp = 2 * PI - temp;
	kep_elem_set(kep, temp, KEP_TA, ELEM_EXACT);
	kep_elem_set(kep, 1.0 / (2.0 / v3mag(cart.pos) - v3sqrmag(cart.vel)\
	/ cart.parent.grav), KEP_SMA, ELEM_EXACT);
	kep_elem_set(kep, acosf(v_mo.z/v3mag(v_mo)), KEP_INC, ELEM_EXACT);
	kep_elem_set(kep, 2 * atan(tan(kep->ta / 2.0) / sqrt((1.0 + kep->ecc)\
	/ (1.0 - kep->ecc))), KEP_EA, ELEM_EXACT);
	temp = acos(v_an.x / v3mag(v_an));
	if (v_an.y < 0)
		temp = 2 * PI - temp;
	kep_elem_set(kep, temp, KEP_LAN, ELEM_EXACT);
	temp = acos(v3dot(v_an, v_ec));
	if (v_ec.z < 0)
		temp = 2 * PI - temp;
	kep_elem_set(kep, temp, KEP_AOP, ELEM_EXACT);
	kep_elem_set(kep, kep->ea - kep->ecc * sin(kep->ea),KEP_MNA, ELEM_EXACT);
}


// void orb_kepler_to_cart(t_kep_orb k, t_cart_orb *c)
// {
	
// }

// void	orb_kepler_to_cart(t_kep_orb k, t_cart_orb *cart)
// {
// 	const double ang[] = {
// 		cos(k.lan),
// 		sin(k.lan),
// 		cos(k.aop + k.ta),
// 		sin(k.aop + k.ta),
// 		cos(k.inc)
// 	};
// 	const double pos[] = {
// 		k.radius * (ang[0] * ang[2] - ang[1] * ang[3] * ang[4]),
// 		k.radius * (ang[1] * ang[2] + ang[0] * ang[3] * ang[4]),
// 		k.radius * (sin(k.inc) * ang[3])
// 	};
// 	const double p = k.sma * (1 - k.ecc * k.ecc);
// 	const double vel[] = {
// 		(pos[0] * k.mom * k.ecc) / (k.radius * p) * sin(k.ta),
// 		(pos[1] * k.mom * k.ecc) / (k.radius * p) * sin(k.ta),
// 		(pos[2] * k.mom * k.ecc) / (k.radius * p) * sin(k.ta),
// 	};
// 	const double off[] = 
// 	{
// 		(k.mom/k.radius) * (ang[0] * ang[3] + ang[1] * ang[2] * ang[4]),
// 		(k.mom/k.radius) * (ang[1] * ang[3] + ang[0] * ang[2] * ang[4]),
// 		(k.mom/k.radius) * ang[4] * ang[2]
// 	};
// 	cart->parent = k.parent;
// 	cart->pos = v3new(pos[0], pos[1], pos[2]);
// 	cart->vel = v3new(vel[0] - off[0], vel[1] - off[1], vel[2] + off[2]);
// }

void    orb_kepler_to_cart(t_kep_orb k, t_cart_orb *cart)
{
	float d = k.sma * (1 - k.ecc * cos(k.ea));
	t_vec3 pos = v3muls(v3new(cos(k.ta), sin(k.ta), 0), d);
	t_vec3 vel = v3new(-sin(k.ea), sqrt(1 - k.ecc * k.ecc) * cos(k.ea), 0);
	cart->pos = pos;
	cart->vel = v3muls(vel, sqrt(k.parent.grav * k.sma) / d);
}


// void	orb_kepler_to_cart(t_kep_orb k, t_cart_orb *cart)
// {
// 	double nu = 2 * atan(sqrt((1 + k.ecc) / (1 - k.ecc)) * tan(k.ea / 2.0));
// 	double r = k.sma * (1 - k.ecc * cos(k.ea));
// 	double p = k.sma * (1 - k.ecc * k.ecc);
// 	double h = sqrt(k.parent.grav * p);

// 	cart->pos.x = r * cos(k.lan) * cos(k.aop + nu) - sin(k.lan) * sin(k.aop + nu) * cos(k.inc);
// 	cart->pos.y = r * sin(k.lan) * cos(k.aop + nu) + cos(k.lan) * sin(k.aop + nu) * cos(k.inc);
// 	cart->pos.z = r * (sin(k.inc) * sin(k.aop + nu));

// 	cart->vel.x = (cart->pos.x * h * k.ecc / (r * p)) * sin(nu) - (h/r)*cos(k.lan)*sin(k.aop + nu) + \
// 	sin(k.lan)*cos(k.aop + nu)*cos(k.inc);
// 	cart->vel.y = -((cart->pos.y * h * k.ecc / (r * p)) * sin(nu) - (h/r)*cos(k.lan)*sin(k.aop + nu) - \
// 	cos(k.lan)*cos(k.aop + nu)*cos(k.inc));
// 	cart->vel.z = (cart->pos.z * h * k.ecc / (r * p)) * sin(nu) + (h/r)*cos(k.aop + nu) * sin(k.inc);
// }

// void    orb_kepler_to_cart(t_kep_orb k, t_cart_orb *cart)
// {
// 	t_vec3 p;
// 	t_vec3 v;
// 	const double mat[6] = {
// 		(cos(k.aop) * cos(k.lan) - sin(k.aop) * cos(k.inc) * sin(k.lan)),
// 		(sin(k.aop) * cos(k.lan) + cos(k.aop) * cos(k.inc) * sin(k.lan)),
// 		(cos(k.aop) * sin(k.lan) + sin(k.aop) * cos(k.inc) * cos(k.lan)),
// 		(cos(k.aop) * cos(k.inc) * cos(k.lan) - sin(k.aop) * sin(k.lan)),
// 		(sin(k.aop) * sin(k.inc)),
// 		(cos(k.aop) * sin(k.inc)),
// 	};
// 	p = v3muls(v3new(cos(k.ta), sin(k.ta), 0), k.sma * (1.0 - k.ecc * cos(k.ea)));
// 	v = v3muls(v3new(-sin(k.ea), sqrt(1.0 - k.ecc * k.ecc) * cos(k.ea), 0), sqrt(k.parent.grav * k.sma) / v3mag(p));
// 	cart->parent = k.parent;
// 	cart->pos = v3new(
// 		p.x * mat[0] - p.y * mat[1],
// 		p.x * mat[2] - p.y * mat[3],
// 		p.x * mat[4] + p.y * mat[5]
// 	);
// 	cart->vel = v3new(
// 		v.x * mat[0] - v.y * mat[1],
// 		v.x * mat[2] - v.y * mat[3],
// 		v.x * mat[4] + v.y * mat[5]
// 	);
// }