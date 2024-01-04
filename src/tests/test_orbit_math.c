#include "orbit.h"
#include "cubed.h"
#define AU 1.495978707e+11
#define ARCS2DEG 0.000277778

static char *utest_cart2kep_earth()
{
	t_kep_orb	kep;
	t_cart_orb	cart;
	t_orb_body	sun = orb_body_create(6.96340e8, 1406.313);

	kep = (t_kep_orb){0};
	kep.body = sun;
	kep_elem_set(&kep, 1.00000011 * AU, KEP_SMA);
	kep_elem_set(&kep, 0.016708617, KEP_ECC);
	kep_elem_set(&kep, 180 * DEG2RAD, KEP_INC);
	kep_elem_set(&kep, 0, KEP_LAN);
	kep_elem_set(&kep, 0, KEP_TA);
	kep_complete(&kep);
	orb_kepler_to_cart(kep, &cart);
	if (abs(v3mag(cart.velocity) - 30290) > 100)
		return "Earth speed not in expected range";
	kep_elem_set(&kep, 180 * DEG2RAD, KEP_TA);
	kep_complete(&kep);
	orb_kepler_to_cart(kep, &cart);
	if (abs(v3mag(cart.velocity) - 29290) > 100)
		return "Earth speed not in expected range";
	orb_cart_to_kepler(cart, &kep);
	if (abs(kep.sma - 1.00000011 * AU) > 1.0)
		return "SMA not in expected range";
	return (NULL);
}

static void cart2kep(t_orb_body body)
{
	/*
	(lldb) p C_GRAV
	6.67430e-11
	(lldb) p cart
	(t_cart_oparam) $0 = {
	body = (radius = 695700000, mass = 1.9746160151950956E+30, grav = 1.3179179670216625E+20)
	position = (x = 1.49599994E+11, y = 0, z = 0)
	velocity = (x = 27095.6602, y = -12115.5469, z = 0)
	}
	*/

	// kep.body = orb_body_create(20, 10000);
	// kep.sma = 150e9;
	// kep.ecc = 0;
	// kep.inc = 0;
	// kep.lan = 0;

	// kep.
	// kep.body = body;
	// kep.mna = DEG2RAD * 120;
	// kep.aop = 0;
	// kep.sma = 0.3844e9;
	// kep.inc = 0.08979719;
	// kep.ecc = 0.0549;

	// cart.position = v3new(617244712358.0, -431694791368.0, -12036457087.0);
	// cart.velocity = v3new(7320.00000000049, 11.328999999999676, -0.21100000000002198);
	// cart.position = v3new(planet.radius + 100000, 0, 0);
	// cart.velocity = v3new(0, 27000, 0);
	//orb_kepler_to_cart(kep, &cart);
}

static void kep2cart(t_orb_body planet)
{
	t_cart_orb cart;
	t_kep_orb kep;
	cart.body = planet;
	cart.position = v3new(-5107606.49, -1741563.23, -4118273.08);
	cart.velocity = v3new(4677.962842, 4677.962842, -3800.652800);
	// cart.position = v3new(617244712358.0, -431694791368.0, -12036457087.0);
	// cart.velocity = v3new(7320.00000000049, 11.328999999999676, -0.21100000000002198);
	// cart.position = v3new(planet.radius + 100000, 0, 0);
	// cart.velocity = v3new(0, 27000, 0);
	orb_cart_to_kepler(cart, &kep);
}
typedef char *(*t_utestfn)();
void utest_perform()
{
	char *test;
	const t_utestfn tests[] = {
		utest_cart2kep_earth
	};
	size_t i;

	i = -1;
	while (++i < sizeof(tests)/sizeof(*tests))
	{
		test = tests[i]();
		if (test != NULL)
		{
			printf("error:%s", test);
			exit(0);
		}
	}
}

int main(void)
{
	utest_perform();
	// t_orb_body planet = orb_body_create(6371000, 5514);
	// t_orb_body sun = orb_body_create(6.957e8, 1400);
	// cart2kep(sun);
	// kep2cart(sun);
	return (0);
}