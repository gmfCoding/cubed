#include <math.h>
#include "constants.h"

double  ft_atan2(double x, double y)
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