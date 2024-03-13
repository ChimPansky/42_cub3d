#ifndef MAP_H
# define MAP_H

# include "libft.h"
# include "physics.h"

typedef enum e_map_sym {
	UNKNOWN_SYM = '\0',
	WALL_SYM = '1',
	PATH_SYM = '0',
}		t_map_sym;

typedef struct s_map
{
	t_charptr_array	raw_map;
	size_t			width;
	size_t			height;
}			t_map;

t_map_sym	coord_to_map_sym(t_map *map, t_pos *coord);

#endif  // MAP_H
