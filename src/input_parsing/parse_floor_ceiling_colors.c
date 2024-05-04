/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_floor_ceiling_colors.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:33:28 by tkasbari          #+#    #+#             */
/*   Updated: 2024/04/27 13:07:08 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"
#include "utils.h"
#include "input_parsing.h"

int	add_floor_ceiling(t_static_graphics *static_gr, t_scene_element *element)
{
	t_trgb	*color;

	if (element->scene_type == FLOOR)
		color = &static_gr->floor_col;
	else
		color = &static_gr->ceiling_col;
	if (*color != 0)
		return (print_error("Found duplicate floor/ceiling element in "
				"scene description.", NULL));
	*color = element->trgb;
	return (SUCCESS);
}

void	print_trgb(t_trgb color)
{
	ft_printf("t: %d; r: %d; g: %d; b: %d\n",
		color >> 24, (color >> 16) % 256, (color >> 8) % 256, color % 256);
}
