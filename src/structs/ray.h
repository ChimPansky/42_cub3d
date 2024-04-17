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

// for now ray_casting is only used for rendering the screen contents (finding
// collision points between
// player view (a ray with starting position and viewing direction vector)
// and walls (as defined in map))
// later ray_casting can be used to find collision points between player and
// other objects...
#ifndef RAY_H
# define RAY_H

#include "structs/physics.h"
#include "vector/vector.h"
#include <math.h>
#include <stdbool.h>
#include "structs/sprites.h"
# include "structs/map.h"

typedef enum e_collision_direction
{
	COLL_EA = 0,
	COLL_SO = 1,
	COLL_WE = 2,
	COLL_NO = 3,
}	t_collision_direction;

// end_point: the point where the ray currently ends (keeps extending until hit)
// map_x, map_y: the indizes of the char** map
// map_dir_x, map_dir_y: x and y direction (1 or -1) depending on quadrants of angle
// delta_ray.x: y val, if we advance +-1 in x_direction
// delta_ray.y: x val, if we advance +-1 in y_direction
// x_ray_len: the length of the ray until the next collision with a vertical wall
// y_ray_len: the length of the ray until the next collision with a horizontal wall
typedef struct s_raycaster
{
	t_pos			end_point;
	int				map_x;
	int				map_y;
	int				map_dir_x;
	int				map_dir_y;
	t_cvector		delta_ray;
	double			x_ray_len;
	double			y_ray_len;
	t_sprite_types	sprite_collision;
	double			angle_btw_ray_and_player;
}				t_raycaster;

typedef struct s_ray
{
	t_pos			origin;
	t_pvector		vec;
	t_raycaster		rc;
}				t_ray;

void	ray_reset(t_ray *ray);
void	calculate_ray_wall_collision(t_ray *ray, t_map *map);
void	check_for_sprite_collision(t_map *map, t_ray *ray);

#endif  // RAY_H
