/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:45:04 by tkasbari          #+#    #+#             */
/*   Updated: 2024/03/19 09:05:24 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "input_parsing.h"
#include <math.h>


// int	check_walls_in_col(t_charptr_array raw_map, size_t col, size_t map_height)
// {
// 	size_t	row;
// 	char	last_char;
// 	char	cur_char;

// 	row = 0;
// 	last_char = HOLE;
// 	while (row < map_height)
// 	{
// 		cur_char = raw_map.buf[row][col];
// 		if (ft_strchr("NSWE", cur_char))
// 			cur_char = PATH;
// 		if (cur_char == PATH && (row == map_height - 1
// 			|| (last_char != PATH && last_char != WALL)))
// 			return (FAILURE);
// 		else if (cur_char == HOLE && last_char != HOLE && last_char != WALL)
// 			return (FAILURE);
// 		last_char = cur_char;
// 		row++;
// 	}
// 	return (SUCCESS);
// }

// int	check_walls_in_row(t_charptr_array raw_map, size_t row, size_t map_width)
// {
// 	size_t	col;
// 	char	last_char;
// 	char	cur_char;

// 	col = 0;
// 	last_char = HOLE;
// 	while (col < map_width)
// 	{
// 		cur_char = raw_map.buf[row][col];
// 		if (ft_strchr("NSWE", cur_char))
// 			cur_char = PATH;
// 		if (cur_char == PATH && (col == map_width - 1
// 			|| (last_char != PATH && last_char != WALL)))
// 			return (FAILURE);
// 		else if (cur_char == HOLE && last_char != HOLE && last_char != WALL)
// 			return (FAILURE);
// 		last_char = cur_char;
// 		col++;
// 	}
// 	return (SUCCESS);
// }


int	check_walls_row_col(t_charptr_array raw_map, int row_col_check, size_t row_col_to_check, size_t max_index)
{
	char	last_char;
	char	cur_char;
	size_t	i;

	i = 0;
	last_char = HOLE;
	while (i < max_index)
	{
		if (row_col_check == ROW_CHECK)
			cur_char = raw_map.buf[row_col_to_check][i];
		else
			cur_char = raw_map.buf[i][row_col_to_check];
		if (ft_strchr("NSWE", cur_char))
			cur_char = PATH;
		if (cur_char == PATH && (i == max_index - 1
			|| (last_char != PATH && last_char != WALL)))
			return (FAILURE);
		else if (cur_char == HOLE && last_char != HOLE && last_char != WALL)
			return (FAILURE);
		last_char = cur_char;
		i++;
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
		if (check_walls_row_col(map.raw_map, ROW_CHECK, row++, map.width) != SUCCESS)
			return (print_error("Map not surrounded by walls"));
	}
	while (col < map.width)
	{
		if (check_walls_row_col(map.raw_map, COL_CHECK, col++, map.height) != SUCCESS)
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

int	read_and_validate_map(t_game_state *game, int scene_fd)
{
	if (fill_raw_map(&game->map, scene_fd) != SUCCESS)
		return (FAILURE);
	game->map.height = game->map.raw_map.sz;
	game->map.width = get_map_width(game->map.raw_map);
	if (equalize_string_lengths(&game->map) != SUCCESS)
		return (FAILURE);
	if (game->map.height < 3 || game->map.width < 3)
		return (print_error("Map too small."));
	if (check_for_invalid_chars_and_player(&game->player, &game->map)
		!= SUCCESS)
		return (FAILURE);
	if (game->player.pos.x == 0.0)
		return (print_error("Map has no player."));
	if (check_walls(game->map) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}
