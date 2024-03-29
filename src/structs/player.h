#ifndef PLAYER_H
# define PLAYER_H

# include "physics.h"

#define PLAYER_DISTANCE_FROM_SCREEN 1.5
typedef struct s_player
{
	t_pos	pos;
	t_speed	speed;
	double	angle;
	double	rot_speed;
}				t_player;

#endif  // PLAYER_H
