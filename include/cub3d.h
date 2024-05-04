/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvilensk <vilenskii.v@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 14:56:11 by vvilensk          #+#    #+#             */
/*   Updated: 2024/05/04 15:01:31 by vvilensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>

//             |
//             |
//             |
//             |
//           3pi/2
// ---------pi----0-------- x
//            pi/2
//             |
//             |
//             |
//             y

# define FPS 60

# define WIN_SIZE_FACTOR 0.50

# define PLAYER_COLLISION_RADIUS		0.1
# define PLAYER_SPEED_FIELD_PER_FRAME	(1. / FPS * 2)
# define PLAYER_RAD_PER_FRAME			(M_PI * 2. / FPS / 5)
# define PLAYER_RAD_PER_MOUSE_PIX		0.0007

# define MAX_RAY_DISTANCE 500

# define DOOR_OPENING_DISTANCE 1.0
# define DOOR_CLOSING_DISTANCE 2

// should be something between 1.0 and 3.0
# define WALL_HEIGHT 1.0
// 60 degrees player field of view
# define FOV (M_PI / 3)

// minimap offset and size
# define MM_X 20
# define MM_Y 20
# define MM_W 100
# define MM_H 75
# define MM_PIXEL_PER_FIELD 10.

// square MM_PLAYER_PIX_SZ * 2 + 1
# define MM_PLAYER_PIX_SZ 1

# define MM_WALL_COL 0xFFFFFFFF
# define MM_PATH_COL 0x00000000
# define MM_DOOR_COL 0x000000FF
# define MM_UNDEFINED_COL 0x0000FF00
# define MM_PLAYER_COL 0x00FF0000

#endif
