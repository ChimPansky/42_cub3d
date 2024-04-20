#ifndef PLAYER_H
# define PLAYER_H

# include "physics.h"
# include "ray.h"

typedef struct s_player
{
	t_ray	view;
	t_speed	speed;
	double	rot_speed;
}				t_player;

#endif  // PLAYER_H
