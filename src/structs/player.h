#ifndef PLAYER_H
# define PLAYER_H

# include "physics.h"

typedef struct s_player
{
	t_pos	pos;
	t_speed	speed;
	double	angle;
}				t_player;

#endif  // PLAYER_H
