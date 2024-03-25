/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:45:04 by tkasbari          #+#    #+#             */
/*   Updated: 2024/03/21 09:38:21 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/utils.h"
#include "input_parsing.h"
#include <stdio.h>

int	equalize_string_lengths(t_map *map)
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

int	fill_raw_map(t_map *map, int scene_fd)
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
			return (free(line.str), print_error("Found empty line(s) in map"));
		else
			charptr_array_add_allocated_str(&map->raw_map, &line.str);
	}
	if (line.error)
		return (perror("read_map: get_next_line"), FAILURE);
	return (SUCCESS);
}
