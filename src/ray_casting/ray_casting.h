/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:43:54 by tkasbari          #+#    #+#             */
/*   Updated: 2024/04/07 11:33:31 by tkasbari         ###   ########.fr       */
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

# include "../structs/rays.h"
#include "structs/physics.h"
#include "structs/vector.h"
#include <math.h>
#include <stdbool.h>

# define POS 1
# define NEG 0

// x_step_ray_len: length of vector if we advance +-1 in x_direction
// and dy in y_direction
// y_step_ray_len: length of vector if we advance +-1 in y_direction
// and dx in x_direction
typedef struct s_raycaster
{
	double		phi;
	bool		x_dir_positive;
	bool		y_dir_positive;
	t_cvector	ray_step_len;
	t_cvector	ray_len;
	double		collision_ray_len;
	t_pos		current_pos;
	bool		wall_hit;
	enum e_sprite_types	wall_hit_type;
}			t_raycaster;

void	raycaster_init(t_raycaster *raycaster, t_ray *ray);
void	calculate_ray_wall_collision(t_ray *ray, t_map *map);

#endif  // RAY_CASTING_H
