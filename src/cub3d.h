
#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "stdbool.h"
# include <errno.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
#


// Colors
# define COLOR_RESET "\033[0;39m"
# define COLOR_RED "\033[0;91m"
# define COLOR_GREEN "\033[0;92m"
# define COLOR_YELLOW "\033[0;93m"

# define movement_speed	80

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

typedef struct s_rgba
{
	short int	red;
	short int	green;
	short int	blue;
	short int	alpha;
}				t_rgba;

typedef enum e_texture_type
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	FLOOR,
	CEILING,
	TX_COUNT,
	UNKNOWN
}			t_texture_type;
typedef struct s_texture_element
{
	t_texture_type	tx_type;
	union
	{
		char	*tx_path;
		t_rgba	tx_rgba;
	};
}			t_texture_element;

typedef struct s_textures
{
	char	*wall_no;
	char	*wall_so;
	char	*wall_we;
	char	*wall_ea;
	t_rgba	floor;
	t_rgba	ceiling;
}				t_textures;

typedef struct s_cube
{
	t_map		*map;
	bool		done;
	t_player	*player;
	t_textures	walls_floor_ceiling;
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

// cub3d.c:
void cub_destroy(t_cube *cub);

// scene_validation.c:
void	read_scene_description(t_cube *cub, char *fpath);

// destroy.c:
void cub_destroy(t_cube *cub);

// error_exit.c:
void	error_exit(t_cube *cub, char *err_msg, int exit_code);


#endif
