/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:45:04 by tkasbari          #+#    #+#             */
/*   Updated: 2024/05/05 08:47:00 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_state.h"
#include "utils.h"
#include "input_parsing.h"
#include <math.h>
#include <stdio.h>

static int	set_player_pos_and_angle(t_player *player,
	size_t x, size_t y, char direction)
{
	if (player->pos.x != 0.0)
		return (print_error("Found multiple starting positions for player.",
				NULL));
	player->pos.x = x + 0.5;
	player->pos.y = y + 0.5;
	if (direction == PLAYER_E)
		player->angle = 0.0;
	else if (direction == PLAYER_S)
		player->angle = M_PI_2;
	else if (direction == PLAYER_W)
		player->angle = M_PI;
	else if (direction == PLAYER_N)
		player->angle = M_PI + M_PI_2;
	return (SUCCESS);
}

static int	handle_map_symbol(t_game_state *game, size_t row, size_t col)
{
	if (ft_strchr("NSWE", game->map.raw_map.buf[row][col]))
	{
		if (set_player_pos_and_angle(&game->player, col, row,
				game->map.raw_map.buf[row][col]) != SUCCESS)
			return (FAILURE);
		game->map.raw_map.buf[row][col] = PATH;
	}
	else if (game->map.raw_map.buf[row][col] == 'D')
	{
		if (door_validate(game->map, col, row) != SUCCESS)
			return (print_error("Doors have to be between walls.", NULL));
		if (door_add(&game->map.doors, col, row, false) != SUCCESS)
			return (perror("handle_map_symbol: door_add"), FAILURE);
	}
	return (SUCCESS);
}

static int	parse_map_symbols(t_game_state *game)
{
	size_t	row;
	size_t	col;

	row = 0;
	while (row < game->map.raw_map.sz)
	{
		col = 0;
		while (col < game->map.width)
		{
			if (!ft_strchr(MAP_SYMBOLS, game->map.raw_map.buf[row][col]))
				return (print_error("Found invalid character in map.", NULL));
			if (handle_map_symbol(game, row, col) != SUCCESS)
				return (FAILURE);
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
		return (print_error("Map too small.", NULL));
	if (parse_map_symbols(game) != SUCCESS)
		return (FAILURE);
	if (game->player.pos.x == 0.0)
		return (print_error("Map has no player.", NULL));
	if (check_walls(game->map) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}
