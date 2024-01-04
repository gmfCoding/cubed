#include "orbit.h"

t_orb_body orb_body_create(double radius, double density)
{
    t_orb_body body;
    body.radius = radius;
    body.mass = 4.0 / 3.0 * PI * radius * radius * radius * density;
    body.grav = body.mass * C_GRAV;
	return (body);
}

void    orb_cart_to_kepler(t_cart_orb cart, t_kep_orb *kep)
{
	const t_vec3  v_mo = v3cross(cart.position, cart.velocity);
	t_vec3  v_ec;
	t_vec3  v_an;

	v_ec = v3sub(v3divs(v3cross(cart.velocity, v_mo), cart.body.grav), v3norm(cart.position));
	v_an = v3new(-v_mo.y, v_mo.x, 0);
	//v_an = v3cross(v3new(0,0,1), v_mo));
	kep->ecc = v3mag(v_ec);
	kep->ta = acos(v3dot(v_ec, cart.position) / (kep->ecc * v3mag(cart.position)));
	if (v3dot(cart.position, cart.velocity) < 0)
		kep->ta = 2 * PI - kep->ta;
	kep->sma =  1.0 / (2.0 / v3mag(cart.position) - v3sqrmag(cart.velocity) / cart.body.grav);
	kep->inc = acosf(v_mo.z/v3mag(v_mo));
	kep->ea = 2 * atan(tan(kep->ta / 2.0) / sqrt((1.0 + kep->ecc) / (1.0 - kep->ecc)));
	kep->lan = acos(v_an.x / v3mag(v_an));
	if (v_an.y < 0)
		kep->lan = 2 * PI - kep->lan;
	kep->aop = acos(v3dot(v_an, v_ec));
	if (v_ec.z < 0)
		kep->aop = 2 * PI - kep->aop;
	kep->mna = kep->ea - kep->ecc * sin(kep->ea);
}

void    orb_kepler_to_cart(t_kep_orb k, t_cart_orb *cart)
{
	t_vec3 p;
	t_vec3 v;
	const double mat[6] = {
		(cos(k.aop) * cos(k.lan) - sin(k.aop) * cos(k.inc) * sin(k.lan)),
		(sin(k.aop) * cos(k.lan) + cos(k.aop) * cos(k.inc) * sin(k.lan)),
		(cos(k.aop) * sin(k.lan) + sin(k.aop) * cos(k.inc) * cos(k.lan)),
		(cos(k.aop) * cos(k.inc) * cos(k.lan) - sin(k.aop) * sin(k.lan)),
		(sin(k.aop) * sin(k.inc)),
		(cos(k.aop) * sin(k.inc)),
	};
	p = v3muls(v3new(cos(k.ta), sin(k.ta), 0), k.sma * (1.0 - k.ecc * cos(k.ea)));
	v = v3muls(v3new(-sin(k.ea), sqrt(1.0 - k.ecc * k.ecc) * cos(k.ea), 0), sqrt(k.body.grav * k.sma) / v3mag(p));
	cart->body = k.body;
	cart->position = v3new(
		p.x * mat[0] - p.y * mat[1],
		p.x * mat[2] - p.y * mat[3],
		p.x * mat[4] + p.y * mat[5]
	);
	cart->velocity = v3new(
		v.x * mat[0] - v.y * mat[1],
		v.x * mat[2] - v.y * mat[3],
		v.x * mat[4] + v.y * mat[5]
	);
}