/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:42:05 by tkasbari          #+#    #+#             */
/*   Updated: 2024/05/01 11:43:07 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_state.h"
#include "structs/door.h"
#include "structs/ray.h"
#include "structs/sprites.h"
#include "math.h"
#include <stdio.h>

static void	calculate_sliding_movement(t_raycaster *rc, t_pvector *movement)
{
	double	shorten_sliding_distance;
	double	collision_angle;

	collision_angle = fabs(movement->phi - rc->collision.orth_angle);
	shorten_sliding_distance = movement->phi
		* (1 - cos(collision_angle) * cos(collision_angle)
		* (1 - sin(collision_angle) * sin(collision_angle)));
	if (rc->collision.direction == COLL_EA
		|| rc->collision.direction == COLL_WE)
	{
		if (rc->map_dir_y > 0)
			movement->phi = M_PI_2;
		else
			movement->phi = 3 * M_PI_2;
	}
	if (rc->collision.direction == COLL_SO
		|| rc->collision.direction == COLL_NO)
	{
		if (rc->map_dir_x > 0)
			movement->phi = 0;
		else
			movement->phi = M_PI;
	}
	movement->r *= shorten_sliding_distance;
}

static void move_until_collision(t_pvector * movement_vec,
	t_ray *movement_ray, t_game_state *game)
{
	*movement_ray = ray_init(game->player.pos, movement_vec->phi);
	calculate_ray_collision(movement_ray, &game->map);
	movement_vec->r = fmin(movement_vec->r,
		movement_ray->raycaster.collision.distance);
	game->player.pos = pos_add_pvec(game->player.pos, *movement_vec);
}

void	player_adjust_player_distance_from_walls(t_game_state *game)
{
	t_pos	*pos = &game->player.pos;

	if (pos->x - floor(pos->x) < PLAYER_COLLISION_RADIUS
		&& coords_are_collidable(&game->map, cvector(pos->x - 1, pos->y)))
		pos->x = floor(pos->x) + PLAYER_COLLISION_RADIUS;
	if (pos->y - floor(pos->y) < PLAYER_COLLISION_RADIUS
		&& coords_are_collidable(&game->map, cvector(pos->x, pos->y - 1)))
		pos->y = floor(pos->y) + PLAYER_COLLISION_RADIUS;
	if (ceil(pos->x) - pos->x < PLAYER_COLLISION_RADIUS
		&& coords_are_collidable(&game->map, cvector(pos->x + 1, pos->y)))
		pos->x = ceil(pos->x) - PLAYER_COLLISION_RADIUS;
	if (ceil(pos->y) - pos->y < PLAYER_COLLISION_RADIUS
		&& coords_are_collidable(&game->map, cvector(pos->x, pos->y + 1)))
		pos->y = ceil(pos->y) - PLAYER_COLLISION_RADIUS;
}

void player_move(t_game_state *game)
{
	t_player	*player;
	t_pvector	movement_vec;
	t_ray		movement_ray;
	double		remaining_distance;

	player = &game->player;
	movement_vec = pvector_from_coords(
		(player->speed.forw * cos(player->angle) - player->speed.ort
		* sin(player->angle)) * PLAYER_SPEED_FIELD_PER_FRAME,
		(player->speed.forw * sin(player->angle) + player->speed.ort
		* cos(player->angle)) * PLAYER_SPEED_FIELD_PER_FRAME);
	remaining_distance = movement_vec.r;
	move_until_collision(&movement_vec, &movement_ray, game);
	remaining_distance = remaining_distance - movement_vec.r;
	if (!(remaining_distance > 0))
		return ;
	movement_vec.r = remaining_distance;
	calculate_sliding_movement(&movement_ray.raycaster, &movement_vec);
	move_until_collision(&movement_vec, &movement_ray, game);
}
