/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polar_vector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:39:59 by tkasbari          #+#    #+#             */
/*   Updated: 2024/04/05 11:54:11 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

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

void		pvector_print(const t_pvector *pvec)
{
	printf("(%f, %f)\n", pvec->r, pvec->phi);
}
