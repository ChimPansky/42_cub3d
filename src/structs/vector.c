/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:39:59 by tkasbari          #+#    #+#             */
/*   Updated: 2024/03/19 12:14:32 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector	vector(double x, double y)
{
	t_vector	result;

	result.x = x;
	result.y = y;
	return (result);
}

t_vector	vector_add(t_vector vec1, t_vector vec2)
{
	t_vector	result;

	result.x = vec1.x + vec2.x;
	result.y = vec1.y + vec2.y;
	return (result);
}

double	get_vec_len(t_vector vec)
{
	double	len;

	len = sqrt(pow(vec.x, 2) + pow(vec.y, 2));
	return (len);
}

double	get_vec_angle(t_vector vec)
{
	return (atan2(vec.y, vec.x));
}

// static double	add_angles(double angle1, double angle2)
// {
// 	double	result;

// 	result = fmod(angle1 + angle2, 2 * M_PI);
// 	return (result);
// }

t_vector	vector_rotate(t_vector vec, double rot_angle)
{
	t_vector	result;

	result.x = vec.x * cos(rot_angle) - vec.y * sin(rot_angle);
	result.y = vec.x * sin(rot_angle) + vec.y * cos(rot_angle);
	return (result);
}

// t_vector	vector_rotate(t_vector vec, double rot_angle)
// {
// 	t_vector	result;
// 	double		vec_len;
// 	double		vec_angle;
// 	double		new_angle;

// 	vec_len = vector_len(vec);
// 	vec_angle = atan2(vec.y, vec.x);
// 	new_angle = add_angles(vec_angle, rot_angle);
// 	result.x = vec_len * cos(new_angle);
// 	result.y = vec_len * sin(new_angle);
// 	return (result);
// }
t_vector	vector_mult(t_vector vec1, t_vector vec2);
t_vector	vector_normalize(t_vector vec)
{
	t_vector	result;
	double		vec_angle;

	vec_angle = get_vec_angle(vec);
	result.x = cos(vec_angle);
	result.y = sin(vec_angle);
	return (result);
}

#include <stdio.h>
void		vector_print(t_vector vec)
{
	printf("(%f/%f)\n", vec.x, vec.y);
}
