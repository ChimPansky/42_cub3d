#ifndef MAP_H
# define MAP_H

# include "libft.h"
# include "physics.h"
# include "structs/door.h"

typedef enum e_map_sym
{
	UNKNOWN_SYM = '\0',
	WALL_SYM = '1',
	PATH_SYM = '0',
	DOOR_SYM = 'D',
}		t_map_sym;

typedef struct s_map
{
	t_charptr_array	raw_map;
	t_map_sym		**map;
	t_door			*doors;
	size_t			width;
	size_t			height;
}			t_map;

t_map_sym	coord_to_map_sym(t_map *map, t_pos *coord);

#endif  // MAP_H
