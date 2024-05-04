/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvilensk <vilenskii.v@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:39:40 by tkasbari          #+#    #+#             */
/*   Updated: 2024/05/04 15:22:51 by vvilensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <stdbool.h>

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
double		cvector_get_mod(const t_cvector *cvec);
void		cvector_normalize(t_cvector *cvec);
void		cvector_print(const t_cvector *cvec);

// functions for polar vectors:
t_pvector	pvector(double r, double phi);
t_pvector	pvector_from_coords(double x, double y);
void		pvector_rotate(t_pvector *pvec, double rot_angle);
void		pvector_print(const t_pvector *pvec);

t_cvector	cvector_transform(t_cvector *cvec, t_pvector *pvec);

#endif  // VECTOR_H
