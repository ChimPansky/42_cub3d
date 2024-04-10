/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_collision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 10:30:58 by tkasbari          #+#    #+#             */
/*   Updated: 2024/04/10 16:35:02 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "../structs/ray.h"
#include "../utils.h"
#include "structs/map.h"
#include "structs/sprites.h"

static t_collision_direction	get_collision_direction(t_raycaster *rc)
{
	if (fabs(rc->end_point.x - round(rc->end_point.x))
		< fabs(rc->end_point.y - round(rc->end_point.y)))
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
void check_for_sprite_collision(t_map *map, t_ray *ray)
{
	t_map_sym				cur_sym;
	t_collision_direction	coll_dir;

	cur_sym = map->raw_map.buf[ray->rc.map_y][ray->rc.map_x];
	if (cur_sym == PATH_SYM)
	{
		ray->rc.sprite_collision = NO_SPRITE;
		return ;
	}
	coll_dir = get_collision_direction(&ray->rc);
	if (cur_sym == WALL_SYM)
		ray->rc.sprite_collision = WALL_EA + coll_dir;
}
