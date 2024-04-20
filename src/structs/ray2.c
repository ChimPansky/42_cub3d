/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 10:30:58 by tkasbari          #+#    #+#             */
/*   Updated: 2024/04/20 13:35:45 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include <math.h>
#include "../vector/vector.h"
#include "physics.h"

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

t_ray	ray(t_pos *origin, t_pvector *pvec)
{
	t_ray	result;

	result.origin = pos_copy(origin);
	result.vec = pvector_copy(pvec);
	ft_bzero(&result.raycaster, sizeof(t_raycaster));
	result.raycaster.fov_center_angle = pvec->phi;
	return (result);
}

t_ray	ray_copy(t_ray *ray)
{
	t_ray	result;

	result.origin = pos_copy(&ray->origin);
	result.vec = pvector_copy(&ray->vec);
	ft_memcpy(&result.raycaster, &ray->raycaster, sizeof(t_raycaster));
	return (result);
}
