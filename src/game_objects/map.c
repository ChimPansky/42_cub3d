/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvilensk <vilenskii.v@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:35:16 by vvilensk          #+#    #+#             */
/*   Updated: 2024/05/04 15:46:57 by vvilensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

t_map_sym	coord_to_map_sym(t_map *map, t_pos coord)
{
	const int	x = coord.x - (coord.x < 0);
	const int	y = coord.y - (coord.y < 0);

	if (x >= (int)map->width || y >= (int)map->height || x < 0 || y < 0)
		return (UNKNOWN_SYM);
	if (map->raw_map.buf[y][x] == WALL_SYM)
		return (WALL_SYM);
	if (map->raw_map.buf[y][x] == PATH_SYM)
		return (PATH_SYM);
	if (map->raw_map.buf[y][x] == DOOR_SYM)
		return (DOOR_SYM);
	return (UNKNOWN_SYM);
}

void	try_change_map_symb(t_map *map, int x, int y, t_map_sym sym)
{
	if (coord_to_map_sym(map, cvector(x, y)) != UNKNOWN_SYM)
		map->raw_map.buf[y][x] = sym;
}

bool	coords_are_collidable(t_map *map, t_pos coord)
{
	return (coord_to_map_sym(map, coord) == WALL_SYM
		|| (coord_to_map_sym(map, coord) == DOOR_SYM
			&& !door_is_open(map->doors, coord.x, coord.y)));
}
