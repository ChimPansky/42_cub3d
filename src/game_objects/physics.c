/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 09:01:51 by tkasbari          #+#    #+#             */
/*   Updated: 2024/05/05 09:02:35 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include <math.h>

void	update_coords(
			t_pos *pos,
			t_speed *speed,
			double angle,
			double speed_to_coord_coef)
{
	pos->y += (speed->forw * sin(angle) + speed->ort * cos(angle))
		* speed_to_coord_coef;
	pos->x += (speed->forw * cos(angle) - speed->ort * sin(angle))
		* speed_to_coord_coef;
}

t_pos	pos_create(double x, double y)
{
	t_pos	result;

	result.x = x;
	result.y = y;
	return (result);
}

t_pos	pos_add_pvec(t_pos pos, t_pvector pvec)
{
	t_pos	result;

	result.x = pos.x + pvec.r * cos(pvec.phi);
	result.y = pos.y + pvec.r * sin(pvec.phi);
	return (result);
}

t_pos	pos_add_pos(t_pos pos1, t_pos pos2)
{
	t_pos	result;

	result.x = pos1.x + pos2.x;
	result.y = pos1.y + pos2.y;
	return (result);
}

double	pos_distance(t_pos pos1, t_pos pos2)
{
	return (sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2)));
}

// void	pos_print(t_pos pos)
// {
// 	printf("(%f / %f)\n", pos.x, pos.y);
// }
