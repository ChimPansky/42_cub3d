#ifndef PHYSICS_H
# define PHYSICS_H

# include "vector.h"
# include "structs/sprites.h"

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

typedef struct s_ray_collision
{
	t_pos				collision_point;
	double				distance_from_origin;
	enum e_sprite_types	wall_type;
}				t_ray_collision;

void	update_coords(
			t_pos *pos,
			t_speed *speed,
			double angle,
			double speed_to_coord_coef);

t_pos	pos_create(double x, double y);
t_pos	pos_add_pvec(t_pos pos, t_pvector pvec);
t_pos	pos_add_pos(t_pos pos1, t_pos pos2);

#endif  // PHYSICS_H
