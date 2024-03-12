#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "stdbool.h"
# include <errno.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "graphics/graphics.h"
# include "hooks/hooks.h"


// Colors
# define COLOR_RESET "\033[0;39m"
# define COLOR_RED "\033[0;91m"
# define COLOR_GREEN "\033[0;92m"
# define COLOR_YELLOW "\033[0;93m"

# define PLAYER_MOVE_SPEED 50	// 1-100
# define PLAYER_ROTATION_SPEED 50 // 1-100
# define MAP_SYMBOLS "01NSWE D"

typedef int				t_trgb;
typedef struct s_player	t_player;

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

typedef struct s_map
{
	t_charptr_array	raw_map;
	size_t			width;
	size_t			height;
}			t_map;

typedef struct s_pos
{
	double	x;
	double	y;
}				t_pos;

typedef struct s_speed
{
	double	forw;
	double	ort;
}				t_speed;

typedef struct s_player
{
	t_pos	pos;
	double	angle;
	t_speed	speed;
}				t_player;

typedef struct s_game_state
{
	t_map		map;
	t_player	player;
}			t_game_state;

typedef struct s_sprite_sources
{
	char	*wall_no;
	char	*wall_so;
	char	*wall_we;
	char	*wall_ea;
	t_trgb	floor;
	t_trgb	ceiling;
}				t_sprite_sources;

typedef struct s_app
{
	t_game_state		game;
	t_graph				graph;
	t_pressed_keys		pressed_keys;
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

// app.c:
int		main(int ac, char *av[]);
int		main_loop(void *data);
void	sprite_sources_destroy(t_sprite_sources *sprites);
void	app_destroy(t_app *app);

// map_validation.c
int		read_map(t_cube *cub, int scene_fd);

// error_exit.c:
int	print_error(char *err_msg);
void	error_exit(t_cube *cub, int exit_code, char *err_msg);

// debugging:
void	print_textures(t_sprite_source sprite_sources);	//TODO: remove
void	print_player(t_player player); //TODO: remove
void	charptr_array_print(t_charptr_array *arr); // TODO: remove

#endif
