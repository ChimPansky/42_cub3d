/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trgb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvilensk <vilenskii.v@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 16:03:39 by vvilensk          #+#    #+#             */
/*   Updated: 2024/05/04 16:04:05 by vvilensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trgb.h"
#include "libft.h"
#include "utils.h"

t_trgb	trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

// TODO print errors
static int	get_next_rgb_val(char **str, int *rgb_val)
{
	*rgb_val = 0;
	skip_spaces(str);
	if (**str == '\0' || **str == ',')
		return (print_error("Scene description: Found incomplete RGB value",
				NULL));
	while (**str != '\0' && **str != ' ' && **str != ',')
	{
		if (**str < '0' || **str > '9')
			return (print_error("Scene description: "
					"RGB values can only contain digits.", NULL));
		*rgb_val = *rgb_val * 10 + **str - '0';
		(*str)++;
		if (*rgb_val > 255)
			return (print_error("Scene description: "
					"RGB values must be between 0 and 255.", NULL));
	}
	skip_spaces(str);
	return (SUCCESS);
}

int	trgb_parse(char **str, t_trgb *col)
{
	int	rgb[4];
	int	i;

	rgb[0] = 0;
	i = 1;
	while (i < 4)
	{
		if (get_next_rgb_val(str, rgb + i) != SUCCESS)
			return (FAILURE);
		if (i < 3)
		{
			if (**str != ',')
				return (print_error("RGB values "
						"must be separated by commas.", NULL));
			(*str)++;
		}
		i++;
	}
	*col = trgb(rgb[0], rgb[1], rgb[2], rgb[3]);
	return (SUCCESS);
}
