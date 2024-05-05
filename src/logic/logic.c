/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:33:31 by vvilensk          #+#    #+#             */
/*   Updated: 2024/05/05 09:24:08 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "logic.h"
#include "physics.h"
#include "player.h"
#include "door.h"
#include "ray.h"
#include "app.h"
#include "cub3d.h"

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
	player->angle += player->rot_speed * PLAYER_RAD_PER_FRAME;
	if (player->speed.forw || player->speed.ort)
	{
		player_move(game_state);
		player_adjust_player_distance_from_walls(game_state);
	}
	doors_check_and_close(game_state, &game_state->map.doors);
}

static void	player_door_action(t_game_state *game, t_ray *player_view)
{
	t_door	*door;

	door = door_get(game->map.doors, player_view->raycaster.map_x,
			player_view->raycaster.map_y);
	if (door)
	{
		if (door->is_open)
			door->is_open = false;
		else
			door->is_open = true;
	}
}

void	player_trigger_action(t_app *app)
{
	t_ray	player_view;

	app->gr.leg.play = true;
	player_view = ray_init(app->game_state.player.pos,
			app->game_state.player.angle);
	calculate_ray_collision(&player_view, &app->game_state.map);
	if (player_view.raycaster.collision.sprite == DOOR_SPRITE
		&& player_view.raycaster.collision.distance < DOOR_OPENING_DISTANCE)
		player_door_action(&app->game_state, &player_view);
	if (app->god_mode)
		try_change_map_symb(&app->game_state.map, player_view.raycaster.map_x,
			player_view.raycaster.map_y, PATH_SYM);
}
