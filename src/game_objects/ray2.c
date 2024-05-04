/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvilensk <vilenskii.v@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 10:30:58 by tkasbari          #+#    #+#             */
/*   Updated: 2024/05/04 15:18:08 by vvilensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "vector.h"
#include "utils.h"
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
	if (dbl_is_almost_zero(ray->vec.phi - M_PI / 2)
		|| dbl_is_almost_zero(ray->vec.phi - 3 * M_PI / 2))
		ray->raycaster.map_dir_x = 0;
	if (dbl_is_almost_zero(ray->vec.phi)
		|| dbl_is_almost_zero(ray->vec.phi - M_PI))
		ray->raycaster.map_dir_y = 0;
}

t_ray	ray_init(t_pos pos, double angle)
{
	t_ray	ray;

	ray.origin = pos;
	ray.vec = pvector(1.0, angle);
	return (ray);
}
