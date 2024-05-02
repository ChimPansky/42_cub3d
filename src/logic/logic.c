#include "logic.h"
#include "structs/physics.h"
#include "structs/player.h"
#include "structs/door.h"
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

	player = &game_state->player;
	if (!dbl_is_almost_zero(player->rot_speed))
		player->angle += player->rot_speed * PLAYER_RAD_PER_FRAME;
	if (!dbl_is_almost_zero(player->speed.forw)
		|| !dbl_is_almost_zero(player->speed.ort))
	{
		player_move(game_state);
		player_adjust_player_distance_from_walls(game_state);
	}
	doors_check_and_close(game_state, &game_state->map.doors);
}
