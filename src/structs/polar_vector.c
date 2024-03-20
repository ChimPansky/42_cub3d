/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polar_vector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:39:59 by tkasbari          #+#    #+#             */
/*   Updated: 2024/03/20 16:55:49 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_pvector	pvector(double r, double phi)
{
	t_pvector	result;

	result.r = r;
	result.phi = phi;
	return (result);
}

t_pvector	pvector_scale(t_pvector pvec, double factor)
{
	t_pvector	result;

	result.r = pvec.r * factor;
	result.phi = pvec.phi;
	return (result);
}

t_pvector	coords_to_pvector(double x, double y)
{
	t_pvector	result;

	result.r = 1;
	result.phi = atan2(y, x);
	return (result);
}

t_pvector	pvector_rotate(t_pvector pvec, double rot_angle)
{
	t_pvector	result;

	result.r = pvec.r;
	result.phi = angles_add(pvec.phi, rot_angle);
	return (result);
}


#include <stdio.h>
void		pvector_print(t_pvector pvec)	//TODO: remove
{
	printf("(%f, %f)\n", pvec.r, pvec.phi);
}
