/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:42:05 by tkasbari          #+#    #+#             */
/*   Updated: 2024/04/27 17:46:20 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_state.h"
#include "structs/ray.h"

#include <stdio.h>
void	player_trigger_action(t_game_state *game)
{
	(void)game;
	printf("Player triggered action\n");
	t_ray	player_view;

	player_view = ray_init(game->player.pos, game->player.angle);

}
