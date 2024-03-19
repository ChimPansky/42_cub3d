/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:39:40 by tkasbari          #+#    #+#             */
/*   Updated: 2024/03/19 12:09:14 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

#include "math.h"

typedef struct s_vector
{
	double	x;
	double	y;
}				t_vector;

t_vector	vector(double x, double y);
double		get_vec_len(t_vector vec);
double		get_vec_angle(t_vector vec);
t_vector	vector_rotate(t_vector vec, double angle);
t_vector	vector_add(t_vector vec1, t_vector vec2);
t_vector	vector_sub(t_vector vec1, t_vector vec2);
t_vector	vector_mult(t_vector vec1, t_vector vec2);
t_vector	vector_normalize(t_vector vec);
void		vector_print(t_vector vec);

#endif  // VECTOR_H
