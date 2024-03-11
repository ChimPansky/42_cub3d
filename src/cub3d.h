
#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "stdbool.h"
# include <errno.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

// Colors
# define COLOR_RESET "\033[0;39m"
# define COLOR_RED "\033[0;91m"
# define COLOR_GREEN "\033[0;92m"
# define COLOR_YELLOW "\033[0;93m"

# define PLAYER_MOVE_SPEED 50	// 1-100
# define PLAYER_ROTATION_SPEED 50 // 1-100
# define MAP_SYMBOLS "01NSWE D"

typedef int t_trgb;

typedef enum e_map_char {
	WALL = '1',
	PATH = '0',
	DOOR = 'D',
	PLAYER_N = 'N',
	PLAYER_S = 'S',
	PLAYER_W = 'W',
	PLAYER_E = 'E',
	HOLE = ' ',
}		t_map_char;

typedef enum e_map_sym {
	UNKNOWN_SYM = '\0',
	WALL_SYM = '1',
	PATH_SYM = '0',
}		t_map_sym;


typedef struct s_player t_player;

typedef struct s_map
{
	//t_map_syms	**raw_map;
	t_charptr_array	raw_map;
	size_t			width;
	size_t			height;
}			t_map;

typedef struct s_sprite_source
{
	char	*wall_no;
	char	*wall_so;
	char	*wall_we;
	char	*wall_ea;
	t_trgb	floor;
	t_trgb	ceiling;
}				t_sprite_source;

typedef struct s_pos
{
	double	x;
	double	y;
}				t_pos;

typedef struct s_speed
{
	double	x;
	double	y;
}				t_speed;

typedef struct s_player
{
	t_pos	pos;
	double	angle;
	t_speed	speed;
}				t_player;

typedef struct s_cube
{
	t_map		map;
	t_player	player;
}			t_cube;

typedef struct s_graph
{
	void			*mlx;
	// mlx...;
	// mlx_window;
	// mlx_img_minimap;
}				t_graph;

typedef struct s_app
{
	t_cube			cub;
	t_graph			gr;
	t_sprite_source	sprite_sources;


}				t_app;

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
void	read_scene_description(t_app *app, char *fpath);

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
