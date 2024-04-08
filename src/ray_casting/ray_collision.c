/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_collision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 10:30:58 by tkasbari          #+#    #+#             */
/*   Updated: 2024/04/08 12:22:58 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_casting.h"
#include "../utils.h"
#include "structs/map.h"
#include "structs/sprites.h"

static t_collision_direction	get_collision_direction(t_raycaster *rc)
{
	if (dbl_is_zero(rc->current_pos.x - (int)rc->current_pos.x))
	{
		if (rc->x_dir_positive)
			return (COLL_EA);
		else
		 	return (COLL_WE);
	}
	else
	{
		if (rc->y_dir_positive)
			return (COLL_SO);
		else
		 	return (COLL_NO);
	}
}

// Wall order: EA->SO->WE->NO (clockwise like our phi)
void check_for_sprite_collision(t_map *map, t_raycaster *rc)
{
	t_map_sym				cur_sym;
	t_collision_direction	coll_dir;

	cur_sym = coord_to_map_sym(map, &rc->current_pos);
	if (cur_sym == PATH_SYM)
	{
		rc->sprite_collision = NO_SPRITE;
		return ;
	}
	coll_dir = get_collision_direction(rc);
	if (cur_sym == WALL_SYM)
		rc->sprite_collision = WALL_EA + coll_dir;
}
