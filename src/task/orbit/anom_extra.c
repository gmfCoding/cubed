#include <math.h>
#include "orbit.h"

double	orb_ta_to_ma(double ta, double ecc)
{
	double ea;

	ea = orb_ta_to_ea(ta, ecc);
	return (orb_ea_to_ma(ea, ecc));
}

double	orb_ma_to_ta(double ma, double ecc)
{
	double ea;

	ea = orb_ma_to_ea(ma, ecc);
	return (orb_ea_to_ta(ea, ecc));
}