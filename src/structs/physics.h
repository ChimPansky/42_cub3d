#ifndef PHYSICS_H
# define PHYSICS_H

# include "vector.h"

typedef struct s_pos
{
	double	x;
	double	y;
}				t_pos;

typedef struct s_speed
{
	double	forw;
	double	ort;
}				t_speed;

void	update_coords(
			t_pos *pos,
			t_speed *speed,
			double angle,
			double speed_to_coord_coef);

t_pos	pos_add_pvec(t_pos pos, t_pvector pvec);
t_pos	pos_sub_pvec(t_pos pos, t_pvector pvec);

#endif  // PHYSICS_H
