/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:43:47 by tkasbari          #+#    #+#             */
/*   Updated: 2024/04/17 17:03:02 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "map.h"
#include "physics.h"
#include "sprites.h"
#include <math.h>

void		calculate_ray_collision(t_ray *ray, t_map *map);
static void	raycaster_reset(t_ray *ray);
static void calculate_first_collision_distance(t_ray *ray);
static void	check_for_sprite_collision(t_map *map, t_ray *ray);
static int	get_collision_direction(t_raycaster *raycaster);

static int	get_collision_direction(t_raycaster *rc)
{
	if (fabs(rc->collision.point.x - round(rc->collision.point.x))
		< fabs(rc->collision.point.y - round(rc->collision.point.y)))
	{
		if (rc->map_dir_x > 0)
			return (COLL_EA);
		else
		 	return (COLL_WE);
	}
	else
	{
		if (rc->map_dir_y > 0)
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
		ray->raycaster.collision.sprite = NO_SPRITE;
		return ;
	}
	coll_dir = get_collision_direction(&ray->raycaster);
	if (cur_sym == WALL_SYM)
		ray->raycaster.collision.sprite = WALL_EA + coll_dir;
}

static void calculate_first_collision_distance(t_ray *ray)
{
	if (ray->raycaster.map_dir_x > 0)
		ray->raycaster.x_ray_len = ray->raycaster.delta_ray.x *
			(ceil(ray->origin.x) - ray->origin.x);
	else
		ray->raycaster.x_ray_len = ray->raycaster.delta_ray.x *
			(ray->origin.x - floor(ray->origin.x));
	if (ray->raycaster.map_dir_y > 0)
		ray->raycaster.y_ray_len = ray->raycaster.delta_ray.y *
			(ceil(ray->origin.y) - ray->origin.y);
	else
		ray->raycaster.y_ray_len = ray->raycaster.delta_ray.y *
			(ray->origin.y - floor(ray->origin.y));
}

static void	raycaster_reset(t_ray *ray)
{
	ft_bzero(&ray->raycaster.collision, sizeof(t_ray_collision));
	//ray->raycaster.collision.point.x = ray->origin.x;
	//ray->raycaster.collision.point.y = ray->origin.y;
	ray->raycaster.map_x = (int)ray->origin.x;
	ray->raycaster.map_y = (int)ray->origin.y;
	raycaster_set_directions(ray);
	ray->raycaster.delta_ray = cvector(sqrt(1 + pow(tan(ray->vec.phi), 2)),
		sqrt(1 + pow(1 / tan(ray->vec.phi), 2)));
	ray->raycaster.x_ray_len = 0.0;
	ray->raycaster.y_ray_len = 0.0;
	ray->raycaster.collision.sprite = NO_SPRITE;
}

void	calculate_ray_collision(t_ray *ray, t_map *map)
{
	raycaster_reset(ray);
	calculate_first_collision_distance(ray);
	while (ray->raycaster.collision.sprite == NO_SPRITE)
	{
		if (ray->raycaster.x_ray_len < ray->raycaster.y_ray_len)
		{
			ray->raycaster.collision.distance =
				ray->raycaster.x_ray_len;
			ray->raycaster.x_ray_len += ray->raycaster.delta_ray.x;
			ray->raycaster.map_x += ray->raycaster.map_dir_x;
		}
		else
		{
			ray->raycaster.collision.distance =
				ray->raycaster.y_ray_len;
			ray->raycaster.y_ray_len += ray->raycaster.delta_ray.y;
			ray->raycaster.map_y += ray->raycaster.map_dir_y;
		}
		check_for_sprite_collision(map, ray);
		ray->raycaster.collision.point = pos_add_pvec(ray->origin,
			pvector(ray->raycaster.collision.distance, ray->vec.phi));
	}
}
