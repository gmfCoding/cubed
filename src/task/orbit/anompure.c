#include <math.h>
#include "constants.h"
#include "orbit.h"

double orb_ta_to_ea(double ta, double ecc)
{
	return (atan2(sqrt(1.0 - ecc * ecc) * sin(ta), ecc + cos(ta)));
}

double orb_ma_to_ea(double ma, double ecc)
{
	double	target;
	double	error;
	double	prev;
	int		i;

	target = ma;
	if (ecc > 0.8)
		target = PI;
	error = target - ecc * sin(target) - ma;
	while (abs(error) >= EA_MAX_ERROR && i < EA_MAX_ITER)
	{
		prev = target;
		target = prev - (error / 1.0 - ecc * cos(prev));
		error = target - ecc * sin(target) - ma;
	}
	return (target);
}

double orb_ea_to_ta(double ea, double ecc)
{
	return (2.0 * atan2(sqrt(1.0 + ecc) * sin(ea / 2.0),\
	sqrt(1 - ecc)* cos (ea/2)));
}

double orb_ea_to_ma(double ea, double ecc)
{
	return (ea - ecc * sin(ea));
}