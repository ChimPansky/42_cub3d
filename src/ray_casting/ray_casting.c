/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:43:47 by tkasbari          #+#    #+#             */
/*   Updated: 2024/04/07 18:45:00 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_casting.h"
#include "../structs/map.h"
#include "structs/app.h"
#include "structs/physics.h"
#include "structs/sprites.h"
#include "utils.h"
#include <math.h>

static void calculate_first_collision(t_raycaster *rc)
{
	if (rc->x_dir_positive)
		rc->ray_len.x = rc->ray_step_len.x
			* ((int)rc->current_pos.x + 1 - rc->current_pos.x);
	else
		rc->ray_len.x = rc->ray_step_len.x
			* (rc->current_pos.x - (int)rc->current_pos.x);
	if (rc->y_dir_positive)
		rc->ray_len.y = rc->ray_step_len.y
			* (rc->current_pos.y - (int)rc->current_pos.y);
	else
		rc->ray_len.y = rc->ray_step_len.y
			* ((int)rc->current_pos.y + 1 - rc->current_pos.y);
}

// differentiate between the 4 quadrants in the trigonometric circle
static void	raycaster_set_directions(t_raycaster *raycaster)
{
	if (raycaster->phi <= M_PI / 2)
	{
		raycaster->x_dir_positive = true;
		raycaster->y_dir_positive = true;
	}
	else if (raycaster->phi <= M_PI)
	{
		raycaster->x_dir_positive = false;
		raycaster->y_dir_positive = true;
	}
	else if (raycaster->phi <= 3 * M_PI / 2)
	{
		raycaster->x_dir_positive = false;
		raycaster->y_dir_positive = false;
	}
	else
	{
		raycaster->x_dir_positive = true;
		raycaster->y_dir_positive = false;
	}
}

// make sure that the rc->phi == M_PI comparisons work with double...
void	raycaster_init(t_raycaster *rc, t_ray *ray)
{
	ft_bzero(rc, sizeof(t_raycaster));
	rc->phi = ray->direction.phi;// SEGFAULT
	raycaster_set_directions(rc);
	rc->current_pos = ray->origin;
	if (dbl_is_equal(rc->phi, 0.0) || dbl_is_equal(rc->phi, M_PI))
		rc->ray_step_len = cvector(1.0, 0.0);
	else if (dbl_is_equal(rc->phi, M_PI / 2)
		|| dbl_is_equal(rc->phi, 3 * M_PI / 2))
		rc->ray_step_len = cvector(0.0, 1.0);
	else
		rc->ray_step_len = cvector(sqrt(1 + pow(tan(ray->direction.phi), 2)),
							sqrt(1 + pow(1 / tan(ray->direction.phi), 2)));
}

static int get_collision_wall_type(t_raycaster *rc)
{
	if (dbl_is_zero(rc->current_pos.x - (int)rc->current_pos.x))
	{
		if (rc->x_dir_positive)
			return (WALL_EA);
		else
			return (WALL_WE);
	}
	else
	{
		if (rc->y_dir_positive)
			return (WALL_NO);
		else
			return (WALL_SO);
	}
}

// beware of negative distance from origin...
// make sure rc.ray_len.x > 0 works with double...
void	calculate_ray_wall_collision(t_ray *ray, t_map *map)
{
	t_raycaster	rc;

	raycaster_init(&rc, ray);
	calculate_first_collision(&rc);
	while (!rc.wall_hit)
	{
		if (!dbl_is_equal(rc.ray_len.x, 0.0) && rc.ray_len.x < rc.ray_len.y)
		{
			rc.collision_ray_len = rc.ray_len.x;
			rc.ray_len.x += rc.ray_step_len.x;
		}
		else
		{
			rc.collision_ray_len = rc.ray_len.y;
			rc.ray_len.y += rc.ray_step_len.y;
		}
		rc.current_pos = pos_add_pvec(ray->origin,
			pvector(rc.collision_ray_len, rc.phi));
		if (coord_to_map_sym(map, &rc.current_pos) == WALL_SYM)
			rc.wall_hit = true;
	}
	if (rc.wall_hit)
	{
		ray->collision.collision_point = rc.current_pos;
		ray->collision.distance_from_origin = rc.collision_ray_len;
		ray->collision.wall_type = get_collision_wall_type(&rc);
	}
	else	// should never happen: (leaks in this case)
	{
		exit(print_error("fatal: No ray collision found :("));
	}


	// ray->collision.collision_point = pos_create(0.0, 0.0);
	// ray->collision.distance_from_origin = pos_distance(ray->origin,
	// 	ray->collision.collision_point);
	// if (coord_to_map_sym(map, &raycaster.current_pos) == WALL_SYM)
	// 	raycaster.wall_hit = true;
}
