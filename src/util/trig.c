#include <math.h>
#include "constants.h"

double  ft_atan2(double y, double x)
{
    if (x > 0)
        return (atan(y / x));
    else if (y >= 0 && x < 0)
        return (atan(y / x) + M_PI);
    else if (y < 0 && x < 0)
        return (atan(y / x) - M_PI);
    else if (y > 0 && x == 0)
        return (M_PI / 2);
    else if (y < 0 && x == 0)
        return (-M_PI / 2);
    else
        return (0);
}

double facos(double x)
{
	if (x > 1)
		return (0);
	if (x < -1)
		return (M_PI);
	return acos(x);
}