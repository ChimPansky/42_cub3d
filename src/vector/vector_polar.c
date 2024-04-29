/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_polar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:39:59 by tkasbari          #+#    #+#             */
/*   Updated: 2024/04/29 13:31:16 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <math.h>

t_pvector	pvector(double r, double phi)
{
	t_pvector	result;

	result.r = r;
	result.phi = phi;
	if (r < 0)
	{
		result.r *= -1;
		result.phi += M_PI;
	}
	result.phi = fmod(result.phi + 2 * M_PI, 2 * M_PI);
	return (result);
}

void	pvector_scale(t_pvector *pvec, double factor)
{
	pvec->r *= factor;
}

void	pvector_add_pvector(t_pvector *pvec, t_pvector addition)
{
	double	x;
	double	y;

	x = pvec->r * cos(pvec->phi) + addition.r * cos(addition.phi);
	y = pvec->r * sin(pvec->phi) + addition.r * sin(addition.phi);
	pvec->r = sqrt(x * x + y * y);
	pvec->phi = fmod(atan2(y, x) + 2 * M_PI, 2 * M_PI);
}

t_pvector	pvector_from_coords(double x, double y)
{
	t_pvector	result;

	result.r = sqrt(x * x + y * y);
	result.phi = fmod(atan2(y, x) + 2 * M_PI, 2 * M_PI);
	return (result);
}

void	pvector_rotate(t_pvector *pvec, double rot_angle)
{
	pvec->phi = fmod(pvec->phi + rot_angle + 2 * M_PI, 2 * M_PI);
}
