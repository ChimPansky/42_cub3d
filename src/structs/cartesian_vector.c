/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartesian_vector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:39:59 by tkasbari          #+#    #+#             */
/*   Updated: 2024/04/02 12:04:15 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <float.h>
#include <stdio.h>

t_cvector	cvector(double x, double y)
{
	t_cvector	result;

	result.x = x;
	result.y = y;
	return (result);
}

t_cvector	cvector_from_angle(double angle)
{
	t_cvector	result;

	result.x = cos(angle);
	result.y = sin(angle);
	return (result);
}

t_cvector	cvector_add(const t_cvector *cvec1, const t_cvector *cvec2)
{
	return (cvector(cvec1->x + cvec2->x, cvec1->y + cvec2->y));
}


double	cvector_get_mod(const t_cvector *cvec)
{
	return (sqrt(pow(cvec->x, 2) + pow(cvec->y, 2)));
}

t_cvector	cvector_rotate(const t_cvector *cvec, double rot_angle)
{
	t_cvector	result;

	result.x = cvec->x * cos(rot_angle) - cvec->y * sin(rot_angle);
	result.y = cvec->x * sin(rot_angle) + cvec->y * cos(rot_angle);
	return (result);
}

void	cvector_normalize(t_cvector *cvec)
{
	double		vec_mod;

	vec_mod = cvector_get_mod(cvec);
	if (fabs(vec_mod) < DBL_EPSILON)
		return ;
	cvec->x /= vec_mod;
	cvec->y /= vec_mod;
}

void	cvector_print(const t_cvector *cvec)
{
	printf("(%f/%f)\n", cvec->x, cvec->y);
}
