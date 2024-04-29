#include "logic.h"
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

bool	player_can_move_orth(t_game_state *game)
{
	t_ray		move_ray;

	if (game->player.speed.ort > 0)
		move_ray = ray_init(game->player.pos, game->player.angle + M_PI / 2);
	else
		move_ray = ray_init(game->player.pos, game->player.angle - M_PI / 2);
	calculate_ray_collision(&move_ray, &game->map);
	if (move_ray.raycaster.collision.distance
		< PLAYER_SPEED_FIELD_PER_FRAME)
		return (false);
	return (true);
}


bool	player_can_move_forw(t_game_state *game)
{
	t_ray		move_ray;

	if (game->player.speed.forw > 0)
		move_ray = ray_init(game->player.pos, game->player.angle);
	else
		move_ray = ray_init(game->player.pos, game->player.angle + M_PI);
	calculate_ray_collision(&move_ray, &game->map);
	if (move_ray.raycaster.collision.distance
		< PLAYER_SPEED_FIELD_PER_FRAME)
		return (false);
	return (true);
}

// static void	calc_pos_change(t_game_state *game, t_cvector *pos_change)
// {
// 	pos_change->x = (game->player.speed.forw * cos(game->player.angle)
// 		- game->player.speed.ort * sin(game->player.angle)) * PLAYER_SPEED_FIELD_PER_FRAME;
// 	pos_change->y = (game->player.speed.forw * sin(game->player.angle)
// 		+ game->player.speed.ort * cos(game->player.angle)) * PLAYER_SPEED_FIELD_PER_FRAME;
// }

static void	apply_collision_to_pos_change(t_game_state *game, t_pvector *pos_change)
{
	t_ray		move_ray;
	double		move_until_collision_scale;
	t_pvector	slide_along_sprite;
	double		slide_angle;

	move_ray = ray_init(game->player.pos, pos_change->phi);
	calculate_ray_collision(&move_ray, &game->map);
	move_until_collision_scale = 1.0;
	if (move_ray.raycaster.collision.distance < PLAYER_SPEED_FIELD_PER_FRAME)
		move_until_collision_scale = move_ray.raycaster.collision.distance
			/ PLAYER_SPEED_FIELD_PER_FRAME;
	else
		return ;
	pvector_scale(pos_change, move_until_collision_scale);
	if (move_ray.raycaster.collision.direction == COLL_EA
		|| move_ray.raycaster.collision.direction == COLL_WE)
		slide_angle = M_PI / 2;
	else
		slide_angle = 0;
	slide_along_sprite = pvector(pos_change->r
		* (1 - move_until_collision_scale), slide_angle);
	pvector_add_pvector(pos_change, slide_along_sprite);
}

void	change_state_for_next_frame(t_game_state *game_state)
{
	t_player	*player;
	t_pvector	pos_change;

	player = &game_state->player;
	player->angle += player->rot_speed * PLAYER_RAD_PER_FRAME;
	if (!dbl_is_almost_zero(player->speed.forw))
		player->speed.forw *= player_can_move_forw(game_state);
	if (!dbl_is_almost_zero(player->speed.ort))
		player->speed.ort *= player_can_move_orth(game_state);
	pos_change = pvector_from_coords(
		(player->speed.forw * cos(player->angle) - player->speed.ort
		* sin(player->angle)) * PLAYER_SPEED_FIELD_PER_FRAME,
		(player->speed.forw * sin(player->angle) + player->speed.ort
		* cos(player->angle)) * PLAYER_SPEED_FIELD_PER_FRAME);
	apply_collision_to_pos_change(game_state, &pos_change);

	// calc_pos_change(game_state, &pos_change);
	player->pos = pos_add_pvec(player->pos, pos_change);

	// update_coords(&player->pos, &player->speed, player->angle,
	// 	PLAYER_SPEED_FIELD_PER_FRAME);
}
