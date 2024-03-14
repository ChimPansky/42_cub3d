#include "logic.h"
#include <math.h>

void	process_inputs(t_game_state *game_state, t_inputs *inputs)
{
	if (inputs->w)
		game_state->player.speed.forw = 1;
	else if (inputs->s)
		game_state->player.speed.forw = -1;
	else
		game_state->player.speed.forw = 0;
	if (inputs->d)
		game_state->player.speed.ort = 1;
	else if (inputs->a)
		game_state->player.speed.ort = -1;
	else
		game_state->player.speed.ort = 0;
}

void	change_state_for_next_frame(t_game_state *game_state)
{
	t_player	*player;

	player = &game_state->player;
	update_coords(&player->pos, &player->speed, player->angle,
		PLAYER_SPEED_FIELD_PER_FRAME);
}
