/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_floor_ceiling_colors.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:33:28 by tkasbari          #+#    #+#             */
/*   Updated: 2024/03/22 08:15:58 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/utils.h"
#include "input_parsing.h"



int	add_floor_ceiling(t_sprites *sprites, t_scene_element *element)
{
	t_trgb	*trgb;

	if (element->scene_type == FLOOR)
		trgb = &sprites->floor;
	else
		trgb = &sprites->ceiling;
	if (*trgb != 0)
		return (print_error("Found duplicate floor/ceiling element in "
				"scene description."));
	*trgb = element->trgb;
	return (SUCCESS);
}
