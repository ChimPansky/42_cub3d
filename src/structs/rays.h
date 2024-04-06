#ifndef RAYS_H
# define RAYS_H

# include <math.h>
# include "structs/app.h"
# include "vector.h"
# include "sprites.h"
# include "physics.h"
# include "map.h"

typedef struct s_ray_collision
{
	t_pos				collision_point;
	double				distance_from_origin;
	enum e_sprite_types	wall_type;
}				t_ray_collision;

typedef struct s_ray
{
	t_pos			origin;
	t_pvector		direction;
	t_ray_collision	collision;
}				t_ray;

#endif  // RAYS_H
