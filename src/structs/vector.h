/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:39:40 by tkasbari          #+#    #+#             */
/*   Updated: 2024/03/20 16:56:09 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

#include "math.h"

typedef struct s_cartesian_vector
{
	double	x;
	double	y;
}				t_cvector;

typedef struct s_polar_vector
{
	double	r;
	double	phi;
}				t_pvector;

double		angles_add(double angle1, double angle2);

// functions for cartesian vectors:
t_cvector	cvector(double x, double y);
t_cvector	angle_to_cvector(double angle);
double		get_cvec_len(t_cvector cvec);
t_cvector	cvector_rotate(t_cvector cvec, double angle);
t_cvector	cvector_add(t_cvector cvec1, t_cvector cvec2);
t_cvector	cvector_normalize(t_cvector cvec);
void		cvector_print(t_cvector cvec); // TODO: remove

// functions for polar vectors:
t_pvector	pvector(double r, double phi);
t_pvector	coords_to_pvector(double x, double y);
t_pvector	pvector_scale(t_pvector pvec, double factor);
t_pvector	pvector_rotate(t_pvector pvec, double rot_angle);
void		pvector_print(t_pvector pvec);	//TODO: remove

#endif  // VECTOR_H
