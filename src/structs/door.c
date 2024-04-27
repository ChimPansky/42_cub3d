/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 21:14:29 by tkasbari          #+#    #+#             */
/*   Updated: 2024/04/19 15:39:07 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "door.h"
#include <stdlib.h>
#include "../cub3d.h"
#include <stdio.h>

int	door_add(t_door **doors, int map_x, int map_y, bool is_open)
{
	t_door	*new_door;
	t_door	*last_door;

	new_door = malloc(sizeof(t_door));
	if (!new_door)
		return (FAILURE);
	new_door->map_x = map_x;
	new_door->map_y = map_y;
	new_door->is_open = is_open;
	new_door->next = NULL;
	if (*doors == NULL)
		*doors = new_door;
	else
	{
		last_door = *doors;
		while (last_door->next != NULL)
			last_door = last_door->next;
		last_door->next = new_door;
	}
	return (SUCCESS);
}

void	doors_destroy(t_door **doors)
{
	t_door	*current_door;
	t_door	*next_door;

	if (doors == NULL || *doors == NULL)
		return ;
	current_door = *doors;
	while (current_door != NULL)
	{
		next_door = current_door->next;
		free(current_door);
		current_door = next_door;
	}
}

t_door	*door_get(t_door *doors, int map_x, int map_y)
{
	while (doors != NULL)
	{
		if (doors->map_x == map_x && doors->map_y == map_y)
			return (doors);
		doors = doors->next;
	}
	return (NULL);
}

void	door_print(t_door *door)
{
	if (door == NULL)
		return ;
	printf("Door(%d, %d): ", door->map_x, door->map_y);
	if (door->is_open)
		printf("open\n");
	else
		printf("closed\n");
}

void	doors_print(t_door *doors)
{
	int	i;

	i = 0;
	while (doors != NULL)
	{
		printf("%d ", i++);
		door_print(doors);
		doors = doors->next;
	}
}

// int main()
// {
// 	t_door *doors = NULL;
// 	t_door *door;

// 	door_add(&doors, 1, 2, true);
// 	door_add(&doors, 3, 4, false);
// 	door_add(&doors, 1231, 788, false);
// 	door_add(&doors, 0, 86, false);
// 	doors_print(doors);

// 	door = door_get(doors, 5, 4);
// 	door_print(door);
// 	doors_destroy(&doors);
// 	return 0;
// }
