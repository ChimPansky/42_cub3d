#include "logic.h"
#include "../cub3d.h"
#include <math.h>

#define PLAYER_SPEED_FIELD_PER_FRAME 0.01

void	process_logic(t_app *app)
{
	t_player	*player;
	player = &app->cub.player;
	if (app->pressed_keys.w)
		player->speed.forw = 1;
	else if (app->pressed_keys.s)
		player->speed.forw = -1;
	else
		player->speed.forw = 0;
	if (app->pressed_keys.d)
		player->speed.ort = 1;
	else if (app->pressed_keys.a)
		player->speed.ort = -1;
	else
		player->speed.ort = 0;
	player->pos.y += (player->speed.forw * sin(player->angle)
			+ player->speed.ort * cos(player->angle))
		* PLAYER_SPEED_FIELD_PER_FRAME;
	player->pos.x += (player->speed.forw * cos(player->angle)
			- player->speed.ort * sin(player->angle))
		* PLAYER_SPEED_FIELD_PER_FRAME;
}
