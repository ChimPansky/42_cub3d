/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvilensk <vilenskii.v@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 14:58:40 by vvilensk          #+#    #+#             */
/*   Updated: 2024/05/04 15:40:20 by vvilensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "libft.h"
# include "physics.h"
# include "door.h"

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

t_map_sym	coord_to_map_sym(t_map *map, t_pos coord);
void		try_change_map_symb(t_map *map, int x, int y, t_map_sym sym);
bool		coords_are_collidable(t_map *map, t_pos coord);

#endif  // MAP_H
