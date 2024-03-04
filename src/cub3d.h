
#ifndef CUB3D_H
# define CUB3D_H

// # include <stdio.h>
// # include "libft.h"
#include "stdbool.h"

#define movement_speed	80

typedef enum e_map_syms {
	WALL = '1',
	DOOR = 'D',
	PLAYER_E = 'E',
	PLAYER_W = 'W',
	PLAYER_S = 'S',
	PLAYER_N = 'N',
	HOLE = ' ',
}		t_map_syms;

typedef struct s_player t_player;

typedef struct s_map
{
	t_map_syms	**raw_map;
	int			width;
	int			height;
}			t_map;

typedef struct s_cube
{
	t_map		*map;
	bool		done;
	t_player	*player;
}			t_cube;

typedef struct s_mlx
{
	void *mlx;
	// mlx...;
	// mlx_window;
	// mlx_img_minimap;
}				t_mlx;
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

typedef struct s_pos
{
	float	x;
	float	y;
}				t_pos;

typedef struct s_speed
{
	float	x;
	float	y;
}				t_speed;

typedef struct s_player
{
	t_pos	pos;
	float	angle;
	t_speed	speed;
}				t_player;





#endif
