/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling_validation.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:33:28 by tkasbari          #+#    #+#             */
/*   Updated: 2024/03/08 15:32:17 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	get_next_rgb_val(char **str, int shift)
{
	int		color_val;
	bool	valid;

	valid = false;
	color_val = 0;
	skip_spaces(str);
	if (**str == '\0')
		return (print_error("Found incomplete RGB value "
			"in scene description."), -1);
	while (**str >= '0' && **str <= '9')
	{
		valid = true;
		color_val = color_val * 10 + **str - '0';
		(*str)++;
		if (color_val > 255)
		{
			valid = false;
			break ;
		}
	}
	skip_spaces(str);
	if (valid)
		return (color_val << shift);
	return (print_error("RGB values in scene description "
		"must be between 0 and 255."), -1);
}

int	extract_trgb_from_line(char **str, t_trgb *trgb)
{
	int	rgb;

	*trgb = *trgb | 100 << 24;	// Transparency
	rgb = get_next_rgb_val(str, 16);
	if (rgb == -1)
		return (FAILURE);
	if (**str != ',')
		return (print_error("RGB values in scene description "
			"must be separated by commas."), FAILURE);
	(*str)++;
	*trgb = *trgb | rgb;		// Red
	rgb = get_next_rgb_val(str, 8);
	if (rgb == -1)
		return (FAILURE);
	if (**str != ',')
		return (print_error("RGB values in scene description "
			"must be separated by commas."), FAILURE);
	(*str)++;
	*trgb = *trgb | rgb;		// Blue
	rgb = get_next_rgb_val(str, 0);
	if (rgb == -1)
		return (FAILURE);
	*trgb = *trgb | rgb;		// Green
	return (SUCCESS);
}

int	add_floor_ceiling(t_cube *cub, t_scene_element *element)
{
	t_trgb	*trgb;

	if (element->scene_type == FLOOR)
		trgb = &cub->walls_floor_ceiling.floor;
	else
		trgb = &cub->walls_floor_ceiling.ceiling;
	if (*trgb != 0)
		return (print_error("Found duplicate floor/ceiling element in "
			"scene description."), FAILURE);
	*trgb = element->trgb;
	return (SUCCESS);
}
