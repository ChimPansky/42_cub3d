
#ifndef SCENE_VALIDATION_H
# define SCENE_VALIDATION_H

# include "structs/trgb.h"
# include "structs/app.h"

# define MAP_SYMBOLS "01NSWE D"

typedef struct s_player t_player;

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

typedef struct s_sprite_source
{
	char	*wall_no;
	char	*wall_so;
	char	*wall_we;
	char	*wall_ea;
	t_trgb	floor;
	t_trgb	ceiling;
}				t_sprite_sources;

// scene_description.c:
int	read_scene_description(t_app *app, char *fpath,
		t_sprite_sources *sprites);

// walls_validation.c:
int		add_wall(t_sprite_sources *sprites, t_scene_element *element);
int		extract_tx_path_from_line(char **str, char **tx_path);

// floor_ceiling_validation.c
int		add_floor_ceiling(t_sprite_sources *sprites, t_scene_element *element);
int		extract_trgb_from_line(char **str, t_trgb *trgb);

// map_validation.c
int		read_map(t_game_state *game, int scene_fd);

// utilities.c:
void	skip_spaces(char **str);
t_line	get_next_line_no_nl(int scene_fd);

#endif
