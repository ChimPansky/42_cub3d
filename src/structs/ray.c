/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:43:47 by tkasbari          #+#    #+#             */
/*   Updated: 2024/04/17 13:22:38 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "map.h"
#include "physics.h"
#include "sprites.h"
#include <math.h>

void		calculate_ray_collision(t_ray *ray, t_map *map);
static void	raycaster_reset(t_ray *ray);
static void calculate_first_collision(t_raycaster *raycaster);
static void	check_for_sprite_collision(t_map *map, t_ray *ray);
static int	get_collision_direction(t_raycaster *raycaster);

static int	get_collision_direction(t_raycaster *raycaster)
{
	if (fabs(raycaster->end_point.x - round(raycaster->end_point.x))
		< fabs(raycaster->end_point.y - round(raycaster->end_point.y)))
	{
		if (raycaster->map_dir_x > 0)
			return (COLL_EA);
		else
		 	return (COLL_WE);
	}
	else
	{
		if (raycaster->map_dir_y > 0)
			return (COLL_SO);
		else
		 	return (COLL_NO);
	}
}

// Wall order: EA->SO->WE->NO (clockwise like our phi)
static void check_for_sprite_collision(t_map *map, t_ray *ray)
{
	t_map_sym				cur_sym;
	t_collision_direction	coll_dir;

	cur_sym = map->raw_map.buf[ray->raycaster.map_y][ray->raycaster.map_x];
	if (cur_sym == PATH_SYM)
	{
		ray->raycaster.sprite_collision = NO_SPRITE;
		return ;
	}
	coll_dir = get_collision_direction(&ray->raycaster);
	if (cur_sym == WALL_SYM)
		ray->raycaster.sprite_collision = WALL_EA + coll_dir;
}

static void calculate_first_collision(t_raycaster *raycaster)
{
	if (raycaster->map_dir_x > 0)
		raycaster->x_ray_len = raycaster->delta_ray.x *
			(ceil(raycaster->end_point.x) - raycaster->end_point.x);
	else
		raycaster->x_ray_len = raycaster->delta_ray.x *
			(raycaster->end_point.x - floor(raycaster->end_point.x));
	if (raycaster->map_dir_y > 0)
		raycaster->y_ray_len = raycaster->delta_ray.y *
			(ceil(raycaster->end_point.y) - raycaster->end_point.y);
	else
		raycaster->y_ray_len = raycaster->delta_ray.y *
			(raycaster->end_point.y - floor(raycaster->end_point.y));
}

static void	raycaster_reset(t_ray *ray)
{
	ray->raycaster.end_point = ray->origin;
	ray->raycaster.map_x = (int)ray->origin.x;
	ray->raycaster.map_y = (int)ray->origin.y;
	raycaster_set_directions(ray);
	ray->raycaster.delta_ray = cvector(sqrt(1 + pow(tan(ray->vec.phi), 2)),
		sqrt(1 + pow(1 / tan(ray->vec.phi), 2)));
	ray->raycaster.x_ray_len = 0.0;
	ray->raycaster.y_ray_len = 0.0;
	ray->raycaster.sprite_collision = NO_SPRITE;
}

void	calculate_ray_collision(t_ray *ray, t_map *map)
{
	raycaster_reset(ray);
	calculate_first_collision(&ray->raycaster);
	while (ray->raycaster.sprite_collision == NO_SPRITE)
	{
		if (ray->raycaster.x_ray_len < ray->raycaster.y_ray_len)
		{
			ray->vec.r = ray->raycaster.x_ray_len;
			ray->raycaster.x_ray_len += ray->raycaster.delta_ray.x;
			ray->raycaster.map_x += ray->raycaster.map_dir_x;
		}
		else
		{
			ray->vec.r = ray->raycaster.y_ray_len;
			ray->raycaster.y_ray_len += ray->raycaster.delta_ray.y;
			ray->raycaster.map_y += ray->raycaster.map_dir_y;
		}
		ray->raycaster.end_point = pos_add_pvec(ray->origin, ray->vec);
		check_for_sprite_collision(map, ray);
	}
}
