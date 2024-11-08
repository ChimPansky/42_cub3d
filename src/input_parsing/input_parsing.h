/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:21:30 by tkasbari          #+#    #+#             */
/*   Updated: 2024/05/05 08:47:26 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_PARSING_H
# define INPUT_PARSING_H

# include "trgb.h"
# include "app.h"
# include "sprites.h"

# define MAP_SYMBOLS "01NSWE D"
# define FLOOR_CEILING_TRANSPARENCY 50

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

typedef enum e_row_col_check {
	ROW_CHECK,
	COL_CHECK
}			t_row_col_check;

typedef enum e_scene_type
{
	UNKNOWN = 99,
	EAST = 0,
	SOUTH = 1,
	WEST = 2,
	NORTH = 3,
	FLOOR = 4,
	CEILING = 5,
	WALLS_FLOOR_CEILING_COUNT = 6,
}			t_scene_type;

typedef struct s_scene_element
{
	t_scene_type	scene_type;
	char			*tx_path;
	t_trgb			trgb;
}			t_scene_element;

// input_parsing.c:
int		read_scene_description(t_app *app, char *fpath);

// parse_wall_textures.c:
int		add_sprite_img(void *mlx,
			t_sprites *sprites, int type, char *img_path);
int		extract_tx_path_from_line(char **str, char **tx_path);

// pars_floor_ceiling_colors.c
int		add_floor_ceiling(t_static_graphics *sprites, t_scene_element *element);
int		extract_trgb_from_line(char **str, t_trgb *trgb);

// parse_map.c
int		read_and_validate_map(t_game_state *game, int scene_fd);

// parse_map_walls.c
int		check_walls(t_map map);

// parse_doors.c
int		door_validate(t_map map, size_t col, size_t row);

// prepare_map.c
int		fill_raw_map(t_map *map, int scene_fd);
int		equalize_string_lengths(t_map *map);

// utilities.c:
t_line	get_next_line_no_nl(int scene_fd);
int		get_map_width(t_charptr_array raw_map);

#endif
