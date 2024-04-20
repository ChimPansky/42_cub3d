#ifndef PLAYER_H
# define PLAYER_H

# include "physics.h"

typedef struct  s_game_state t_game_state;

typedef struct s_player
{
	t_pos	pos;
	t_speed	speed;
	double	angle;
	double	rot_speed;
}				t_player;

void	player_trigger_action(t_game_state *game);

#endif  // PLAYER_H
