/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvilensk <vilenskii.v@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 14:58:48 by vvilensk          #+#    #+#             */
/*   Updated: 2024/05/04 14:58:54 by vvilensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHYSICS_H
# define PHYSICS_H

# include "vector.h"

typedef t_cvector	t_pos;

typedef struct s_speed
{
	double	forw;
	double	ort;
}				t_speed;

void	update_coords(
			t_pos *pos,
			t_speed *speed,
			double angle,
			double speed_to_coord_coef);
t_pos	pos_create(double x, double y);
t_pos	pos_copy(t_pos *source);
t_pos	pos_add_pvec(t_pos pos, t_pvector pvec);
t_pos	pos_add_pos(t_pos pos1, t_pos pos2);
double	pos_distance(t_pos pos1, t_pos pos2);
void	pos_print(t_pos pos);

#endif  // PHYSICS_H
