/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 21:14:32 by tkasbari          #+#    #+#             */
/*   Updated: 2024/04/18 21:21:22 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOR_H
# define DOOR_H

#include <stdbool.h>

typedef struct s_door
{
	int				map_x;
	int				map_y;
	bool			is_open;
	struct s_door	*next;
}				t_door;

#endif  // DOOR_H
