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

t_pos	pos_add_pvec(t_pos pos, t_pvector pvec)
{
	t_pos	result;

	result.x = pos.x + pvec.r * cos(pvec.phi);
	result.y = pos.y + pvec.r * sin(pvec.phi);
	return (result);
}

t_pos	pos_sub_pvec(t_pos pos, t_pvector pvec)
{
	t_pos	result;

	result.x = pos.x - pvec.r * cos(pvec.phi);
	result.y = pos.y - pvec.r * sin(pvec.phi);
	return (result);
}
