/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clmath.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 01:27:13 by clovell           #+#    #+#             */
/*   Updated: 2024/02/14 13:53:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef CLMATH_H
# define CLMATH_H
# ifndef __USE_MISC 
#  ifndef M_PI
#   define M_PI 3.141592653589
#  endif
# endif
# define M_TAU 6.2831853072


double	angle_diff(double a, double b);
double	ft_atan2(double x, double y);
double	facos(double x);
double	flerp(double min, double max, double lerp);
double	fclamp(double min, double max, double value);

#endif
