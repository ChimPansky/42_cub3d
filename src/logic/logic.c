#include "logic.h"
#include "structs/map.h"
#include "structs/physics.h"
#include "structs/player.h"
#include "structs/ray.h"
#include <math.h>
#include <stdbool.h>
#include "./structs/ray.h"
#include "./vector/vector.h"

void	process_inputs(t_game_state *game_state, t_inputs *inputs)
{
	game_state->player.speed.forw = inputs->w - inputs->s;
	game_state->player.speed.ort = inputs->d - inputs->a;
	game_state->player.rot_speed = inputs->right - inputs->left;
	game_state->player.angle += inputs->mouse_dx * PLAYER_RAD_PER_MOUSE_PIX;
	inputs->mouse_dx = 0;
	inputs->mouse_dy = 0;
}

static void	calculate_sliding_movement(t_raycaster *rc, t_pvector *movement)
{
	double	r_scaling;
	double	collision_angle;

	r_scaling = 1.0;
	if (rc->collision.direction == COLL_EA)
	{
		collision_angle = movement->phi;
		r_scaling = movement->phi * (1 - cos(collision_angle) * cos(collision_angle));
		if (rc->map_dir_y > 0)
			movement->phi = M_PI_2;
		else
			movement->phi = 3 * M_PI_2;
	}
	if (rc->collision.direction == COLL_SO)
	{
		collision_angle = fabs(movement->phi - M_PI_2);
		r_scaling = movement->phi * (1 - sin(collision_angle) * sin(collision_angle));
		if (rc->map_dir_x > 0)
			movement->phi = 0;
		else
			movement->phi = M_PI;
	}
	if (rc->collision.direction == COLL_WE)
	{
		collision_angle = fabs(movement->phi - M_PI);
		r_scaling = movement->phi * (1 - cos(collision_angle) * cos(collision_angle));
		if (rc->map_dir_y > 0)
			movement->phi = M_PI_2;
		else
			movement->phi = 3 * M_PI_2;
	}
	if (rc->collision.direction == COLL_NO)
	{
		collision_angle = fabs(movement->phi - 3 * M_PI_2);
		r_scaling = movement->phi * (1 - sin(collision_angle) * sin(collision_angle));
		if (rc->map_dir_x > 0)
			movement->phi = 0;
		else
			movement->phi = M_PI;
	}
	movement->r *= r_scaling;
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

static void	adjust_player_distance_from_walls(t_game_state *game)
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

static void move_player(t_game_state *game, t_pvector *movement_vec)
{
	t_ray	movement_ray;
	double	remaining_distance;

	remaining_distance = movement_vec->r;
	move_until_collision(movement_vec, &movement_ray, game);
	remaining_distance = remaining_distance - movement_vec->r;
	if (!(remaining_distance > 0))
		return ;
	movement_vec->r = remaining_distance;
	calculate_sliding_movement(&movement_ray.raycaster, movement_vec);
	move_until_collision(movement_vec, &movement_ray, game);
}

void	change_state_for_next_frame(t_game_state *game_state)
{
	t_player	*player;
	t_pvector	movement;

	player = &game_state->player;
	if (!dbl_is_almost_zero(player->rot_speed))
		player->angle += player->rot_speed * PLAYER_RAD_PER_FRAME;
	if (dbl_is_almost_zero(player->speed.forw) && dbl_is_almost_zero(player->speed.ort))
		return ;
	movement = pvector_from_coords(
		(player->speed.forw * cos(player->angle) - player->speed.ort
		* sin(player->angle)) * PLAYER_SPEED_FIELD_PER_FRAME,
		(player->speed.forw * sin(player->angle) + player->speed.ort
		* cos(player->angle)) * PLAYER_SPEED_FIELD_PER_FRAME);
	move_player(game_state, &movement);
	adjust_player_distance_from_walls(game_state);
}
