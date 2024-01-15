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
	kep_elem_set(&kep, 1.00000011 * AU, KEP_SMA, ELEM_EXACT);
	kep_elem_set(&kep, 0.016708617, KEP_ECC, ELEM_EXACT);
	kep_elem_set(&kep, 45 * DEG2RAD, KEP_INC, ELEM_EXACT);
	kep_elem_set(&kep, 0, KEP_LAN, ELEM_EXACT);
	kep_elem_set(&kep, 0, KEP_TA, ELEM_EXACT);

	kep_complete(&kep);
	orb_kepler_to_cart(kep, &cart);
	if (abs(v3mag(cart.velocity) - 30290) > 100)
		return "Earth speed not in expected range";
	kep_elem_set(&kep, 180 * DEG2RAD, KEP_TA, ELEM_EXACT);
	kep_complete(&kep);
	orb_kepler_to_cart(kep, &cart);
	if (abs(v3mag(cart.velocity) - 29290) > 100)
		return "Earth speed not in expected range";
	orb_cart_to_kepler(cart, &kep);
	if (abs(kep.sma - 1.00000011 * AU) > 1.0)
		return "SMA not in expected range";
	return (NULL);
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
	t_orb_body planet = orb_body_create(6371000, 5514);
	t_kep_orb orb;

	return (0);
}