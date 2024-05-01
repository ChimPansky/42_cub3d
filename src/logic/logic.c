#include "logic.h"
#include "structs/physics.h"
#include "structs/player.h"
#include <math.h>
#include <stdbool.h>
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
