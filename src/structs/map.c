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
