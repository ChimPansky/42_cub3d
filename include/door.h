/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 21:14:32 by tkasbari          #+#    #+#             */
/*   Updated: 2024/05/02 16:20:52 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOR_H
# define DOOR_H

# include <stdbool.h>

typedef struct  s_game_state t_game_state;

typedef struct s_door
{
	int				map_x;
	int				map_y;
	bool			is_open;
	struct s_door	*next;
}				t_door;

int		door_add(t_door **doors, int map_x, int map_y, bool is_open);
void	doors_check_and_close(t_game_state *game, t_door **doors);
void	doors_destroy(t_door **doors);
t_door	*door_get(t_door *doors, int map_x, int map_y);
void	doors_print(t_door *doors);
bool	door_is_open(t_door *doors, int map_x, int map_y);

#endif  // DOOR_H
