/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utilities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 09:38:05 by tkasbari          #+#    #+#             */
/*   Updated: 2024/04/17 09:43:33 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "vector.h"
#include <stdio.h>
#include <math.h>

bool	dbl_is_almost_zero(double a)
{
	if (a == 0)
		return (true);
	if (a < 0 && a > -10e-10)
		return (true);
	if (a > 0 && a < 10e-10)
		return (true);
	return (false);
}

void	cvector_print(const t_cvector *cvec)
{
	printf("(%f/%f)\n", cvec->x, cvec->y);
}

void	pvector_print(const t_pvector *pvec)
{
	printf("(%f, %f)\n", pvec->r, pvec->phi);
}

t_cvector	cvector_from_pvector(t_pvector *pvec)
{
	t_cvector	result;

	result.x = pvec->r * cos(pvec->phi);
	result.y = pvec->r * sin(pvec->phi);
	return (result);
}

t_pvector	pvector_from_cvector(t_cvector *cvec)
{
	t_pvector	result;

	result.r = cvector_get_mod(cvec);
	result.phi = acos(cvec->x/result.r);
	return (result);
}
