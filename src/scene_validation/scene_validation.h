
#ifndef SCENE_VALIDATION_H
# define SCENE_VALIDATION_H

# include "../cub3d.h"

# define MAP_SYMBOLS "01NSWE D"

typedef struct s_player t_player;

typedef enum e_scene_type
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	FLOOR,
	CEILING,
	WALLS_FLOOR_CEILING_COUNT,
	UNKNOWN
}			t_scene_type;
typedef struct s_scene_element
{
	t_scene_type	scene_type;
	union
	{
		char	*tx_path;
		t_trgb	trgb;
	};
}			t_scene_element;

typedef struct s_textures
{
	char	*wall_no;
	char	*wall_so;
	char	*wall_we;
	char	*wall_ea;
	t_trgb	floor;
	t_trgb	ceiling;
}				t_textures;

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

typedef struct s_cube
{
	t_map		map;
	bool		done;
	t_player	player;
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



// cub3d.c:
void 	cub_destroy(t_cube *cub);

// scene_validation.c:
void	read_scene_description(t_cube *cub, char *fpath);

// walls_validation.c:
int		add_wall(t_cube *cub, t_scene_element *element);
int		extract_tx_path_from_line(char **str, char **tx_path);

// floor_ceiling_validation.c
int		add_floor_ceiling(t_cube *cub, t_scene_element *element);
int		extract_trgb_from_line(char **str, t_trgb *trgb);

// map_validation.c
int		read_map(t_cube *cub, int scene_fd);

// destroy.c:
void cub_destroy(t_cube *cub);

// error_exit.c:
void	print_error(char *err_msg);
void	error_exit(t_cube *cub, int exit_code, char *err_msg);

// utilities.c:
void	skip_spaces(char **str);
t_line	get_next_line_no_nl(int scene_fd);

// debugging:
void	print_textures(t_textures textures);	//TODO: remove
void	print_player(t_player player); //TODO: remove
void	charptr_array_print(t_charptr_array *arr); // TODO: remove

#endif
