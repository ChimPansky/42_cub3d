#include "physics.h"
#include <math.h>

void	update_coords(
			t_pos *pos,
			t_speed *speed,
			double angle,
			double speed_to_coord_coef)
{
	pos->y += (speed->forw * sin(angle) + speed->ort * cos(angle))
		* speed_to_coord_coef;
	pos->x += (speed->forw * cos(angle) - speed->ort * sin(angle))
		* speed_to_coord_coef;
}

