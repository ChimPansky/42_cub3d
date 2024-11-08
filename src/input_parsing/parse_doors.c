/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_doors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:02:23 by tkasbari          #+#    #+#             */
/*   Updated: 2024/05/05 08:45:37 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "map.h"
#include "input_parsing.h"

int	door_validate(t_map map, size_t col, size_t row)
{
	char	up;
	char	down;
	char	left;
	char	right;

	if (col == 0 || row == 0 || col == map.width - 1 || row == map.height - 1)
		return (FAILURE);
	up = map.raw_map.buf[row - 1][col];
	down = map.raw_map.buf[row + 1][col];
	left = map.raw_map.buf[row][col - 1];
	right = map.raw_map.buf[row][col + 1];
	if ((left == WALL && right == WALL) || (up == WALL && down == WALL))
		return (SUCCESS);
	return (FAILURE);
}
