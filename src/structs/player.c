/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:42:05 by tkasbari          #+#    #+#             */
/*   Updated: 2024/04/27 18:41:01 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_state.h"
#include "structs/door.h"
#include "structs/ray.h"
#include "structs/sprites.h"

#include <stdio.h>

static void	player_door_action(t_game_state *game, t_ray *player_view)
{
	t_door	*door;

	door = door_get(game->doors, player_view->raycaster.map_x, player_view->raycaster.map_y);
	if (door)
	{
		printf("Door found\n");
		if (door->is_open)
		{
			printf("Closing door\n");
			door->is_open = false;
		}
		else
		{
			printf("Opening door\n");
			door->is_open = true;
		}
	}
	else
		printf("No door found\n");
}

void	player_trigger_action(t_game_state *game)
{
	t_ray	player_view;

	printf("Player triggered action\n");

	player_view = ray_init(game->player.pos, game->player.angle);
	calculate_ray_collision(&player_view, &game->map);
	printf("Player view collision: %d\n", player_view.raycaster.collision.sprite);
	printf("Collision distance: %f\n", player_view.raycaster.collision.distance);
	printf("Collision point: (%f, %f)\n", player_view.raycaster.collision.point.x, player_view.raycaster.collision.point.y);
	printf("map_coordinates: (%d, %d)\n", player_view.raycaster.map_x, player_view.raycaster.map_y);
	if (player_view.raycaster.collision.sprite == DOOR_SPRITE
		&& player_view.raycaster.collision.distance < DOOR_TOGGLE_DISTANCE)
		player_door_action(game, &player_view);
}
