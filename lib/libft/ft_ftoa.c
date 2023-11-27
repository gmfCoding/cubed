
#include "libft.h"

static int ft_abs(int abs)
{
	if (abs < 0)
		return (-abs);
	return (abs);
}

char	*ft_ftoa(double n, int precision)
{
	char		*whole;
	char		*frac;
	const char	*sign = "";
	const char	*padding = "";

	if (n < 0)
		sign = "-";
	whole = ft_itoa((int)n);
	n = ft_abs((n - (int)n) * (double)precision);
	frac = ft_itoa(n);
	if (n < 10)
		padding = "00";
	else if (n < 100)
		padding = "0";
	return ft_strfmt("%s%S.%s%S", sign, whole, padding, frac);
}