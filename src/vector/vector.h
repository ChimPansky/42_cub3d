/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:39:40 by tkasbari          #+#    #+#             */
/*   Updated: 2024/04/20 13:24:38 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

#include <stdbool.h>

typedef struct s_cartesian_vector
{
	double	x;
	double	y;
}				t_cvector;

// allowed values:
//	r >= 0.0
//	phi [-2pi, 2pi]
typedef struct s_polar_vector
{
	double	r;
	double	phi;
}				t_pvector;

// functions for cartesian vectors:
t_cvector	cvector(double x, double y);
t_cvector	cvector_from_angle(double angle);
double		cvector_get_mod(const t_cvector *cvec);
t_cvector	cvector_add(const t_cvector *cvec1, const t_cvector *cvec2);
t_cvector	cvector_rotate(const t_cvector *cvec, double rot_angle);
void		cvector_normalize(t_cvector *cvec);
void		cvector_print(const t_cvector *cvec);

// functions for polar vectors:
t_pvector	pvector(double r, double phi);
t_pvector	pvector_from_coords(double x, double y);
t_pvector	pvector_copy(t_pvector *pvec);
void		pvector_scale(t_pvector *pvec, double factor);
void		pvector_rotate(t_pvector *pvec, double rot_angle);
void		pvector_print(const t_pvector *pvec);

bool		dbl_is_almost_zero(double a);

#endif  // VECTOR_H
