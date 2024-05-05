/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_walls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:45:04 by tkasbari          #+#    #+#             */
/*   Updated: 2024/05/05 08:47:44 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "input_parsing.h"

static int	check_walls_row_col(t_charptr_array raw_map, int row_col_check,
	size_t row_col_index, size_t max_index)
{
	char	last_char;
	char	cur_char;
	size_t	i;

	i = 0;
	last_char = HOLE;
	while (i < max_index)
	{
		if (row_col_check == ROW_CHECK)
			cur_char = raw_map.buf[row_col_index][i];
		else
			cur_char = raw_map.buf[i][row_col_index];
		if (ft_strchr("NSWED", cur_char))
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

int	check_walls(t_map map)
{
	size_t	row;
	size_t	col;

	row = 0;
	col = 0;
	while (row < map.height)
	{
		if (check_walls_row_col(map.raw_map, ROW_CHECK, row++, map.width)
			!= SUCCESS)
			return (print_error("Map not surrounded by walls.", NULL));
	}
	while (col < map.width)
	{
		if (check_walls_row_col(map.raw_map, COL_CHECK, col++, map.height)
			!= SUCCESS)
			return (print_error("Map not surrounded by walls.", NULL));
	}
	return (SUCCESS);
}
