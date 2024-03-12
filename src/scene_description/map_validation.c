/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:45:04 by tkasbari          #+#    #+#             */
/*   Updated: 2024/03/12 13:33:25 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "scene_description.h"

static int	get_map_width(t_charptr_array raw_map)
{
	size_t	row;
	int	max_width;
	int	cur_width;

	row = 0;
	max_width = 0;
	cur_width = 0;
	while (row < raw_map.sz)
	{
		cur_width = ft_strlen(raw_map.buf[row++]);
		if (cur_width > max_width)
			max_width = cur_width;
	}
	return (max_width);
}

int	check_walls_in_col(t_charptr_array raw_map, size_t col, size_t map_height)
{
	size_t	row;
	char	last_char;
	char	cur_char;

	row = 0;
	last_char = HOLE;
	while (row < map_height)
	{
		cur_char = raw_map.buf[row][col];
		if (ft_strchr("NSWE", cur_char))
			cur_char = PATH;
		if (cur_char == PATH && (row == map_height - 1
			|| (last_char != PATH && last_char != WALL)))
			return (FAILURE);
		else if (cur_char == HOLE && last_char != HOLE && last_char != WALL)
			return (FAILURE);
		last_char = cur_char;
		row++;
	}
	return (SUCCESS);
}

int	check_walls_in_row(t_charptr_array raw_map, size_t row, size_t map_width)
{
	size_t	col;
	char	last_char;
	char	cur_char;

	col = 0;
	last_char = HOLE;
	while (col < map_width)
	{
		cur_char = raw_map.buf[row][col];
		if (ft_strchr("NSWE", cur_char))
			cur_char = PATH;
		if (cur_char == PATH && (col == map_width - 1
			|| (last_char != PATH && last_char != WALL)))
			return (FAILURE);
		else if (cur_char == HOLE && last_char != HOLE && last_char != WALL)
			return (FAILURE);
		last_char = cur_char;
		col++;
	}
	return (SUCCESS);
}
static int	check_walls(t_map map)
{
	size_t	row;
	size_t	col;

	row = 0;
	col = 0;
	while (row < map.height)
	{
		if (check_walls_in_row(map.raw_map, row++, map.width) != SUCCESS)
			return (print_error("Map not surrounded by walls"));
	}
	while (col < map.width)
	{
		if (check_walls_in_col(map.raw_map, col++, map.height) != SUCCESS)
			return (print_error("Map not surrounded by walls"));
	}
	return (SUCCESS);
}

static int	set_player_pos_and_angle(t_player *player,
	size_t x, size_t y, char direction)
{
	if (player->pos.x != 0.0)
		return (print_error("Found multiple starting positions "
			"for player in map"));
	player->pos.x = x + 0.5;
	player->pos.y = y + 0.5;
	if (direction == PLAYER_E)
		player->angle = 0.0;
	else if(direction == PLAYER_S)
		player->angle = M_PI_2;
	else if(direction == PLAYER_W)
		player->angle = M_PI;
	else if(direction == PLAYER_N)
		player->angle = M_PI + M_PI_2;
	return (SUCCESS);
}

static int	check_for_invalid_chars_and_player(t_player *player,
	t_map *map)
{
	size_t	row;
	size_t	col;

	row = 0;
	while (row < map->raw_map.sz)
	{
		col = 0;
		while (col < map->width)
		{
			if (!ft_strchr(MAP_SYMBOLS, map->raw_map.buf[row][col]))
				return (print_error("Found invalid character in map"),
					FAILURE);
			if (ft_strchr("NSWE", map->raw_map.buf[row][col]))
			{
				if (set_player_pos_and_angle(player, col, row,
					map->raw_map.buf[row][col]) != SUCCESS)
					return (FAILURE);
				map->raw_map.buf[row][col] = PATH;
			}
			col++;
		}
		row++;
	}
	return (SUCCESS);
}

static int	equalize_string_lengths(t_map *map)
{
	size_t	row;

	row = 0;
	while (row < map->raw_map.sz)
	{
		if (ft_strlen(map->raw_map.buf[row]) < map->width)
		{
			map->raw_map.buf[row] = ft_strrpad(map->raw_map.buf[row], ' ',
				map->width, true);
			if (!map->raw_map.buf[row])
				return (perror("validate_map: ft_strrpad"), FAILURE);
		}
		row++;
	}
	return (SUCCESS);
}

static int	validate_map(t_game_state *game)
{
	game->map.height = game->map.raw_map.sz;
	game->map.width = get_map_width(game->map.raw_map);
	if (game->map.height < 3 || game->map.width < 3)
		return (print_error("Map too small."));
	if (equalize_string_lengths(&game->map) != SUCCESS)
		return (FAILURE);
	if (check_for_invalid_chars_and_player(&game->player, &game->map)
		!= SUCCESS)
		return (FAILURE);
	if (game->player.pos.x == 0.0)
		return (print_error("Map has no player."));
	if (check_walls(game->map) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}


static int	fill_raw_map(t_map *map, int scene_fd)
{
	t_line	line;
	bool	empty_lines;

	empty_lines = false;
	while (true)
	{
		line = get_next_line_no_nl(scene_fd);
		if (line.str == NULL)
			break ;
		if (ft_string_is_empty(line.str))
		{
			free(line.str);
			if (map->raw_map.sz > 0)
				empty_lines = true;
		}
		else if (empty_lines)
			return (free(line.str),	print_error("Found empty line(s) in map"));
		else
			charptr_array_add_allocated_str(&map->raw_map, &line.str);
	}
	if (line.error)
		return (perror("read_map: get_next_line"), FAILURE);
	return (SUCCESS);
}

int	read_map(t_game_state *game, int scene_fd)
{
	if (fill_raw_map(&game->map, scene_fd) != SUCCESS)
		return (FAILURE);
	if (validate_map(game) != SUCCESS)
		return (FAILURE);
	//print_player(map.player);
	return (SUCCESS);
}
