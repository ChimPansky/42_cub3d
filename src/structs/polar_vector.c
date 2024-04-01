/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polar_vector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:39:59 by tkasbari          #+#    #+#             */
/*   Updated: 2024/04/01 16:56:35 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_pvector	pvector(double r, double phi)
{
	t_pvector	result;

	if (r < 0)
		result.r = 0;
	else
		result.r = r;
	result.phi = phi;
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
	result.phi = atan2(y, x);
	return (result);
}

t_pvector	pvector_rotate(const t_pvector *pvec, double rot_angle)
{
	t_pvector	result;

	result.r = pvec->r;
	result.phi = fmod(pvec->phi + rot_angle, 2 * M_PI);
	return (result);
}

void		pvector_print(const t_pvector *pvec)
{
	printf("(%f, %f)\n", pvec->r, pvec->phi);
}
