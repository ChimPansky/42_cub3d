#include "trgb.h"


static int	get_next_rgb_val(char **str, int shift)
{
	int		color_val;
	bool	valid;

	valid = false;
	color_val = 0;
	skip_spaces(str);
	if (**str == '\0')
		return (print_error("Found incomplete RGB value "
				"in scene description."));
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
			"must be between 0 and 255."));
}

int	extract_trgb_from_line(char **str, t_trgb *trgb)
{
	int	rgb;

	*trgb = *trgb | 100 << 24;
	rgb = get_next_rgb_val(str, 16);
	if (rgb == -1)
		return (FAILURE);
	if (**str != ',')
		return (print_error("RGB values in scene description "
				"must be separated by commas."));
	(*str)++;
	*trgb = *trgb | rgb;
	rgb = get_next_rgb_val(str, 8);
	if (rgb == -1)
		return (FAILURE);
	if (**str != ',')
		return (print_error("RGB values in scene description "
				"must be separated by commas."));
	(*str)++;
	*trgb = *trgb | rgb;
	rgb = get_next_rgb_val(str, 0);
	if (rgb == -1)
		return (FAILURE);
	*trgb = *trgb | rgb;
	return (SUCCESS);
}
