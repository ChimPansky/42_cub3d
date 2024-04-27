/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 10:30:58 by tkasbari          #+#    #+#             */
/*   Updated: 2024/04/27 17:55:21 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include <math.h>

// differentiate between the 4 quadrants in the trigonometric circle
void	raycaster_set_directions(t_ray *ray)
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

t_ray	ray_init(t_pos pos, double angle)
{
	t_ray	ray;

	ray.origin = pos;
	ray.vec = pvector(1.0, angle);
	raycaster_set_directions(&ray);
	raycaster_reset(&ray);
	return (ray);
}
