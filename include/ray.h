/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:43:54 by tkasbari          #+#    #+#             */
/*   Updated: 2024/04/09 16:42:37 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "vector.h"
# include "sprites.h"
# include "map.h"

// for now ray_casting is only used for rendering the walls (finding
// collision points between
// player view (a ray with starting position and viewing direction vector)
// and walls (as defined in map))
// later ray_casting can be used to find collision points between player and
// other objects...
typedef enum e_collision_direction
{
	COLL_EA = 0,
	COLL_SO = 1,
	COLL_WE = 2,
	COLL_NO = 3,
}	t_collision_direction;

typedef struct s_ray_collision
{
	t_pos					point;
	double					distance;
	t_sprite_types			sprite;
	t_collision_direction	direction;
	double					orth_angle;
}				t_ray_collision;

// collision: collision-coordinates, distance, direction and type of sprite hit
//	of the ray_collision with a map_square that is	not a path
// map_x, map_y: the indizes of the char** map
// map_dir_x, map_dir_y: x and y direction (1 or -1) depending on
//	quadrants of angle
// delta_ray.x: y change, if we advance +-1 in x_direction
// delta_ray.y: x change, if we advance +-1 in y_direction
// x_ray_len: the length of the ray until the next collision with a vert wall
// y_ray_len: the length of the ray until the next collision with a horiz wall
// fov_center_angle: for rendering multiple rays:
// field of view angle (center, e.g. player direction)
typedef struct s_raycaster
{
	t_ray_collision	collision;
	int				map_x;
	int				map_y;
	int				map_dir_x;
	int				map_dir_y;
	t_cvector		delta_ray;
	double			x_ray_len;
	double			y_ray_len;
	double			fov_center_angle;
}				t_raycaster;

typedef struct s_ray
{
	t_pos			origin;
	t_pvector		vec;
	t_raycaster		raycaster;
}				t_ray;

void	calculate_ray_collision(t_ray *ray, t_map *map);
void	raycaster_set_directions(t_ray *ray);
t_ray	ray_init(t_pos pos, double angle);

#endif  // RAY_H
