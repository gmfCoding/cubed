/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clmath.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 01:27:13 by clovell           #+#    #+#             */
/*   Updated: 2024/02/05 17:31:04 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef CLMATH_H
# define CLMATH_H
# ifndef __USE_MISC
#  define M_PI 3.141592653589
# endif
# define M_TAU 6.2831853072


double	angle_diff(double a, double b);
double	ft_atan2(double x, double y);
double	facos(double x);
double	flerp(float lerp, float min, float max);

#endif
