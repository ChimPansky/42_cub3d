#include "logic.h"
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

void	change_state_for_next_frame(t_game_state *game_state)
{
	t_player	*player;

	player = &game_state->player;
	player->angle += player->rot_speed * PLAYER_RAD_PER_FRAME;
	if (!dbl_is_almost_zero(player->speed.forw))
		player->speed.forw *= player_can_move_forw(game_state);
	if (!dbl_is_almost_zero(player->speed.ort))
		player->speed.ort *= player_can_move_orth(game_state);
	update_coords(&player->pos, &player->speed, player->angle,
		PLAYER_SPEED_FIELD_PER_FRAME);
}
