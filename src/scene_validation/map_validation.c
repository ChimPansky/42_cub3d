/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:45:04 by tkasbari          #+#    #+#             */
/*   Updated: 2024/03/09 00:32:51 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdbool.h>


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

int	check_walls_in_col(t_charptr_array *raw_map, size_t col, size_t map_height)
{
	size_t	row;
	char	last_char;
	char	cur_char;

	row = 0;
	last_char = HOLE;
	while (row < map_height)
	{
		cur_char = raw_map->buf[row][col];
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

int	check_walls_in_row(t_charptr_array *raw_map, size_t row, size_t map_width)
{
	size_t	col;
	char	last_char;
	char	cur_char;

	col = 0;
	last_char = HOLE;
	while (col < map_width)
	{
		cur_char = raw_map->buf[row][col];
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
static int	check_walls(t_cube *cub, t_charptr_array *raw_map)
{
	size_t	row;
	size_t	col;

	row = 0;
	col = 0;
	while (row < cub->map.height)
	{
		if (check_walls_in_row(raw_map, row++, cub->map.width) != SUCCESS)
			return (print_error("Map not surrounded by walls"), FAILURE);
	}
	while (col < cub->map.width)
	{
		if (check_walls_in_col(raw_map, col++, cub->map.height) != SUCCESS)
			return (print_error("Map not surrounded by walls"), FAILURE);
	}
	return (SUCCESS);
}

static int	set_player_pos_and_angle(t_cube *cub,
	size_t x, size_t y, char direction)
{
	if (cub->player.pos.x != -1.0)
		return (print_error("Found multiple starting positions "
			"for player in map"), FAILURE);
	cub->player.pos.x = x;
	cub->player.pos.y = y;
	if (direction == 'E')
		cub->player.angle = 0.0;
	else if(direction == 'S')
		cub->player.angle = M_PI_2;
	else if(direction == 'W')
		cub->player.angle = M_PI;
	else if(direction == 'N')
		cub->player.angle = M_PI + M_PI_2;
	return (SUCCESS);
}

static int	check_for_invalid_chars_and_player(t_cube *cub,
	t_charptr_array *raw_map)
{
	size_t	row;
	size_t	col;

	row = 0;
	while (row < raw_map->sz)
	{
		col = 0;
		while (col < cub->map.width)
		{
			if (!ft_strchr(MAP_SYMBOLS, raw_map->buf[row][col]))
				return (print_error("Found invalid character in map"),
					FAILURE);
			if (ft_strchr("NSWE", raw_map->buf[row][col]))
			{
				if (set_player_pos_and_angle(cub, col, row,
					raw_map->buf[row][col]) != SUCCESS)
					return (FAILURE);
			}
			col++;
		}
		row++;
	}
	return (SUCCESS);
}

static int	equalize_string_lengths(t_cube *cub, t_charptr_array *raw_map)
{
	size_t	row;

	row = 0;
	while (row < raw_map->sz)
	{
		if (ft_strlen(raw_map->buf[row]) < cub->map.width)
		{
			raw_map->buf[row] = ft_strrpad(raw_map->buf[row], ' ',
				cub->map.width, true);
			if (!raw_map->buf[row])
				return (perror("validate_map: ft_strrpad"), FAILURE);
		}
		row++;
	}
	return (SUCCESS);
}

static int	validate_map(t_cube *cub, t_charptr_array *raw_map)
{
	cub->map.height = raw_map->sz;
	cub->map.width = get_map_width(*raw_map);
	if (cub->map.height < 3 || cub->map.width < 3)
		return (print_error("Map too small."), FAILURE);
	if (equalize_string_lengths(cub, raw_map) != SUCCESS)
		return (FAILURE);
	charptr_array_print(raw_map);
	if (check_for_invalid_chars_and_player(cub, raw_map) != SUCCESS)
		return (FAILURE);
	if (cub->player.pos.x == -1.0)
		return (print_error("Map has no player."), FAILURE);
	if (check_walls(cub, raw_map) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

int	read_map(t_cube *cub, int scene_fd)
{
	t_line	line;

	while (true)
	{
		line = get_next_line(scene_fd);
		if (line.str == NULL)
			break ;
		ft_str_chr_replace(line.str, '\n', '\0');
		if (ft_string_is_empty(line.str))
		{
			free(line.str);
			if (cub->map.raw_map.sz > 0)
				return (print_error("Found empty line in map"), FAILURE);
		}
		else
			charptr_array_add_allocated_str(&cub->map.raw_map, &line.str);
	}
	if (line.error)
		return (perror("read_map: get_next_line"), FAILURE);
	if (validate_map(cub, &cub->map.raw_map) != SUCCESS)
		return (FAILURE);
	print_player(cub->player);
	return (SUCCESS);
}
