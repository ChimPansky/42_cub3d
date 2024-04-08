/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:43:54 by tkasbari          #+#    #+#             */
/*   Updated: 2024/04/08 12:27:39 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// for now ray_casting is only used for rendering the screen contents (finding
// collision points between
// player view (a ray with starting position and viewing direction vector)
// and walls (as defined in map))
// later ray_casting can be used to find collision points between player and
// other objects...
#ifndef RAY_CASTING_H
# define RAY_CASTING_H

#include "structs/physics.h"
#include "structs/vector.h"
#include <math.h>
#include <stdbool.h>
#include "structs/sprites.h"
# include "structs/map.h"

# define POS 1
# define NEG 0

typedef enum e_collision_direction
{
	COLL_EA = 0,
	COLL_SO = 1,
	COLL_WE = 2,
	COLL_NO = 3,
}	t_collision_direction;

typedef struct s_ray_collision
{
	t_pos			collision_point;
	double			distance_from_origin;
	t_sprite_types	collision_sprite_type;
}				t_ray_collision;

typedef struct s_ray
{
	t_pos			origin;
	t_pvector		direction;
	t_ray_collision	collision;
}				t_ray;

// x_step_ray_len: length of vector if we advance +-1 in x_direction
// and dy in y_direction
// y_step_ray_len: length of vector if we advance +-1 in y_direction
// and dx in x_direction
typedef struct s_raycaster
{
	double			phi;
	bool			x_dir_positive;
	bool			y_dir_positive;
	t_cvector		ray_step_len;
	t_cvector		ray_len;
	double			collision_ray_len;
	t_pos			current_pos;
	t_sprite_types	sprite_collision;
}			t_raycaster;

void	raycaster_init(t_raycaster *raycaster, t_ray *ray);
void	calculate_ray_wall_collision(t_ray *ray, t_map *map);
void	check_for_sprite_collision(t_map *map, t_raycaster *rc);

#endif  // RAY_CASTING_H
