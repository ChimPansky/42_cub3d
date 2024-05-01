/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:43:03 by tkasbari          #+#    #+#             */
/*   Updated: 2024/05/01 11:42:23 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "cub3d.h"
# include "physics.h"

# define PLAYER_COLLISION_RADIUS 0.1
# define PLAYER_SPEED_FIELD_PER_FRAME	1. / FPS * 2

typedef struct  s_game_state t_game_state;

typedef struct s_player
{
	t_pos	pos;
	t_speed	speed;
	double	angle;
	double	rot_speed;
}				t_player;

void 	player_move(t_game_state *game);
void	player_adjust_player_distance_from_walls(t_game_state *game);
void	player_trigger_action(t_game_state *game);

#endif  // PLAYER_H
