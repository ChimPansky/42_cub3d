/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_floor_ceiling_colors.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:33:28 by tkasbari          #+#    #+#             */
/*   Updated: 2024/03/25 14:13:58 by tkasbari         ###   ########.fr       */
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

static int	get_next_rgb_val(char **str, int *rgb_val)
{
	*rgb_val = 0;
	skip_spaces(str);
	if (**str == '\0' || **str == ',')
		return (print_error("Scene description: Found incomplete RGB value"));
	while (**str != '\0' && **str != ' ' && **str != ',')
	{
		if (**str < '0' || **str > '9')
			return (print_error("Scene description: "
				"RGB values can only contain digits."));
		*rgb_val = *rgb_val * 10 + **str - '0';
		(*str)++;
		if (*rgb_val > 255)
			return (print_error("Scene description: "
				"RGB values must be between 0 and 255."));
	}
	skip_spaces(str);
	return (SUCCESS);
}

int	extract_trgb_from_line(char **str, t_trgb *trgb)
{
	int	rgb[4];
	int	i;

	rgb[0] = FLOOR_CEILING_TRANSPARENCY;
	i = 1;
	while (i < 4)
	{
		if (get_next_rgb_val(str, rgb + i) != SUCCESS)
			return (FAILURE);
		if (i < 3)
		{
			if (**str != ',')
				return (print_error("RGB values in scene description "
					"must be separated by commas."));
			(*str)++;
		}
		i++;
	}
	*trgb = trgb_create(rgb[0], rgb[1], rgb[2], rgb[3]);
	return (SUCCESS);
}

void	print_trgb(t_trgb color)	//TODO: remove
{
	ft_printf("t: %d; r: %d; g: %d; b: %d\n",
	get_t_from_trgb(color),
	get_r_from_trgb(color),
	get_g_from_trgb(color),
	get_b_from_trgb(color));
}
