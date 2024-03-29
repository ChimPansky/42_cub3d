#include "logic.h"
#include <math.h>

void	process_inputs(t_game_state *game_state, t_inputs *inputs)
{
	game_state->player.speed.forw = inputs->w - inputs->s;
	game_state->player.speed.ort = inputs->d - inputs->a;
	game_state->player.rot_speed = inputs->right - inputs->left;
}

void	change_state_for_next_frame(t_game_state *game_state)
{
	t_player	*player;

	player = &game_state->player;
	player->angle += player->rot_speed * PLAYER_RAD_PER_FRAME;
	update_coords(&player->pos, &player->speed, player->angle,
		PLAYER_SPEED_FIELD_PER_FRAME);
}
