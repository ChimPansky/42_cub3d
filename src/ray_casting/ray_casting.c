/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:43:47 by tkasbari          #+#    #+#             */
/*   Updated: 2024/04/09 16:59:55 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../structs/ray.h"
#include "../structs/map.h"
#include "structs/physics.h"
#include "structs/sprites.h"
#include <math.h>

static void calculate_first_collision(t_raycaster *rc)
{
	if (rc->map_dir_x > 0)
		rc->x_ray_len = rc->delta_ray.x
			* ((int)rc->end_point.x + 1 - rc->end_point.x);
	else
		rc->x_ray_len = rc->delta_ray.x
			* (rc->end_point.x - (int)rc->end_point.x);
	if (rc->map_dir_y > 0)
		rc->y_ray_len = rc->delta_ray.y
			* (rc->end_point.y - (int)rc->end_point.y);
	else
		rc->y_ray_len = rc->delta_ray.y
			* ((int)rc->end_point.y + 1 - rc->end_point.y);
}

// differentiate between the 4 quadrants in the trigonometric circle
static void	raycaster_set_directions(t_ray *ray)
{
	if (ray->vec.phi <= M_PI / 2)
	{
		ray->rc.map_dir_x = 1;
		ray->rc.map_dir_y = 1;
	}
	else if (ray->vec.phi <= M_PI)
	{
		ray->rc.map_dir_x = -1;
		ray->rc.map_dir_y = 1;
	}
	else if (ray->vec.phi <= 3 * M_PI / 2)
	{
		ray->rc.map_dir_x = -1;
		ray->rc.map_dir_y = -1;
	}
	else
	{
		ray->rc.map_dir_x = 1;
		ray->rc.map_dir_y = -1;
	}
}

void	ray_reset(t_ray *ray)
{
	ray->vec.r = 0;
	ray->rc.end_point = ray->origin;
	ray->rc.map_x = (int)ray->origin.x;
	ray->rc.map_y = (int)ray->origin.y;
	raycaster_set_directions(ray);
	ray->rc.delta_ray = cvector(sqrt(1 + pow(tan(ray->vec.phi), 2)),
		sqrt(1 + pow(1 / tan(ray->vec.phi), 2)));
	ray->rc.x_ray_len = 0.0;
	ray->rc.y_ray_len = 0.0;
	ray->rc.sprite_collision = NO_SPRITE;
}

void	calculate_ray_wall_collision(t_ray *ray, t_map *map)
{
	ray_reset(ray);
	calculate_first_collision(&ray->rc);
	while (ray->rc.sprite_collision == NO_SPRITE)
	{
		if (ray->rc.x_ray_len < ray->rc.y_ray_len)
		{
			ray->vec.r = ray->rc.x_ray_len;
			ray->rc.x_ray_len += ray->rc.delta_ray.x;
			ray->rc.map_x += ray->rc.map_dir_x;
		}
		else
		{
			ray->vec.r = ray->rc.y_ray_len;
			ray->rc.y_ray_len += ray->rc.delta_ray.y;
			ray->rc.map_y += ray->rc.map_dir_y;
		}
		ray->rc.end_point = pos_add_pvec(ray->origin, ray->vec);
		check_for_sprite_collision(map, ray);
	}
}
