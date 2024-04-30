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

static double	add_sliding_movement(t_raycaster *rc, t_pvector *movement)
{
	if (rc->collision.direction == COLL_EA)
	{
		if (rc->map_dir_y > 0)
			movement->phi = M_PI_2;
		else
			movement->phi = 3 * M_PI_2;
	}
	if (rc->collision.direction == COLL_WE)
	{
		if (rc->map_dir_y > 0)
			movement->phi = M_PI_2;
		else
			movement->phi = 3 * M_PI_2;
	}
	if (rc->collision.direction == COLL_NO)
	{
		if (rc->map_dir_x > 0)
			movement->phi = 0;
		else
			movement->phi = M_PI;
	}
	if (rc->collision.direction == COLL_SO)
	{
		if (rc->map_dir_x > 0)
			movement->phi = 0;
		else
			movement->phi = M_PI;
	}
	return (0);
}

#include <stdio.h>
static void move_player(t_game_state *game, t_pvector *movement)
{
	t_ray	move_ray;
	double	remaining_distance;
	double	coll_distance;
	int		i;

	i = 0;
	remaining_distance = movement->r;
	while (remaining_distance > 0)
	{
		// if (i > 5)
		// 	break ;
		move_ray = ray_init(game->player.pos, movement->phi);
		calculate_ray_collision(&move_ray, &game->map);

		coll_distance = move_ray.raycaster.collision.distance;
		if (movement->r > coll_distance - 0.0000001)
		{
			if (fabs(fabs(move_ray.vec.phi - move_ray.raycaster.collision.normal_angle) - M_PI) < 0.1)
			{
				printf("ORTHOGONAL COLLISION\n");
				break;
			}
			movement->r = coll_distance - 0.0000001;
		}

		game->player.pos = pos_add_pvec(game->player.pos, *movement);
		remaining_distance = fmax(remaining_distance - movement->r, 0); // adjust remaining distance: eliminate x or y part of vector (depending form map_x_dir and map_y_dir)
		movement->r = remaining_distance;
		if (remaining_distance > 0)
			add_sliding_movement(&move_ray.raycaster, movement);
		printf("player-pos: %f, %f\n", game->player.pos.x, game->player.pos.y);
		printf("MOVING: %d\n", i++);
		printf("remaining_distance: %f\n", remaining_distance);
		printf("coll_distance: %f\n", coll_distance);
		printf("movement->r: %f\n", movement->r);
		printf("movement->phi: %f\n", movement->phi);
	}
}

void	adjust_player_distance_from_walls(t_game_state *game)
{
	t_pos	*pos = &game->player.pos;

	if (pos->x - floor(pos->x) < PLAYER_COLLISION_RADIUS
		&& coord_to_map_sym(&game->map, cvector(pos->x - 1, pos->y)) == WALL_SYM)
		pos->x = floor(pos->x) + PLAYER_COLLISION_RADIUS;
	if (pos->y - floor(pos->y) < PLAYER_COLLISION_RADIUS
	&& coord_to_map_sym(&game->map, cvector(pos->x, pos->y - 1)) == WALL_SYM)
		pos->y = floor(pos->y) + PLAYER_COLLISION_RADIUS;
	if (ceil(pos->x) - pos->x < PLAYER_COLLISION_RADIUS
		&& coord_to_map_sym(&game->map, cvector(pos->x + 1, pos->y)) == WALL_SYM)
		pos->x = ceil(pos->x) - PLAYER_COLLISION_RADIUS;
	if (ceil(pos->y) - pos->y < PLAYER_COLLISION_RADIUS
		&& coord_to_map_sym(&game->map, cvector(pos->x, pos->y + 1)) == WALL_SYM)
		pos->y = ceil(pos->y) - PLAYER_COLLISION_RADIUS;
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
