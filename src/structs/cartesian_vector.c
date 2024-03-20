/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartesian_vector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:39:59 by tkasbari          #+#    #+#             */
/*   Updated: 2024/03/20 14:03:27 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_cvector	cvector(double x, double y)
{
	t_cvector	result;

	result.x = x;
	result.y = y;
	return (result);
}

t_cvector	angle_to_cvector(double angle)
{
	t_cvector	result;

	result.x = cos(angle);
	result.y = sin(angle);
	return (result);
}

t_cvector	cvector_add(t_cvector cvec1, t_cvector cvec2)
{
	t_cvector	result;

	result.x = cvec1.x + cvec2.x;
	result.y = cvec1.y + cvec2.y;
	return (result);
}

double	angles_add(double angle1, double angle2)
{
	return (fmod(angle1 + angle2, 2 * M_PI));
}

double	get_cvec_len(t_cvector cvec)
{
	double	len;

	len = sqrt(pow(cvec.x, 2) + pow(cvec.y, 2));
	return (len);
}

t_cvector	cvector_rotate(t_cvector cvec, double rot_angle)
{
	t_cvector	result;

	result.x = cvec.x * cos(rot_angle) - cvec.y * sin(rot_angle);
	result.y = cvec.x * sin(rot_angle) + cvec.y * cos(rot_angle);
	return (result);
}

t_cvector	cvector_normalize(t_cvector cvec)
{
	t_cvector	result;
	double		vec_angle;

	vec_angle = atan2(cvec.y, cvec.x);
	result.x = cos(vec_angle);
	result.y = sin(vec_angle);
	return (result);
}

#include <stdio.h>
void		cvector_print(t_cvector cvec)	//TODO: remove
{
	printf("(%f/%f)\n", cvec.x, cvec.y);
}
