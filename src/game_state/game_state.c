#include "game_state.h"
#include "../cub3d.h"
#include <math.h>

#define PLAYER_SPEED_FIELD_PER_FRAME 0.01

int	game_init(t_game_state *game)
{
	if (charptr_array_init(&game->map.raw_map) != SUCCESS)
		return (perror("cub_init: charptr_array_init"), FAILURE);
}

void	game_destroy(t_game_state *game)
{
	charptr_array_destroy(&game->map.raw_map);
}

void	process_logic(t_app *app)
{
	t_player	*player;

	player = &app->game.player;
	if (app->pressed_keys.w)
		player->speed.forw = 1;
	else if (app->pressed_keys.s)
		player->speed.forw = -1;
	if (app->pressed_keys.d)
		player->speed.ort = 1;
	else if (app->pressed_keys.a)
		player->speed.ort = -1;
	player->pos.x += (player->speed.forw * cos(player->angle)
			+ player->speed.forw * sin(player->angle))
		* PLAYER_SPEED_FIELD_PER_FRAME;
	player->pos.y += (player->speed.forw * sin(player->angle)
			+ player->speed.forw * cos(player->angle))
		* PLAYER_SPEED_FIELD_PER_FRAME;
}
