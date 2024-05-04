/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pvector.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvilensk <vilenskii.v@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:39:59 by tkasbari          #+#    #+#             */
/*   Updated: 2024/05/04 15:32:14 by vvilensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <math.h>
#include <stdio.h>

static double	normolize_angle(double angle)
{
	if (angle < 0)
		return (fmod(angle, M_PI * 2) + M_PI * 2);
	return (fmod(angle, M_PI * 2));
}

t_pvector	pvector(double r, double phi)
{
	t_pvector	result;

	if (r < 0)
	{
		r *= -1;
		phi += M_PI;
	}
	result.r = r;
	result.phi = normolize_angle(phi);
	return (result);
}

t_pvector	pvector_from_coords(double x, double y)
{
	t_pvector	result;

	result.r = sqrt(x * x + y * y);
	result.phi = normolize_angle(atan2(y, x));
	return (result);
}

void	pvector_print(const t_pvector *pvec)
{
	printf("(%f, %f)\n", pvec->r, pvec->phi);
}

void	pvector_rotate(t_pvector *pvec, double rot_angle)
{
	pvec->phi = normolize_angle(pvec->phi + rot_angle);
}
