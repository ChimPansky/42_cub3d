/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 10:30:58 by tkasbari          #+#    #+#             */
/*   Updated: 2024/05/05 09:22:04 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "vector.h"
#include <math.h>

// differentiate between the 4 quadrants in the trigonometric circle
void	raycaster_set_map_directions(t_ray *ray)
{
	if (ray->vec.phi <= M_PI / 2)
	{
		ray->raycaster.map_dir_x = 1;
		ray->raycaster.map_dir_y = 1;
	}
	else if (ray->vec.phi <= M_PI)
	{
		ray->raycaster.map_dir_x = -1;
		ray->raycaster.map_dir_y = 1;
	}
	else if (ray->vec.phi <= 3 * M_PI / 2)
	{
		ray->raycaster.map_dir_x = -1;
		ray->raycaster.map_dir_y = -1;
	}
	else
	{
		ray->raycaster.map_dir_x = 1;
		ray->raycaster.map_dir_y = -1;
	}
}

void	raycaster_set_collision_angle(t_ray *ray)
{
	if (ray->raycaster.collision.direction == COLL_EA)
		ray->raycaster.collision.orth_angle = 0;
	else if (ray->raycaster.collision.direction == COLL_SO)
		ray->raycaster.collision.orth_angle = M_PI_2;
	else if (ray->raycaster.collision.direction == COLL_WE)
		ray->raycaster.collision.orth_angle = M_PI;
	else if (ray->raycaster.collision.direction == COLL_NO)
		ray->raycaster.collision.orth_angle = 3 * M_PI_2;
}

void	raycaster_set_collision_direction(t_raycaster *rc)
{
	if (fabs(rc->collision.point.x - round(rc->collision.point.x))
		< fabs(rc->collision.point.y - round(rc->collision.point.y)))
	{
		if (rc->map_dir_x > 0)
			rc->collision.direction = COLL_EA;
		else
			rc->collision.direction = COLL_WE;
	}
	else
	{
		if (rc->map_dir_y > 0)
			rc->collision.direction = COLL_SO;
		else
			rc->collision.direction = COLL_NO;
	}
}

t_ray	ray_init(t_pos pos, double angle)
{
	t_ray	ray;

	ray.origin = pos;
	ray.vec = pvector(1.0, angle);
	return (ray);
}
